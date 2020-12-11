#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dirent.h>
#include <sys/iosupport.h>
#include <sys/param.h>
#include <unistd.h>
#include <stdbool.h>

#include "../../include/wut_romfs_dev.h"

typedef enum {
    RomfsSource_FileDescriptor,
} RomfsSource;

typedef struct romfs_mount {
    devoptab_t device;
    bool setup;
    RomfsSource fd_type;
    int32_t id;
    int32_t fd;
    time_t mtime;
    uint64_t offset;
    romfs_header header;
    romfs_dir *cwd;
    uint32_t *dirHashTable, *fileHashTable;
    void *dirTable, *fileTable;
    char name[32];
} romfs_mount;

extern int __system_argc;
extern char **__system_argv;

//static char __thread __component[PATH_MAX+1];
static char __component[PATH_MAX + 1];

#define romFS_root(m)   ((romfs_dir*)(m)->dirTable)
#define romFS_none      ((uint32_t)~0)
#define romFS_dir_mode  (S_IFDIR | S_IRUSR | S_IRGRP | S_IROTH)
#define romFS_file_mode (S_IFREG | S_IRUSR | S_IRGRP | S_IROTH)


static romfs_dir *romFS_dir(romfs_mount *mount, uint32_t off) {
    if (off + sizeof(romfs_dir) > mount->header.dirTableSize) return NULL;
    romfs_dir *curDir = ((romfs_dir * )((uint8_t *) mount->dirTable + off));
    if (off + sizeof(romfs_dir) + curDir->nameLen > mount->header.dirTableSize) return NULL;
    return curDir;
}

static romfs_file *romFS_file(romfs_mount *mount, uint32_t off) {
    if (off + sizeof(romfs_file) > mount->header.fileTableSize) return NULL;
    romfs_file *curFile = ((romfs_file * )((uint8_t *) mount->fileTable + off));
    if (off + sizeof(romfs_file) + curFile->nameLen > mount->header.fileTableSize) return NULL;
    return curFile;
}

static ssize_t _romfs_read(romfs_mount *mount, uint64_t offset, void *buffer, uint64_t size) {
    uint64_t pos = mount->offset + offset;
    size_t _read = 0;
    if (mount->fd_type == RomfsSource_FileDescriptor) {
        off_t seek_offset = lseek(mount->fd, pos, SEEK_SET);
        if (pos != seek_offset) {
            return -1;
        }
        _read = read(mount->fd, buffer, size);
    }
    return _read;
}

static bool _romfs_read_chk(romfs_mount *mount, uint64_t offset, void *buffer, uint64_t size) {
    return _romfs_read(mount, offset, buffer, size) == size;
}

//-----------------------------------------------------------------------------

static int romfs_open(struct _reent *r, void *fileStruct, const char *path, int flags, int mode);

static int romfs_close(struct _reent *r, void *fd);

static ssize_t romfs_read(struct _reent *r, void *fd, char *ptr, size_t len);

static off_t romfs_seek(struct _reent *r, void *fd, off_t pos, int dir);

static int romfs_fstat(struct _reent *r, void *fd, struct stat *st);

static int romfs_stat(struct _reent *r, const char *path, struct stat *st);

static int romfs_chdir(struct _reent *r, const char *path);

static DIR_ITER *romfs_diropen(struct _reent *r, DIR_ITER *dirState, const char *path);

static int romfs_dirreset(struct _reent *r, DIR_ITER *dirState);

static int romfs_dirnext(struct _reent *r, DIR_ITER *dirState, char *filename, struct stat *filestat);

static int romfs_dirclose(struct _reent *r, DIR_ITER *dirState);

typedef struct {
    romfs_mount *mount;
    romfs_file *file;
    uint64_t offset, pos;
} romfs_fileobj;

typedef struct {
    romfs_mount *mount;
    romfs_dir *dir;
    uint32_t state;
    uint32_t childDir;
    uint32_t childFile;
} romfs_diriter;

static const devoptab_t romFS_devoptab =
        {
                .structSize   = sizeof(romfs_fileobj),
                .open_r       = romfs_open,
                .close_r      = romfs_close,
                .read_r       = romfs_read,
                .seek_r       = romfs_seek,
                .fstat_r      = romfs_fstat,
                .stat_r       = romfs_stat,
                .chdir_r      = romfs_chdir,
                .dirStateSize = sizeof(romfs_diriter),
                .diropen_r    = romfs_diropen,
                .dirreset_r   = romfs_dirreset,
                .dirnext_r    = romfs_dirnext,
                .dirclose_r   = romfs_dirclose,
                // symlinks aren't supported so alias lstat to stat
                .lstat_r      = romfs_stat,
        };

static bool romfs_initialised = false;
static romfs_mount romfs_mounts[32];

//-----------------------------------------------------------------------------

static int32_t romfsMountCommon(const char *name, romfs_mount *mount);

static void romfsInitMtime(romfs_mount *mount);

static void _romfsResetMount(romfs_mount *mount, int32_t id) {
    memset(mount, 0, sizeof(*mount));
    memcpy(&mount->device, &romFS_devoptab, sizeof(romFS_devoptab));
    mount->device.name = mount->name;
    mount->device.deviceData = mount;
    mount->id = id;
}

static void _romfsInit(void) {
    uint32_t i;
    uint32_t total = sizeof(romfs_mounts) / sizeof(romfs_mount);

    if (!romfs_initialised) {
        for (i = 0; i < total; i++) {
            _romfsResetMount(&romfs_mounts[i], i);
        }

        romfs_initialised = true;
    }
}

static romfs_mount *romfsFindMount(const char *name) {
    uint32_t i;
    uint32_t total = sizeof(romfs_mounts) / sizeof(romfs_mount);
    romfs_mount *mount = NULL;

    _romfsInit();

    for (i = 0; i < total; i++) {
        mount = &romfs_mounts[i];

        if (name == NULL) { //Find an unused mount entry.
            if (!mount->setup)
                return mount;
        } else if (mount->setup) { //Find the mount with the input name.
            if (strncmp(mount->name, name, sizeof(mount->name)) == 0)
                return mount;
        }
    }

    return NULL;
}

__attribute__((weak)) const char *__romfs_path = NULL;

static romfs_mount *romfs_alloc(void) {
    return romfsFindMount(NULL);
}

static void romfs_free(romfs_mount *mount) {
    free(mount->fileTable);
    free(mount->fileHashTable);
    free(mount->dirTable);
    free(mount->dirHashTable);
    _romfsResetMount(mount, mount->id);
}

static void romfs_mountclose(romfs_mount *mount) {
    if (mount->fd_type == RomfsSource_FileDescriptor) {
        close(mount->fd);
    }
    romfs_free(mount);
}

int32_t romfsMount(const char *name, const char *filepath) {
    romfs_mount *mount = romfs_alloc();
    if (mount == NULL)
        return 99;

    // Regular RomFS
    mount->fd_type = RomfsSource_FileDescriptor;

    mount->fd = open(filepath, 0);
    if (mount->fd == -1) {
        romfs_free(mount);
        return -1;
    }

    return romfsMountCommon(name, mount);
}

int32_t romfsMountCommon(const char *name, romfs_mount *mount) {
    memset(mount->name, 0, sizeof(mount->name));
    strncpy(mount->name, name, sizeof(mount->name) - 1);

    romfsInitMtime(mount);

    if (_romfs_read(mount, 0, &mount->header, sizeof(mount->header)) != sizeof(mount->header))
        goto fail_io;

    mount->dirHashTable = (uint32_t *) malloc(mount->header.dirHashTableSize);
    if (!mount->dirHashTable)
        goto fail_oom;
    if (!_romfs_read_chk(mount, mount->header.dirHashTableOff, mount->dirHashTable, mount->header.dirHashTableSize))
        goto fail_io;

    mount->dirTable = malloc(mount->header.dirTableSize);
    if (!mount->dirTable)
        goto fail_oom;
    if (!_romfs_read_chk(mount, mount->header.dirTableOff, mount->dirTable, mount->header.dirTableSize))
        goto fail_io;

    mount->fileHashTable = (uint32_t *) malloc(mount->header.fileHashTableSize);
    if (!mount->fileHashTable)
        goto fail_oom;
    if (!_romfs_read_chk(mount, mount->header.fileHashTableOff, mount->fileHashTable, mount->header.fileHashTableSize))
        goto fail_io;

    mount->fileTable = malloc(mount->header.fileTableSize);
    if (!mount->fileTable)
        goto fail_oom;
    if (!_romfs_read_chk(mount, mount->header.fileTableOff, mount->fileTable, mount->header.fileTableSize))
        goto fail_io;

    mount->cwd = romFS_root(mount);

    if (AddDevice(&mount->device) < 0)
        goto fail_oom;

    mount->setup = true;
    return 0;

    fail_oom:
    romfs_mountclose(mount);
    return 9;

    fail_io:
    romfs_mountclose(mount);
    return 10;
}

static void romfsInitMtime(romfs_mount *mount) {
    mount->mtime = time(NULL);
}

int32_t romfsUnmount(const char *name) {
    romfs_mount *mount;
    char tmpname[34];

    mount = romfsFindMount(name);
    if (mount == NULL)
        return -1;

    // Remove device
    memset(tmpname, 0, sizeof(tmpname));
    strncpy(tmpname, mount->name, sizeof(tmpname) - 2);
    strncat(tmpname, ":", sizeof(tmpname) - strlen(tmpname) - 1);

    RemoveDevice(tmpname);

    romfs_mountclose(mount);

    return 0;
}

//-----------------------------------------------------------------------------

static uint32_t calcHash(uint32_t parent, const uint8_t *name, uint32_t namelen, uint32_t total) {
    uint32_t hash = parent ^123456789;
    uint32_t i;
    for (i = 0; i < namelen; i++) {
        hash = (hash >> 5) | (hash << 27);
        hash ^= name[i];
    }
    return hash % total;
}

static int searchForDir(romfs_mount *mount, romfs_dir *parent, const uint8_t *name, uint32_t namelen, romfs_dir **out) {
    uint64_t parentOff = (uintptr_t) parent - (uintptr_t) mount->dirTable;
    uint32_t hash = calcHash(parentOff, name, namelen, mount->header.dirHashTableSize / 4);
    romfs_dir *curDir = NULL;
    uint32_t curOff;
    *out = NULL;
    for (curOff = mount->dirHashTable[hash]; curOff != romFS_none;
    curOff = curDir->nextHash) {
        curDir = romFS_dir(mount, curOff);
        if (curDir == NULL) return EFAULT;
        if (curDir->parent != parentOff)
            continue;
        if (curDir->nameLen != namelen)
            continue;
        if (memcmp(curDir->name, name, namelen) != 0)
            continue;
        *out = curDir;
        return 0;
    }
    return ENOENT;
}

static int searchForFile(romfs_mount *mount, romfs_dir *parent, const uint8_t *name, uint32_t namelen, romfs_file **out) {
    uint64_t parentOff = (uintptr_t) parent - (uintptr_t) mount->dirTable;
    uint32_t hash = calcHash(parentOff, name, namelen, mount->header.fileHashTableSize / 4);
    romfs_file *curFile = NULL;
    uint32_t curOff;
    *out = NULL;
    for (curOff = mount->fileHashTable[hash]; curOff != romFS_none;
    curOff = curFile->nextHash) {
        curFile = romFS_file(mount, curOff);
        if (curFile == NULL)
            return EFAULT;
        if (curFile->parent != parentOff)
            continue;
        if (curFile->nameLen != namelen)
            continue;
        if (memcmp(curFile->name, name, namelen) != 0)
            continue;
        *out = curFile;
        return 0;
    }
    return ENOENT;
}

static int navigateToDir(romfs_mount *mount, romfs_dir **ppDir, const char **pPath, bool isDir) {
    char *colonPos = strchr(*pPath, ':');
    if (colonPos) *pPath = colonPos + 1;
    if (!**pPath)
        return EILSEQ;

    *ppDir = mount->cwd;
    if (**pPath == '/') {
        *ppDir = romFS_root(mount);
        (*pPath)++;
    }

    while (**pPath) {
        char *slashPos = strchr(*pPath, '/');
        char *component = __component;

        if (slashPos) {
            uint32_t len = slashPos - *pPath;
            if (!len)
                return EILSEQ;
            if (len > PATH_MAX)
                return ENAMETOOLONG;

            memcpy(component, *pPath, len);
            component[len] = 0;
            *pPath = slashPos + 1;
        } else if (isDir) {
            component = (char *) *pPath;
            *pPath += strlen(component);
        } else
            return 0;

        if (component[0] == '.') {
            if (!component[1]) continue;
            if (component[1] == '.' && !component[2]) {
                *ppDir = romFS_dir(mount, (*ppDir)->parent);
                if (!*ppDir)
                    return EFAULT;
                continue;
            }
        }

        int ret = searchForDir(mount, *ppDir, (uint8_t *) component, strlen(component), ppDir);
        if (ret != 0)
            return ret;
    }

    return 0;
}

static ino_t dir_inode(romfs_mount *mount, romfs_dir *dir) {
    return (uint32_t *) dir - (uint32_t *) mount->dirTable;
}

static off_t dir_size(romfs_dir *dir) {
    return sizeof(romfs_dir) + (dir->nameLen + 3) / 4;
}

static nlink_t dir_nlink(romfs_mount *mount, romfs_dir *dir) {
    nlink_t count = 2; // one for self, one for parent
    uint32_t offset = dir->childDir;

    while (offset != romFS_none) {
        romfs_dir *tmp = romFS_dir(mount, offset);
        if (!tmp) break;
        ++count;
        offset = tmp->sibling;
    }

    offset = dir->childFile;
    while (offset != romFS_none) {
        romfs_file *tmp = romFS_file(mount, offset);
        if (!tmp) break;
        ++count;
        offset = tmp->sibling;
    }

    return count;
}

static ino_t file_inode(romfs_mount *mount, romfs_file *file) {
    return ((uint32_t *) file - (uint32_t *) mount->fileTable) + mount->header.dirTableSize / 4;
}

int romfs_GetFileInfoPerPath(const char *romfs, const char *path, romfs_fileInfo *out) {
    if (out == NULL) {
        return -1;
    }
    romfs_mount *mount = (romfs_mount *) romfsFindMount(romfs);
    if (mount == NULL) {
        return -2;
    }
    romfs_dir *curDir = NULL;
    int errno2 = navigateToDir(mount, &curDir, &path, false);
    if (errno2 != 0) {
        return -3;
    }
    romfs_file* file = NULL;
    int err = searchForFile(mount, curDir, (uint8_t *) path, strlen(path), &file);
    if (err != 0) {
        return -4;
    }

    out->length = file->dataSize;
    out->offset = mount->header.fileDataOff + file->dataOff;

    return 0;
}


//-----------------------------------------------------------------------------

int romfs_open(struct _reent *r, void *fileStruct, const char *path, int flags, int mode) {
    romfs_fileobj *fileobj = (romfs_fileobj *) fileStruct;

    fileobj->mount = (romfs_mount *) r->deviceData;

    if ((flags & O_ACCMODE) != O_RDONLY) {
        r->_errno = EROFS;
        return -1;
    }

    romfs_dir *curDir = NULL;
    r->_errno = navigateToDir(fileobj->mount, &curDir, &path, false);
    if (r->_errno != 0)
        return -1;

    romfs_file *file = NULL;
    int ret = searchForFile(fileobj->mount, curDir, (uint8_t *) path, strlen(path), &file);
    if (ret != 0) {
        if (ret == ENOENT && (flags & O_CREAT))
            r->_errno = EROFS;
        else
            r->_errno = ret;
        return -1;
    } else if ((flags & O_CREAT) && (flags & O_EXCL)) {
        r->_errno = EEXIST;
        return -1;
    }

    fileobj->file = file;
    fileobj->offset = fileobj->mount->header.fileDataOff + file->dataOff;
    fileobj->pos = 0;

    return 0;
}

int romfs_close(struct _reent *r, void *fd) {
    return 0;
}

ssize_t romfs_read(struct _reent *r, void *fd, char *ptr, size_t len) {
    romfs_fileobj *file = (romfs_fileobj *) fd;
    uint64_t endPos = file->pos + len;

    /* check if past end-of-file */
    if (file->pos >= file->file->dataSize)
        return 0;

    /* truncate the read to end-of-file */
    if (endPos > file->file->dataSize)
        endPos = file->file->dataSize;
    len = endPos - file->pos;

    ssize_t adv = _romfs_read(file->mount, file->offset + file->pos, ptr, len);
    if (adv >= 0) {
        file->pos += adv;
        return adv;
    }

    r->_errno = EIO;
    return -1;
}

off_t romfs_seek(struct _reent *r, void *fd, off_t pos, int dir) {
    romfs_fileobj *file = (romfs_fileobj *) fd;
    off_t start;
    switch (dir) {
        case SEEK_SET:
            start = 0;
            break;

        case SEEK_CUR:
            start = file->pos;
            break;

        case SEEK_END:
            start = file->file->dataSize;
            break;

        default:
            r->_errno = EINVAL;
            return -1;
    }

    /* don't allow negative position */
    if (pos < 0) {
        if (start + pos < 0) {
            r->_errno = EINVAL;
            return -1;
        }
    }
        /* check for overflow */
    else if (INT64_MAX - pos < start) {
        r->_errno = EOVERFLOW;
        return -1;
    }

    file->pos = start + pos;
    return file->pos;
}

static void fillDir(struct stat *st, romfs_mount *mount, romfs_dir *dir) {
    memset(st, 0, sizeof(*st));
    st->st_ino = dir_inode(mount, dir);
    st->st_mode = romFS_dir_mode;
    st->st_nlink = dir_nlink(mount, dir);
    st->st_size = dir_size(dir);
    st->st_blksize = 512;
    st->st_blocks = (st->st_blksize + 511) / 512;
    st->st_atime = st->st_mtime = st->st_ctime = mount->mtime;
}

static void fillFile(struct stat *st, romfs_mount *mount, romfs_file *file) {
    memset(st, 0, sizeof(struct stat));
    st->st_ino = file_inode(mount, file);
    st->st_mode = romFS_file_mode;
    st->st_nlink = 1;
    st->st_size = (off_t) file->dataSize;
    st->st_blksize = 512;
    st->st_blocks = (st->st_blksize + 511) / 512;
    st->st_atime = st->st_mtime = st->st_ctime = mount->mtime;
}

int romfs_fstat(struct _reent *r, void *fd, struct stat *st) {
    romfs_fileobj *fileobj = (romfs_fileobj *) fd;
    fillFile(st, fileobj->mount, fileobj->file);

    return 0;
}

int romfs_stat(struct _reent *r, const char *path, struct stat *st) {
    romfs_mount *mount = (romfs_mount *) r->deviceData;
    romfs_dir *curDir = NULL;
    r->_errno = navigateToDir(mount, &curDir, &path, false);
    if (r->_errno != 0)
        return -1;

    if (!*path) {
        fillDir(st, mount, curDir);
        return 0;
    }

    romfs_dir *dir = NULL;
    int ret = 0;
    ret = searchForDir(mount, curDir, (uint8_t *) path, strlen(path), &dir);
    if (ret != 0 && ret != ENOENT) {
        r->_errno = ret;
        return -1;
    }
    if (ret == 0) {
        fillDir(st, mount, dir);

        return 0;
    }

    romfs_file *file = NULL;
    ret = searchForFile(mount, curDir, (uint8_t *) path, strlen(path), &file);
    if (ret != 0 && ret != ENOENT) {
        r->_errno = ret;
        return -1;
    }
    if (ret == 0) {
        fillFile(st, mount, file);
        return 0;
    }

    r->_errno = ENOENT;
    return 1;
}

int romfs_chdir(struct _reent *r, const char *path) {
    romfs_mount *mount = (romfs_mount *) r->deviceData;
    romfs_dir *curDir = NULL;
    r->_errno = navigateToDir(mount, &curDir, &path, true);
    if (r->_errno != 0)
        return -1;

    mount->cwd = curDir;
    return 0;
}

DIR_ITER *romfs_diropen(struct _reent *r, DIR_ITER *dirState, const char *path) {
    romfs_diriter *iter = (romfs_diriter *) (dirState->dirStruct);
    romfs_dir *curDir = NULL;
    iter->mount = (romfs_mount *) r->deviceData;

    r->_errno = navigateToDir(iter->mount, &curDir, &path, true);
    if (r->_errno != 0)
        return NULL;

    iter->dir = curDir;
    iter->state = 0;
    iter->childDir = curDir->childDir;
    iter->childFile = curDir->childFile;

    return dirState;
}

int romfs_dirreset(struct _reent *r, DIR_ITER *dirState) {
    romfs_diriter *iter = (romfs_diriter *) (dirState->dirStruct);

    iter->state = 0;
    iter->childDir = iter->dir->childDir;
    iter->childFile = iter->dir->childFile;

    return 0;
}

int romfs_dirnext(struct _reent *r, DIR_ITER *dirState, char *filename, struct stat *filestat) {
    romfs_diriter *iter = (romfs_diriter *) (dirState->dirStruct);

    if (iter->state == 0) {
        /* '.' entry */
        memset(filestat, 0, sizeof(*filestat));
        filestat->st_ino = dir_inode(iter->mount, iter->dir);
        filestat->st_mode = romFS_dir_mode;

        strcpy(filename, ".");
        iter->state = 1;
        return 0;
    } else if (iter->state == 1) {
        /* '..' entry */
        romfs_dir *dir = romFS_dir(iter->mount, iter->dir->parent);
        if (!dir) {
            r->_errno = EFAULT;
            return -1;
        }

        memset(filestat, 0, sizeof(*filestat));
        filestat->st_ino = dir_inode(iter->mount, dir);
        filestat->st_mode = romFS_dir_mode;

        strcpy(filename, "..");
        iter->state = 2;
        return 0;
    }

    if (iter->childDir != romFS_none) {
        romfs_dir *dir = romFS_dir(iter->mount, iter->childDir);
        if (!dir) {
            r->_errno = EFAULT;
            return -1;
        }

        iter->childDir = dir->sibling;

        memset(filestat, 0, sizeof(*filestat));
        filestat->st_ino = dir_inode(iter->mount, dir);
        filestat->st_mode = romFS_dir_mode;

        memset(filename, 0, NAME_MAX);

        if (dir->nameLen >= NAME_MAX) {
            r->_errno = ENAMETOOLONG;
            return -1;
        }

        strncpy(filename, (char *) dir->name, dir->nameLen);

        return 0;
    } else if (iter->childFile != romFS_none) {
        romfs_file *file = romFS_file(iter->mount, iter->childFile);
        if (!file) {
            r->_errno = EFAULT;
            return -1;
        }

        iter->childFile = file->sibling;

        memset(filestat, 0, sizeof(*filestat));
        filestat->st_ino = file_inode(iter->mount, file);
        filestat->st_mode = romFS_file_mode;

        memset(filename, 0, NAME_MAX);

        if (file->nameLen >= NAME_MAX) {
            r->_errno = ENAMETOOLONG;
            return -1;
        }

        strncpy(filename, (char *) file->name, file->nameLen);

        return 0;
    }

    r->_errno = ENOENT;
    return -1;
}

int romfs_dirclose(struct _reent *r, DIR_ITER *dirState) {
    return 0;
}


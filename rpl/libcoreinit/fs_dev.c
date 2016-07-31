#include <wut.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/dirent.h>
#include <sys/iosupport.h>
#include <sys/param.h>
#include <unistd.h>

#include <coreinit/filesystem.h>

static int fs_translate_error(FSStatus error);

static int       fs_open(struct _reent *r, void *fileStruct, const char *path, int flags, int mode);
static int       fs_close(struct _reent *r, int fd);
static ssize_t   fs_write(struct _reent *r, int fd, const char *ptr, size_t len);
static ssize_t   fs_write_safe(struct _reent *r, int fd, const char *ptr, size_t len);
static ssize_t   fs_read(struct _reent *r, int fd, char *ptr, size_t len);
static off_t     fs_seek(struct _reent *r, int fd, off_t pos, int dir);
static int       fs_fstat(struct _reent *r, int fd, struct stat *st);
static int       fs_stat(struct _reent *r, const char *file, struct stat *st);
static int       fs_link(struct _reent *r, const char *existing, const char  *newLink);
static int       fs_unlink(struct _reent *r, const char *name);
static int       fs_chdir(struct _reent *r, const char *name);
static int       fs_rename(struct _reent *r, const char *oldName, const char *newName);
static int       fs_mkdir(struct _reent *r, const char *path, int mode);
static DIR_ITER* fs_diropen(struct _reent *r, DIR_ITER *dirState, const char *path);
static int       fs_dirreset(struct _reent *r, DIR_ITER *dirState);
static int       fs_dirnext(struct _reent *r, DIR_ITER *dirState, char *filename, struct stat *filestat);
static int       fs_dirclose(struct _reent *r, DIR_ITER *dirState);
static int       fs_statvfs(struct _reent *r, const char *path, struct statvfs *buf);
static int       fs_ftruncate(struct _reent *r, int fd, off_t len);
static int       fs_fsync(struct _reent *r, int fd);
static int       fs_chmod(struct _reent *r, const char *path, mode_t mode);
static int       fs_fchmod(struct _reent *r, int fd, mode_t mode);
static int       fs_rmdir(struct _reent *r, const char *name);

/* Open file struct */
typedef struct
{
  FSFileHandle fd;     /* FS handle */
  int          flags;  /* Flags used in open(2) */
 uint32_t     offset; /* Current file offset */
} fs_file_t;

#define FS_DIRITER_MAGIC 0x77696975 /* "wiiu" */

/* Open directory struct */
typedef struct
{
  u32                     magic;
  FSDirectoryHandle       fd;             /* FS handle */
  FSDirectoryEntry entry_data; /* Temporary storage for reading entries */
} fs_dir_t;

/* Wii U FS devoptab */
static devoptab_t
fs_devoptab =
{
  .name         = "fs",
  .structSize   = sizeof(fs_file_t),
  .open_r       = fs_open,
  .close_r      = fs_close,
  .write_r      = fs_write_safe,
  .read_r       = fs_read,
  .seek_r       = fs_seek,
  .fstat_r      = fs_fstat,
  .stat_r       = fs_stat,
  .link_r       = fs_link,
  .unlink_r     = fs_unlink,
  .chdir_r      = fs_chdir,
  .rename_r     = fs_rename,
  .mkdir_r      = fs_mkdir,
  .dirStateSize = sizeof(fs_dir_t),
  .diropen_r    = fs_diropen,
  .dirreset_r   = fs_dirreset,
  .dirnext_r    = fs_dirnext,
  .dirclose_r   = fs_dirclose,
  .statvfs_r    = fs_statvfs,
  .ftruncate_r  = fs_ftruncate,
  .fsync_r      = fs_fsync,
  .deviceData   = NULL,
  .chmod_r      = fs_chmod,
  .fchmod_r     = fs_fchmod,
  //.rmdir_r      = fs_rmdir,
};

/* FS structs */
void *fsClient;
void *fsCmd;

static bool sdmcInitialised = false;

/* Initialize SDMC device */
FSStatus fsDevInit(void)
{
  FSStatus   rc = 0;

  if(sdmcInitialised)
    return rc;
    
  fsClient = memalign(0x20, 0x1700);
  fsCmd    = memalign(0x20, 0xA80);
  u8 mountSource[0x300];
  char mountPath[0x80];
  char workDir[0x83];

  FSInit();
  rc = FSAddClient(fsClient, -1);
  if(rc < 0)
  {
    free(fsClient);
    free(fsCmd);
    return rc;
  }
        
  FSInitCmdBlock(fsCmd);
    
  // Mount the SD card
  rc = FSGetMountSource(fsClient, fsCmd, FS_MOUNT_SOURCE_SD, (void*)mountSource, -1);
  if(rc < 0) 
    return rc;
    
  rc = FSMount(fsClient, fsCmd, (void*)mountSource, mountPath, 0x80, -1);
  
  if(rc >= 0)
  { 
    sdmcInitialised = true;

    int dev = AddDevice(&fs_devoptab);

    if(dev != -1)
    {
      setDefaultDevice(dev);
      
      // chdir to SD root for general use
      strcpy(workDir, "fs:");
      strcat(workDir, mountPath);
      chdir(workDir);
    }
  }

  

  return rc;
}

static char*
fs_fixpath(struct _reent *r,
             const char    *path)
{
  char *p = strchr(path, ':')+1;
  char *__fixedpath = memalign(0x40, PATH_MAX+1);
  
  if(__fixedpath == NULL)
    return NULL;
  
  if(!strchr(path, ':'))
    p = (char*)path;

  // cwd is handled by coreinit, so just strip the 'fs:' if it exists
  strcpy(__fixedpath, p);

  if(__fixedpath[PATH_MAX] != 0)
  {
    __fixedpath[PATH_MAX] = 0;
    r->_errno = ENAMETOOLONG;
    return NULL;
  }

  return __fixedpath;
}

void fsWriteSafe(bool enable)
{
  if(enable)
    fs_devoptab.write_r = fs_write_safe;
  else
    fs_devoptab.write_r = fs_write;
}

FSStatus fsDevExit(void)
{
  FSStatus rc = 0;

  if(!sdmcInitialised) return rc;

  FSDelClient(fsClient, -1);
  free(fsClient);
  free(fsCmd);

  return rc;
}

static int
fs_open(struct _reent *r,
          void          *fileStruct,
          const char    *path,
          int           flags,
          int           mode)
{
  FSFileHandle  fd;
  FSStatus      rc;

  if(path == NULL)
    return -1;
    
  char *path_fixed = fs_fixpath(r,path);
  if(!path_fixed) 
  {
    r->_errno = ENOMEM;
    return -1;
  }

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fileStruct;
  const char *fs_mode;

  // Map flags to open modes
  if(flags == 0)
  {
    fs_mode = "r";
  }
  else if(flags == 2)
  {
    fs_mode = "r+";
  }
  else if(flags == 0x601)
  {
    fs_mode = "w";
  }
  else if(flags == 0x602)
  {
    fs_mode = "w+";
  }
  else if(flags == 0x209)
  {
    fs_mode = "a";
  }
  else if(flags == 0x20A)
  {
    fs_mode = "a+";
  }
  else
  {
    free(path_fixed);
    r->_errno = EINVAL;
    return -1;
  }

  /* set attributes */
  /*if(!(mode & S_IWUSR))
    attributes |= FS_ATTRIBUTE_READONLY;*/

  /* open the file */
  rc = FSOpenFile(fsClient, fsCmd, path_fixed, fs_mode, &fd, -1);
  if(rc >= 0)
  {
    file->fd     = fd;
    file->flags  = (flags & (O_ACCMODE|O_APPEND|O_SYNC));
    FSGetPosFile(fsClient, fsCmd, fd, &file->offset, -1);
    free(path_fixed);
    return 0;
  }

  free(path_fixed);
  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_close(struct _reent *r,
           int           fd)
{
  FSStatus    rc;

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fd;

  rc = FSCloseFile(fsClient, fsCmd, file->fd, -1);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static ssize_t
fs_write(struct _reent *r,
           int           fd,
           const char    *ptr,
           size_t        len)
{
  FSStatus    rc;
  u32         bytes, bytesWritten = 0;

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fd;

  /* check that the file was opened with write access */
  if((file->flags & O_ACCMODE) == O_RDONLY)
  {
    r->_errno = EBADF;
    return -1;
  }

  // Copy to internal buffer and write in chunks.
  u8 *tmp_buffer = memalign(0x40, 8192);
  while(len > 0)
  {
    size_t toWrite = len;
    if(toWrite > sizeof(tmp_buffer))
      toWrite = sizeof(tmp_buffer);

    /* copy to internal buffer */
    memcpy(tmp_buffer, ptr, toWrite);

    /* write the data */
    rc = FSWriteFile(fsClient, fsCmd, tmp_buffer, 1, toWrite, file->fd, 0, -1);
    if(rc < 0)
    {
      free(tmp_buffer);
    
      /* return partial transfer */
      if(bytesWritten > 0)
        return bytesWritten;

      r->_errno = fs_translate_error(rc);
      return -1;
    }
    else
      bytes = rc;

    file->offset += bytes;
    bytesWritten += bytes;
    ptr          += bytes;
    len          -= bytes;
  }
  free(tmp_buffer);

  return bytesWritten;
}

static ssize_t
fs_write_safe(struct _reent *r,
                int           fd,
                const char    *ptr,
                size_t        len)
{
  FSStatus    rc;
  u32         bytes, bytesWritten = 0;

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fd;

  /* check that the file was opened with write access */
  if((file->flags & O_ACCMODE) == O_RDONLY)
  {
    r->_errno = EBADF;
    return -1;
  }

  // Copy to internal buffer and write in chunks.
  u8 *tmp_buffer = memalign(0x40, 8192);
  while(len > 0)
  {
    size_t toWrite = len;
    if(toWrite > sizeof(tmp_buffer))
      toWrite = sizeof(tmp_buffer);

    /* copy to internal buffer */
    memcpy(tmp_buffer, ptr, toWrite);

    /* write the data */
    rc = FSWriteFile(fsClient, fsCmd, tmp_buffer, 1, toWrite, file->fd, 0, -1);
    if(rc < 0)
    {
      free(tmp_buffer);
    
      /* return partial transfer */
      if(bytesWritten > 0)
        return bytesWritten;

      r->_errno = fs_translate_error(rc);
      return -1;
    }
    else
      bytes = rc;

    file->offset += bytes;
    bytesWritten += bytes;
    ptr          += bytes;
    len          -= bytes;
  }
  free(tmp_buffer);

  return bytesWritten;
}

static ssize_t
fs_read(struct _reent *r,
          int           fd,
          char          *ptr,
          size_t         len)
{
  FSStatus    rc;
  u32         bytes, bytesRead = 0;

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fd;

  /* check that the file was opened with read access */
  if((file->flags & O_ACCMODE) == O_WRONLY)
  {
    r->_errno = EBADF;
    return -1;
  }
  
  FSStat fsstat;
  rc = FSGetStatFile(fsClient, fsCmd, file->fd, &fsstat, -1);
  if(rc < 0)
  {
    r->_errno = fs_translate_error(rc);
    return -1;
  }
  
  // Copy to internal buffer and read in chunks.
  u8 *tmp_buffer = memalign(0x40, 8192);
  while(len > 0)
  {
    size_t toRead = len;
    if(toRead > 8192)
      toRead = 8192;

    /* write the data */
    rc = FSReadFile(fsClient, fsCmd, tmp_buffer, 1, toRead, file->fd, 0, -1);
    
    if(rc <= 0)
    {
      free(tmp_buffer);
    
      /* return partial transfer */
      if(bytesRead > 0)
        return bytesRead;

      r->_errno = fs_translate_error(rc);
      return -1;
    }
    else
      bytes = rc;
      
    /* copy to internal buffer */
    memcpy(ptr, tmp_buffer, bytes);

    file->offset += bytes;
    bytesRead    += bytes;
    ptr          += bytes;
    len          -= bytes;
  }
  free(tmp_buffer);

  return bytesRead;
}

static off_t
fs_seek(struct _reent *r,
          int           fd,
          off_t         pos,
          int           whence)
{
  FSStatus    rc;
  u64         offset;

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fd;
  
  FSStat fsstat;
  rc = FSGetStatFile(fsClient, fsCmd, file->fd, &fsstat, -1);
  if(rc < 0)
  {
    r->_errno = fs_translate_error(rc);
    return -1;
  }

  /* find the offset to see from */
  switch(whence)
  {
    /* set absolute position; start offset is 0 */
    case SEEK_SET:
      offset = 0;
      break;

    /* set position relative to the current position */
    case SEEK_CUR:
      offset = file->offset;
      break;

    /* set position relative to the end of the file */
    case SEEK_END:
      offset = fsstat.size;
      break;

    /* an invalid option was provided */
    default:
      r->_errno = EINVAL;
      return -1;
  }

  /* TODO: A better check that prevents overflow. */
  if(pos < 0 && offset < -pos)
  {
    /* don't allow seek to before the beginning of the file */
    r->_errno = EINVAL;
    return -1;
  }

  /* update the current offset */
  file->offset = offset + pos;
  FSStatus result = FSSetPosFile(fsClient, fsCmd, file->fd, file->offset, -1);
  if(result < 0)
    return result;
  
  return file->offset;
}

static int
fs_fstat(struct _reent *r,
           int           fd,
           struct stat   *st)
{
  FSStatus    rc;
  fs_file_t *file = (fs_file_t*)fd;

  FSStat fsstat;
  rc = FSGetStatFile(fsClient, fsCmd, file->fd, &fsstat, -1);
  if(rc >= 0)
  {
    memset(st, 0, sizeof(struct stat));
    st->st_size = fsstat.size;
    st->st_uid = fsstat.owner;
    st->st_gid = fsstat.group;
    st->st_nlink = 1;
    st->st_mode = fsstat.mode;
    return 0;
  }

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_stat(struct _reent *r,
          const char    *file,
          struct stat   *st)
{
  int      fd;
  FSStatus rc;

  if(file == NULL)
    return -1;

  if((rc = FSOpenFile(fsClient, fsCmd, file, "r", (FSFileHandle*)&fd, -1)) >= 0)
  {
    fs_file_t tmpfd = { .fd = fd };
    rc = fs_fstat(r, (int)&tmpfd, st);
    FSCloseFile(fsClient, fsCmd, fd, -1);

    return rc;
  }
  else if((rc = FSOpenDir(fsClient, fsCmd, file, (FSDirectoryHandle*)&fd, -1)) >= 0)
  {
    memset(st, 0, sizeof(struct stat));
    st->st_nlink = 1;
    st->st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO;
    FSCloseDir(fsClient, fsCmd, fd, -1);
    return 0;
  }

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_link(struct _reent *r,
          const char    *existing,
          const char    *newLink)
{
  r->_errno = ENOSYS;
  return -1;
}

static int
fs_unlink(struct _reent *r,
            const char    *name)
{
  FSStatus  rc;

  if(name == NULL)
    return -1;

  rc = FSRemove(fsClient, fsCmd, name, -1);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_chdir(struct _reent *r,
           const char    *name)
{
  FSStatus  rc;

  if(name == NULL)
    return -1;
    
  char *path = fs_fixpath(r, name);
  if(!path) 
  {
    r->_errno = ENOMEM;
    return -1;
  }

  rc = FSChangeDir(fsClient, fsCmd, path, -1);
  free(path);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_rename(struct _reent *r,
            const char    *oldName,
            const char    *newName)
{
  FSStatus  rc;

  if(oldName == NULL)
    return -1;

  if(newName == NULL)
    return -1;
    
  char *path_old = fs_fixpath(r, oldName);
  if(!path_old) 
  {
    r->_errno = ENOMEM;
    return -1;
  }
  
  char *path_new = fs_fixpath(r, newName);
  if(!path_new) 
  {
    r->_errno = ENOMEM;
    return -1;
  }

  rc = FSRename(fsClient, fsCmd, path_old, path_new, -1);
  free(path_old);
  free(path_new);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_mkdir(struct _reent *r,
           const char    *path,
           int           mode)
{
  FSError  rc;

  if(path == NULL)
    return -1;
    
  char *path_fix = fs_fixpath(r, path);
  if(!path_fix) 
  {
    r->_errno = ENOMEM;
    return -1;
  }

  /* TODO: Use mode to set directory attributes. */

  rc = FSMakeDir(fsClient, fsCmd, path_fix, -1);
  free(path_fix);
  if(rc == FS_ERROR_ALREADY_EXISTS)
  {
    r->_errno = EEXIST;
    return -1;
  }
  else if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static DIR_ITER*
fs_diropen(struct _reent *r,
             DIR_ITER      *dirState,
             const char    *path)
{
  FSDirectoryHandle  fd;
  FSStatus           rc;

  if(path == NULL)
    return NULL;
    
  char *path_fixed = fs_fixpath(r,path);
  if(!path_fixed) 
  {
    r->_errno = ENOMEM;
    return NULL;
  }

  /* get pointer to our data */
  fs_dir_t *dir = (fs_dir_t*)(dirState->dirStruct);

  /* open the directory */
  rc = FSOpenDir(fsClient, fsCmd, path_fixed, &fd, -1);
  if(rc >= 0)
  {
    dir->magic = FS_DIRITER_MAGIC;
    dir->fd    = fd;
    memset(&dir->entry_data, 0, sizeof(dir->entry_data));
    free(path_fixed);
    return dirState;
  }

  free(path_fixed);
  r->_errno = fs_translate_error(rc);
  return NULL;
}

static int
fs_dirreset(struct _reent *r,
              DIR_ITER      *dirState)
{
  FSStatus  rc;

  /* get pointer to our data */
  fs_dir_t *dir = (fs_dir_t*)(dirState->dirStruct);

  /* rewind the directory */
  rc = FSRewindDir(fsClient, fsCmd, dir->fd, -1);
  if(rc >= 0)
  {
    return 0;
  }

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_dirnext(struct _reent *r,
             DIR_ITER      *dirState,
             char          *filename,
             struct stat   *filestat)
{
  FSStatus            rc;

  /* get pointer to our data */
  fs_dir_t *dir = (fs_dir_t*)(dirState->dirStruct);

  {
    /* fetch the next dir */
    memset(&dir->entry_data, 0, sizeof(dir->entry_data));
    rc = FSReadDir(fsClient, fsCmd, dir->fd, &dir->entry_data, -1);
    if(rc < 0)
    {
      /* there are no more entries; ENOENT signals end-of-directory */
      r->_errno = ENOENT;
      return -1;
    }
  }

  if(rc >= 0)
  {
    memset(filestat, 0, sizeof(struct stat));

    /* fill in the stat info */
    filestat->st_ino = 0;
    if(dir->entry_data.info.flags & FS_STAT_DIRECTORY)
      filestat->st_mode = S_IFDIR;
    else
      filestat->st_mode = S_IFREG;
      
    filestat->st_uid = dir->entry_data.info.owner;
    filestat->st_gid = dir->entry_data.info.group;
    filestat->st_size = dir->entry_data.info.size;

    memset(filename, 0, NAME_MAX);
    strcpy(filename, dir->entry_data.name);

    return 0;
  }

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_dirclose(struct _reent *r,
              DIR_ITER      *dirState)
{
  FSStatus       rc;

  /* get pointer to our data */
  fs_dir_t *dir = (fs_dir_t*)(dirState->dirStruct);

  /* close the directory */
  rc = FSCloseDir(fsClient, fsCmd, dir->fd, -1);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_statvfs(struct _reent  *r,
             const char     *path,
             struct statvfs *buf)
{
  FSStatus rc;
  bool writable = false;
  
  char *path_fix = fs_fixpath(r, path);
  if(!path_fix) 
  {
    r->_errno = ENOMEM;
    return -1;
  }

  /*rc = FSUSER_GetSdmcArchiveResource(&resource);

  if(rc >= 0)
  {
    buf->f_bsize   = resource.clusterSize;
    buf->f_frsize  = resource.clusterSize;
    buf->f_blocks  = resource.totalClusters;
    buf->f_bfree   = resource.freeClusters;
    buf->f_bavail  = resource.freeClusters;
    buf->f_files   = 0; //??? how to get
    buf->f_ffree   = resource.freeClusters;
    buf->f_favail  = resource.freeClusters;
    buf->f_fsid    = 0; //??? how to get
    buf->f_flag    = ST_NOSUID;
    buf->f_namemax = 0; //??? how to get

    rc = FSUSER_IsSdmcWritable(&writable);
    if(rc < 0 || !writable)
      buf->f_flag |= ST_RDONLY;

    return 0;
  }

  r->_errno = fs_translate_error(rc);
  return -1;*/
  
  //TODO
  
  free(path_fix);
  r->_errno = ENOSYS;
  return -1;
}

static int
fs_ftruncate(struct _reent *r,
               int           fd,
               off_t         len)
{
  FSStatus    rc;

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fd;

  /* make sure length is non-negative */
  if(len < 0)
  {
    r->_errno = EINVAL;
    return -1;
  }

  /* set the new file size */
  rc = FSSetPosFile(fsClient, fsCmd, file->fd, len, -1);
  if(rc >= 0)
    return 0;
  
  rc = FSTruncateFile(fsClient, fsCmd, file->fd, -1);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_fsync(struct _reent *r,
           int           fd)
{
  FSStatus rc;

  /* get pointer to our data */
  fs_file_t *file = (fs_file_t*)fd;

  rc = FSFlushFile(fsClient, fsCmd, file->fd, -1);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;
}

static int
fs_chmod(struct _reent *r,
          const char    *path,
          mode_t        mode)
{
  //TODO: FSChangeMode
  
  char *path_fix = fs_fixpath(r, path);
  if(!path_fix) 
  {
    r->_errno = ENOMEM;
    return -1;
  }
  
  free(path_fix);

  r->_errno = ENOSYS;
  return -1;
}

static int
fs_fchmod(struct _reent *r,
            int           fd,
            mode_t        mode)
{
  //TODO: FSChangeMode

  r->_errno = ENOSYS;
  return -1;
}

static int
fs_rmdir(struct _reent *r,
           const char    *name)
{
  char *path_fix = fs_fixpath(r, name);
  if(!path_fix) 
  {
    r->_errno = ENOMEM;
    return -1;
  }

  /*FSStatus  rc;

  if(name == NULL)
    return -1;

  rc = FSUSER_DeleteDirectory(sdmcArchive, fs_path);
  if(rc >= 0)
    return 0;

  r->_errno = fs_translate_error(rc);
  return -1;*/
  
  free(path_fix);
  r->_errno = ENOSYS;
  return -1;
}

int
fs_getmtime(const char *name,
              u64        *mtime)
{
  return -1;
}

/* Error map */
typedef struct
{
  FSStatus fs_error; //!< Error from FS service
  int      error;    //!< POSIX errno
} error_map_t;

/* Error table */
static const error_map_t error_table[] =
{
  /* keep this list sorted! */
  { FS_STATUS_CANCELLED,    EINVAL,       },
  { FS_STATUS_EXISTS,       EEXIST,       },
  { FS_STATUS_NOT_FOUND,    ENOENT,       },
  { FS_STATUS_STORAGE_FULL, ENOSPC,       },
  { FS_ERROR_INVALID_PATH,  ENAMETOOLONG, },
};
static const size_t num_errors = sizeof(error_table)/sizeof(error_table[0]);

static int
error_cmp(const void *p1, const void *p2)
{
  const error_map_t *lhs = (const error_map_t*)p1;
  const error_map_t *rhs = (const error_map_t*)p2;

  if((u32)lhs->fs_error < (u32)rhs->fs_error)
    return -1;
  else if((u32)lhs->fs_error > (u32)rhs->fs_error)
    return 1;
  return 0;
}

static int
fs_translate_error(FSStatus error)
{
  error_map_t key = { .fs_error = error };
  const error_map_t *rc = bsearch(&key, error_table, num_errors,
                                  sizeof(error_map_t), error_cmp);

  if(rc != NULL)
    return rc->error;

  return (int)error;
}

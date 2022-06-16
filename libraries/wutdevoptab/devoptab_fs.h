#pragma once
#include <coreinit/filesystem.h>

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

/**
 * Open file struct
 */
typedef struct
{
   //! FS handle
   FSFileHandle fd;

   //! Flags used in open(2)
   int flags;

   //! Current file offset
   uint32_t offset;
} __wut_fs_file_t;


/**
 * Open directory struct
 */
typedef struct
{
   //! Should be set to FS_DIRITER_MAGIC
   uint32_t magic;

   //! FS handle
   FSDirectoryHandle fd;

   //! Temporary storage for reading entries
   FSDirectoryEntry entry_data;
} __wut_fs_dir_t;

#define FS_DIRITER_MAGIC 0x77696975

extern FSClient *
__wut_devoptab_fs_client;

int       __wut_fs_open(struct _reent *r, void *fileStruct, const char *path,
                        int flags, int mode);
int       __wut_fs_close(struct _reent *r, void *fd);
ssize_t   __wut_fs_write(struct _reent *r, void *fd, const char *ptr,
                         size_t len);
ssize_t   __wut_fs_read(struct _reent *r, void *fd, char *ptr, size_t len);
off_t     __wut_fs_seek(struct _reent *r, void *fd, off_t pos, int dir);
int       __wut_fs_fstat(struct _reent *r, void *fd, struct stat *st);
int       __wut_fs_stat(struct _reent *r, const char *file, struct stat *st);
int       __wut_fs_link(struct _reent *r, const char *existing,
                        const char  *newLink);
int       __wut_fs_unlink(struct _reent *r, const char *name);
int       __wut_fs_chdir(struct _reent *r, const char *name);
int       __wut_fs_rename(struct _reent *r, const char *oldName,
                          const char *newName);
int       __wut_fs_mkdir(struct _reent *r, const char *path, int mode);
DIR_ITER* __wut_fs_diropen(struct _reent *r, DIR_ITER *dirState,
                           const char *path);
int       __wut_fs_dirreset(struct _reent *r, DIR_ITER *dirState);
int       __wut_fs_dirnext(struct _reent *r, DIR_ITER *dirState, char *filename,
                           struct stat *filestat);
int       __wut_fs_dirclose(struct _reent *r, DIR_ITER *dirState);
int       __wut_fs_statvfs(struct _reent *r, const char *path,
                           struct statvfs *buf);
int       __wut_fs_ftruncate(struct _reent *r, void *fd, off_t len);
int       __wut_fs_fsync(struct _reent *r, void *fd);
int       __wut_fs_chmod(struct _reent *r, const char *path, mode_t mode);
int       __wut_fs_fchmod(struct _reent *r, void *fd, mode_t mode);
int       __wut_fs_rmdir(struct _reent *r, const char *name);
int       __wut_fs_utimes(struct _reent *r, const char *filename, const struct timeval times[2]);

// devoptab_fs_utils.c
char *    __wut_fs_fixpath(struct _reent *r, const char *path);
int       __wut_fs_translate_error(FSStatus error);
time_t    __wut_fs_translate_time(FSTime timeValue);
mode_t    __wut_fs_translate_mode(FSStat fileStat);

#include "devoptab_fs.h"
#include "../wutnewlib/wut_clock.h"

char *
__wut_fs_fixpath(struct _reent *r,
                 const char *path) {
   char *p;
   char *fixedPath;

   if (!path) {
      r->_errno = EINVAL;
      return NULL;
   }

   p = strchr(path, ':') + 1;
   if (!strchr(path, ':')) {
      p = (char *) path;
   }

   size_t pathLength = strlen(p);
   if (pathLength > PATH_MAX) {
      r->_errno = ENAMETOOLONG;
      return NULL;
   }

   // wii u softlocks on empty strings so give expected error back
   if (pathLength == 0) {
      r->_errno = ENOENT;
      return NULL;
   }

   fixedPath = memalign(0x40, PATH_MAX + 1);
   if (!fixedPath) {
      r->_errno = ENOMEM;
      return NULL;
   }

   // cwd is handled by coreinit, so just strip the 'device:' if it exists
   strcpy(fixedPath, p);
   return fixedPath;
}

mode_t __wut_fs_translate_stat_mode(FSStat* fsStat) {
   mode_t retMode = 0;

   if ((fsStat->flags & FS_STAT_LINK) == FS_STAT_LINK) {
      retMode |= S_IFLNK;
   } else if ((fsStat->flags & FS_STAT_DIRECTORY) == FS_STAT_DIRECTORY) {
      retMode |= S_IFDIR;
   } else if ((fsStat->flags & FS_STAT_FILE) == FS_STAT_FILE) {
      retMode |= S_IFREG;
   } else if (fsStat->size == 0) {
      // Mounted paths like /vol/external01 have no flags set.
      // If no flag is set and the size is 0, it's a (root) dir
      retMode |= S_IFDIR;
   }  else if (fsStat->size > 0) {
      // Some regular Wii U files have no type info but will have a size
      retMode |= S_IFREG;
   }

   // Convert normal CafeOS hexadecimal permission bits into Unix octal permission bits
   mode_t permissionMode = (((fsStat->mode >> 2) & S_IRWXU) | ((fsStat->mode >> 1) & S_IRWXG) | (fsStat->mode & S_IRWXO));

   return retMode | permissionMode;
}

FSMode __wut_fs_translate_permission_mode(mode_t mode) {
   // Convert normal Unix octal permission bits into CafeOS hexadecimal permission bits
   return (FSMode) (((mode & S_IRWXU) << 2) | ((mode & S_IRWXG) << 1) | (mode & S_IRWXO));
}

time_t __wut_fs_translate_time(FSTime timeValue) {
   return (timeValue /1000000) + EPOCH_DIFF_SECS(WIIU_FSTIME_EPOCH_YEAR);
}

void __wut_fs_translate_FSStat(FSStat* fsStat, struct stat* posStat) {
   memset(posStat, 0, sizeof(struct stat));
   posStat->st_dev = (dev_t)__wut_devoptab_fs_client;
   posStat->st_ino = fsStat->entryId;
   posStat->st_mode = __wut_fs_translate_stat_mode(fsStat);
   posStat->st_nlink = 1;
   posStat->st_uid = fsStat->owner;
   posStat->st_gid = fsStat->group;
   posStat->st_rdev = posStat->st_dev;
   posStat->st_size = fsStat->size;
   posStat->st_atime = __wut_fs_translate_time(fsStat->modified);
   posStat->st_ctime = __wut_fs_translate_time(fsStat->created);
   posStat->st_mtime = __wut_fs_translate_time(fsStat->modified);
   posStat->st_blksize = 512;
   posStat->st_blocks = (posStat->st_size + posStat->st_blksize - 1) / posStat->st_size;
}

int
__wut_fs_translate_error(FSStatus error) {
   switch ((int) error) {
      case FS_STATUS_END:
         return ENOENT;
      case FS_STATUS_CANCELLED:
         return ECANCELED;
      case FS_STATUS_EXISTS:
         return EEXIST;
      case FS_STATUS_MEDIA_ERROR:
         return EIO;
      case FS_STATUS_NOT_FOUND:
         return ENOENT;
      case FS_STATUS_PERMISSION_ERROR:
         return EPERM;
      case FS_STATUS_STORAGE_FULL:
         return ENOSPC;
      case FS_STATUS_FILE_TOO_BIG:
         return EFBIG;
      case FS_STATUS_NOT_DIR:
         return ENOTDIR;
      case FS_STATUS_NOT_FILE:
         return EISDIR;
      case FS_STATUS_MAX:
         return ENFILE;
      case FS_STATUS_ACCESS_ERROR:
         return EACCES;
      case FS_STATUS_JOURNAL_FULL:
         return ENOSPC;
      case FS_STATUS_UNSUPPORTED_CMD:
         return ENOTSUP;
      case FS_STATUS_MEDIA_NOT_READY:
         return EOWNERDEAD;
      case FS_STATUS_ALREADY_OPEN:
      case FS_STATUS_CORRUPTED:
      case FS_STATUS_FATAL_ERROR:
         return EIO;
   }
   return (int) error;
}

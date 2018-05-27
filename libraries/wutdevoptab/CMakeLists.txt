cmake_minimum_required(VERSION 3.2)
project(wutdevoptab C)

add_library(wutdevoptab
   devoptab_fs.c
   devoptab_fs_chdir.c
   devoptab_fs_chmod.c
   devoptab_fs_close.c
   devoptab_fs_dirclose.c
   devoptab_fs_dirnext.c
   devoptab_fs_diropen.c
   devoptab_fs_dirreset.c
   devoptab_fs_fchmod.c
   devoptab_fs_fstat.c
   devoptab_fs_fsync.c
   devoptab_fs_getmtime.c
   devoptab_fs_link.c
   devoptab_fs_mkdir.c
   devoptab_fs_open.c
   devoptab_fs_read.c
   devoptab_fs_rename.c
   devoptab_fs_rmdir.c
   devoptab_fs_seek.c
   devoptab_fs_stat.c
   devoptab_fs_statvfs.c
   devoptab_fs_truncate.c
   devoptab_fs_unlink.c
   devoptab_fs_utils.c
   devoptab_fs_write.c)

target_include_directories(wutdevoptab PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutdevoptab
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

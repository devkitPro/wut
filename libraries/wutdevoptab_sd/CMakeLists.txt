cmake_minimum_required(VERSION 3.2)
project(wutdevoptab_sd C)

add_library(wutdevoptab_sd
   devoptab_sd.c
   devoptab_sd_chdir.c
   devoptab_sd_chmod.c
   devoptab_sd_close.c
   devoptab_sd_dirclose.c
   devoptab_sd_dirnext.c
   devoptab_sd_diropen.c
   devoptab_sd_dirreset.c
   devoptab_sd_fchmod.c
   devoptab_sd_fstat.c
   devoptab_sd_fsync.c
   devoptab_sd_getmtime.c
   devoptab_sd_link.c
   devoptab_sd_mkdir.c
   devoptab_sd_open.c
   devoptab_sd_read.c
   devoptab_sd_rename.c
   devoptab_sd_rmdir.c
   devoptab_sd_seek.c
   devoptab_sd_stat.c
   devoptab_sd_statvfs.c
   devoptab_sd_truncate.c
   devoptab_sd_unlink.c
   devoptab_sd_utils.c
   devoptab_sd_write.c)

target_include_directories(wutdevoptab_sd PRIVATE "${WUT_ROOT}/include")

install(TARGETS wutdevoptab_sd
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

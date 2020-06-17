/**
 * @file romfs_dev.h
 * @brief RomFS driver.
 * @author yellows8
 * @author mtheall
 * @author fincs
 * @copyright libnx Authors
 */
#pragma once

#include <wut.h>

/// RomFS header.
typedef struct {
    uint64_t headerSize;        ///< Size of the header.
    uint64_t dirHashTableOff;   ///< Offset of the directory hash table.
    uint64_t dirHashTableSize;  ///< Size of the directory hash table.
    uint64_t dirTableOff;       ///< Offset of the directory table.
    uint64_t dirTableSize;      ///< Size of the directory table.
    uint64_t fileHashTableOff;  ///< Offset of the file hash table.
    uint64_t fileHashTableSize; ///< Size of the file hash table.
    uint64_t fileTableOff;      ///< Offset of the file table.
    uint64_t fileTableSize;     ///< Size of the file table.
    uint64_t fileDataOff;       ///< Offset of the file data.
} romfs_header;

/// RomFS directory.
typedef struct {
    uint32_t parent;    ///< Offset of the parent directory.
    uint32_t sibling;   ///< Offset of the next sibling directory.
    uint32_t childDir;  ///< Offset of the first child directory.
    uint32_t childFile; ///< Offset of the first file.
    uint32_t nextHash;  ///< Directory hash table pointer.
    uint32_t nameLen;   ///< Name length.
    uint8_t name[];    ///< Name. (UTF-8)
} romfs_dir;

/// RomFS file.
typedef struct {
    uint32_t parent;   ///< Offset of the parent directory.
    uint32_t sibling;  ///< Offset of the next sibling file.
    uint64_t dataOff;  ///< Offset of the file's data.
    uint64_t dataSize; ///< Length of the file's data.
    uint32_t nextHash; ///< File hash table pointer.
    uint32_t nameLen;  ///< Name length.
    uint8_t name[];   ///< Name. (UTF-8)
} romfs_file;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mounts the Application's RomFS.
 * @param name Device mount name.
 */
int32_t romfsMount(const char *name, const char * path);


/**
 * @brief Mounts RomFS from an open file.
 * @param file FsFile of the RomFS image.
 * @param offset Offset of the RomFS within the file.
 * @param name Device mount name.
bool romfsMountFromFile(FsFile file, uint64_t offset, const char *name);
*/
/*
static inline bool romfsInitFromFile(int32_t fd, uint64_t offset) {
    return romfsMountFromFile(fd, offset, "romfs");
}*/

/// Unmounts the RomFS device.
int32_t romfsUnmount(const char *name);
/*
static inline bool romfsExit(void) {
    return romfsUnmount("romfs");
}*/

/// RomFS file.
typedef struct {
    uint64_t length;  ///< Offset of the file's data.
    uint64_t offset; ///< Length of the file's data.
} romfs_fileInfo;

int romfs_GetFileInfoPerPath(const char* romfs, const char *path, romfs_fileInfo* out);

#ifdef __cplusplus
}
#endif


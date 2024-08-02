#include <malloc.h>
#include <nn/idb/IDBReader.h>
#include <nn/idb/idb_cpp.h>
#include <sysapp/title.h>

namespace nn::idb {
    IDBReader::~IDBReader() {
        Finalize();
    }

    nn::Result IDBReader::LoadIconDataFromIdb(uint64_t titleId, IconDataRaw &iconData) const {
        if (!LoadIconData(titleId, 0xFFFFFFFF, iconData)) {
            return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
        }
        return {{0}};
    }

    bool IDBReader::SearchFromDataBase(IconDataKey &key, uint32_t &outIndex) const {
        if (!mInitDone) {
            return false;
        }
        int index = 0;
        for (const auto &entry : mFileHeader->entries) {
            if (entry.titleId == key.titleId && (entry.u1 == key.u1 || key.u1 == 0xFFFFFFFF)) {
                outIndex = index;
                return true;
            }
            index++;
        }
        return false;
    }

    bool IDBReader::LoadIconDataFromDatabase(uint32_t index, IconDataRaw &iconData) const {
        if (!mInitDone) {
            return false;
        }
        auto res = LoadFromFile(&iconData, sizeof(IconDataRaw), index * sizeof(IconDataRaw) + sizeof(FileHeader));
        return res == sizeof(IconDataRaw);
    }

    bool IDBReader::LoadIconData(uint64_t titleId, uint32_t u1, IconDataRaw &iconData) const {
        if (!mInitDone) {
            return false;
        }
        IconDataKey dataKey = {
                .titleId = titleId,
                .u1      = u1};
        uint32_t index;


        if (SearchFromDataBase(dataKey, index)) {
            return LoadIconDataFromDatabase(index, iconData);
        }
        return false;
    }

    bool IDBReader::Initialize(const std::string &path) {
        this->mPath = path;
        if (!mFileHeader) {
            mFileHeader = (FileHeader *) memalign(0x40, sizeof(*mFileHeader));
            if (!mFileHeader) {
                return false;
            }
        }

        if (!InitializeFile()) {
            Finalize();
            return false;
        }

        if (LoadFromFile(mFileHeader, sizeof(*mFileHeader), 0) != sizeof(*mFileHeader)) {
            Finalize();
            return false;
        }
        if (mFileHeader->version != 0) {
            Finalize();
            return false;
        }

        mInitDone = true;
        return true;
    }

    bool IDBReader::Initialize() {
        uint64_t menuTid = _SYSGetSystemApplicationTitleId(SYSTEM_APP_ID_WII_U_MENU);
        auto *menuTidPtr = (uint32_t *) &menuTid;
        char path[90];
        snprintf(path, sizeof(path), "fs:/vol/storage_mlc01/usr/save/%08X/%08X/user/common/BaristaIconDataBase.dat", menuTidPtr[0], menuTidPtr[1]);

        return Initialize(path);
    }

    void IDBReader::Finalize() {
        if (mFileHeader) {
            free(mFileHeader);
            mFileHeader = nullptr;
        }
        FinalizeFile();
        mInitDone = false;
    }

    bool IDBReader::InitializeFile() {
        if (!mFile) {
            mFile = fopen(mPath.c_str(), "r");
            if (!mFile) {
                return false;
            }
        }
        return true;
    }

    void IDBReader::FinalizeFile() {
        if (mFile) {
            fclose(mFile);
            mFile = nullptr;
        }
    }

    int IDBReader::LoadFromFile(void *buffer, uint32_t size, uint32_t offset) const {
        if (!mFile) {
            return 0;
        }
        size_t bytesRead;

        if (fseek(mFile, offset, SEEK_SET) != 0) {
            return false;
        }

        bytesRead = ::fread(buffer, 1, (size_t) size, mFile);

        if (bytesRead != size) {
            bytesRead = 0;
        }
        return bytesRead;
    }
} // namespace nn::idb
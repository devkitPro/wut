#pragma once

#include <coreinit/filesystem.h>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED IStreamInternal {
            void *vtable;
        } IStreamInternal;
        WUT_CHECK_SIZE(IStreamInternal, 0x04);

        typedef struct WUT_PACKED FileStreamInternal {
            WUT_UNKNOWN_BYTES(0x10);
        } FileStreamInternal;
        WUT_CHECK_SIZE(FileStreamInternal, 0x10);

        extern "C" nn::Result Initialize__Q3_2nn2sl10FileStreamFP8FSClientP10FSCmdBlockPCcT3(FileStreamInternal *, FSClient *, FSCmdBlock *, char const *, char const *);
        extern "C" FileStreamInternal *__ct__Q3_2nn2sl10FileStreamFv(FileStreamInternal *);
        extern "C" void __dt__Q3_2nn2sl10FileStreamFv(FileStreamInternal *, int);
    } // namespace details

    class IStream {
    public:
        virtual details::IStreamInternal *getStream() = 0;
    };

    class FileStream : public IStream {
    public:
        FileStream() {
            __ct__Q3_2nn2sl10FileStreamFv(&mInstance);
        }

        ~FileStream() {
            __dt__Q3_2nn2sl10FileStreamFv(&mInstance, 2);
        }

        nn::Result Initialize(FSClient *client, FSCmdBlock *cmdBlock, char const *path, char const *mode) {
            return Initialize__Q3_2nn2sl10FileStreamFP8FSClientP10FSCmdBlockPCcT3(&mInstance, client, cmdBlock, path, mode);
        }

        details::IStreamInternal *getStream() override {
            return reinterpret_cast<details::IStreamInternal *>(&mInstance);
        }

    private:
        details::FileStreamInternal mInstance = {};
    };

}; // namespace nn::sl

#endif
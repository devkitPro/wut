#pragma once

#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ISerializer;
    namespace details {
        struct ISerializeInternal;

        typedef nn::Result (*ISerializer_SerializeFn)(ISerializeInternal *, void *, uint32_t);
        typedef nn::Result (*ISerializer_DeserializeFn)(ISerializeInternal *, void *, uint32_t);
        typedef nn::Result (*ISerializer_GetCountFn)(ISerializeInternal *, uint32_t *);

        struct WUT_PACKED ISerializeInternalVTable {
            ISerializer *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            ISerializer_SerializeFn SerializeFn;
            WUT_PADDING_BYTES(4);
            ISerializer_DeserializeFn DeserializeFn;
            WUT_PADDING_BYTES(4);
            ISerializer_GetCountFn GetCountFn;
        };
        WUT_CHECK_SIZE(ISerializeInternalVTable, 0x28);
        WUT_CHECK_OFFSET(ISerializeInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(ISerializeInternalVTable, 0x14, SerializeFn);
        WUT_CHECK_OFFSET(ISerializeInternalVTable, 0x1C, DeserializeFn);
        WUT_CHECK_OFFSET(ISerializeInternalVTable, 0x24, GetCountFn);

        typedef struct WUT_PACKED ISerializeInternal {
            ISerializeInternalVTable *vtable;
        } ISerializeInternal;
        WUT_CHECK_SIZE(ISerializeInternal, 0x04);
        WUT_CHECK_OFFSET(ISerializeInternal, 0x00, vtable);

        extern "C" ISerializeInternal *GetDefaultIconInfoSerializer__Q2_2nn2slFv();
    } // namespace details


    class ISerializer {
        friend class DataCreator;

    public:
        ISerializer() = default;

        virtual ~ISerializer() = default;

        virtual nn::Result Serialize(void *buffer, uint32_t size) = 0;

        virtual nn::Result Deserialize(void *buffer, uint32_t size) = 0;

        virtual nn::Result GetCount(uint32_t *outCount) = 0;

    private:
        virtual details::ISerializeInternal *GetInternal() = 0;
    };

    class ISerializerBase : public ISerializer {

    public:
        ISerializerBase() {
            InitInternalVtable();
        }

        ISerializerBase(ISerializerBase &src) {
            InitInternalVtable();
        }

        ISerializerBase &operator=(const ISerializerBase &other) {
            InitInternalVtable();
            return *this;
        }

        ISerializerBase &operator=(ISerializerBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ISerializerBase() override = default;

    private:
        static nn::Result SerializeWrapper(details::ISerializeInternal *instance, void *buffer, uint32_t size) {
            return instance->vtable->instance->Serialize(buffer, size);
        }
        static nn::Result DeserializeWrapper(details::ISerializeInternal *instance, void *buffer, uint32_t size) {
            return instance->vtable->instance->Deserialize(buffer, size);
        }

        static nn::Result GetCountWrapper(details::ISerializeInternal *instance, uint32_t *outCount) {
            return instance->vtable->instance->GetCount(outCount);
        }

        details::ISerializeInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance      = this,
                                .SerializeFn   = &SerializeWrapper,
                                .DeserializeFn = &DeserializeWrapper,
                                .GetCountFn    = &GetCountWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ISerializeInternal mInstance{};
        details::ISerializeInternalVTable mVTable{};
    };

    class IconInfoSerializerFromPtr : public ISerializer {
    public:
        explicit IconInfoSerializerFromPtr(details::ISerializeInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Serialize(void *buffer, uint32_t size) override {
            return mInstancePtr->vtable->SerializeFn(mInstancePtr, buffer, size);
        }

        nn::Result Deserialize(void *buffer, uint32_t size) override {
            return mInstancePtr->vtable->DeserializeFn(mInstancePtr, buffer, size);
        }
        nn::Result GetCount(uint32_t *outCount) override {
            return mInstancePtr->vtable->GetCountFn(mInstancePtr, outCount);
        }

    private:
        details::ISerializeInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::ISerializeInternal *mInstancePtr;
    };

    IconInfoSerializerFromPtr GetDefaultIconInfoSerializer() {
        return IconInfoSerializerFromPtr(details::GetDefaultIconInfoSerializer__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif
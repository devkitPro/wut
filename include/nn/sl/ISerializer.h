#pragma once

#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    template<typename T>
    class ISerializer;

    namespace details {
        struct ISerializerInternal;

        typedef nn::Result (*ISerializer_SerializeFn)(ISerializerInternal *, void *, uint32_t);
        typedef nn::Result (*ISerializer_DeserializeFn)(ISerializerInternal *, void *, uint32_t);
        typedef nn::Result (*ISerializer_GetCountFn)(ISerializerInternal *, uint32_t *);

        struct WUT_PACKED ISerializerInternalVTable {
            ISerializer<uint8_t> *instance; // Is normally padding
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
        WUT_CHECK_SIZE(ISerializerInternalVTable, 0x28);
        WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x14, SerializeFn);
        WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x1C, DeserializeFn);
        WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x24, GetCountFn);

        typedef struct WUT_PACKED ISerializerInternal {
            ISerializerInternalVTable *vtable;
        } ISerializerInternal;
        WUT_CHECK_SIZE(ISerializerInternal, 0x04);
        WUT_CHECK_OFFSET(ISerializerInternal, 0x00, vtable);

    } // namespace details


    template<typename T>
    class ISerializer {
        friend class DataCreator;
        friend class CacheManager;
        friend class Condition;
        friend class KillerNotificationSelector;

    public:
        ISerializer() = default;

        virtual ~ISerializer() = default;

        virtual nn::Result Serialize(void *buffer, uint32_t size) = 0;

        virtual nn::Result Deserialize(void *buffer, uint32_t size) = 0;

        virtual nn::Result GetCount(uint32_t *outCount) = 0;

    private:
        virtual details::ISerializerInternal *GetInternal() = 0;
    };

    template<typename T>
    class ISerializerBase : public ISerializer<T> {

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

        nn::Result Serialize(T *buffer, uint32_t num) {
            return ISerializer<T>::Serialize(buffer, num * sizeof(buffer));
        }

        nn::Result Deserialize(T *buffer, uint32_t num) {
            return ISerializer<T>::Deserialize(buffer, num * sizeof(buffer));
        }

        ~ISerializerBase() override = default;

    private:
        static nn::Result SerializeWrapper(details::ISerializerInternal *instance, void *buffer, uint32_t size) {
            return instance->vtable->instance->Serialize(buffer, size);
        }

        static nn::Result DeserializeWrapper(details::ISerializerInternal *instance, void *buffer, uint32_t size) {
            return instance->vtable->instance->Deserialize(buffer, size);
        }

        static nn::Result GetCountWrapper(details::ISerializerInternal *instance, uint32_t *outCount) {
            return instance->vtable->instance->GetCount(outCount);
        }

        details::ISerializerInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance      = this,
                                .SerializeFn   = &SerializeWrapper,
                                .DeserializeFn = &DeserializeWrapper,
                                .GetCountFn    = &GetCountWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ISerializerInternal mInstance{};
        details::ISerializerInternalVTable mVTable{};
    };

    template<typename T>
    class SerializerFromPtr : public ISerializer<T> {
    public:
        explicit SerializerFromPtr(details::ISerializerInternal *ptr) : mInstancePtr(ptr) {
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
        details::ISerializerInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::ISerializerInternal *mInstancePtr;
    };

} // namespace nn::sl

#endif
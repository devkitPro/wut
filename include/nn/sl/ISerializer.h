#pragma once

#include <coreinit/time.h>
#include <nn/result.h>
#include <nn/sl/KillerNotification.h>
#include <nn/sl/details/ISerializerDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    template<typename T>
    class ISerializer : public details::ISerializerBase<T> {

    public:
        ISerializer() {
            InitInternalVtable();
        }

        ISerializer(ISerializer &src) {
            InitInternalVtable();
        }

        ISerializer &operator=(const ISerializer &other) {
            InitInternalVtable();
            return *this;
        }

        ISerializer &operator=(ISerializer &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        nn::Result Serialize(T *buffer, uint32_t num) {
            return details::ISerializerBase<T>::Serialize(buffer, num * sizeof(buffer));
        }

        nn::Result Deserialize(T *buffer, uint32_t num) {
            return details::ISerializerBase<T>::Deserialize(buffer, num * sizeof(buffer));
        }

        ~ISerializer() override = default;

    private:
        static nn::Result SerializeWrapper(details::ISerializerInternal *instance, void *buffer, uint32_t size) {
            return details::ISerializerBase<T>::instance->vtable->instance->Serialize(buffer, size);
        }

        static nn::Result DeserializeWrapper(details::ISerializerInternal *instance, void *buffer, uint32_t size) {
            return details::ISerializerBase<T>::instance->vtable->instance->Deserialize(buffer, size);
        }

        static nn::Result GetCountWrapper(details::ISerializerInternal *instance, uint32_t *outCount) {
            return details::ISerializerBase<T>::instance->vtable->instance->GetCount(outCount);
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

    details::ISerializerBase<nn::sl::IconInfo> &GetDefaultIconInfoSerializer();

    details::ISerializerBase<nn::sl::TitleInfo> &GetDefaultQuickStartTitleInfoSerializer();

    details::ISerializerBase<nn::sl::KillerNotification> &GetDefaultKillerNotificationSerializer();

    details::ISerializerBase<nn::sl::TitleInfo> &GetDefaultJumpTitleInfoSerializer();

    details::ISerializerBase<OSTime> &GetDefaultPreviousSendingTimeSerializer();
} // namespace nn::sl

#endif
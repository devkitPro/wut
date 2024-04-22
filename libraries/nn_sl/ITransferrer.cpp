#include <nn/sl/ITransferrer.h>

namespace nn::sl {
    namespace {
        extern "C" details::ITransferrerInternal *GetDrcTransferrer__Q2_2nn2slFv();
    }

    static details::TransferrerFromPtr sDrcTransferrer(GetDrcTransferrer__Q2_2nn2slFv());

    details::ITransferrerBase &GetDrcTransferrer() {
        return sDrcTransferrer;
    }
} // namespace nn::sl
#pragma once

#include <wut.h>
#include <nn/result.h>

#ifdef __cplusplus

namespace nn {

namespace acp {

nn::Result
Initialize(void)
   asm("Initialize__Q2_2nn3acpFv");

nn::Result
Finalize(void)
   asm("Finalize__Q2_2nn3acpFv");

} //namespace acp

} //namespace nn

#endif //__cplusplus

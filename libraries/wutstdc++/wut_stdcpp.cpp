#include "wut_gthread.h"

__asm__ __volatile__(
   "\t.section\t.text.__wrap___gxx_personality_v0,\"ax\",@progbits\n"
   "\t.align\t2\n"
   "\t.globl\t__wrap___gxx_personality_v0\n"
   "\t.type\t__wrap___gxx_personality_v0, @function\n"
   "__wrap___gxx_personality_v0:\n"
   "\t.cfi_startproc\n"
   "\tb\t__real___gxx_personality_v0\n"
   "\t.cfi_endproc"
);

extern "C" void
__init_wut_stdcpp()
{
   __init_wut_gthread();
}

extern "C" void
__fini_wut_stdcpp()
{
}

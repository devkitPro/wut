#include "wut_gthread.h"

extern "C" void
__init_wut_stdcpp()
{
   __init_wut_gthread();
}

extern "C" void
__fini_wut_stdcpp()
{
}

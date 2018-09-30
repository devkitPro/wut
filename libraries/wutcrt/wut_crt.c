extern void __init_wut_newlib() __attribute__((weak));
extern void __init_wut_devoptab() __attribute__((weak));
extern void __init_wut_stdcpp() __attribute__((weak));

extern void __fini_wut_devoptab() __attribute__((weak));
extern void __fini_wut_newlib() __attribute__((weak));
extern void __fini_wut_stdcpp() __attribute__((weak));

void
__init_wut()
{
   if (__init_wut_newlib) {
      __init_wut_newlib();
   }

   if (__init_wut_devoptab) {
      __init_wut_devoptab();
   }

   if (__init_wut_stdcpp) {
      __init_wut_stdcpp();
   }
}

void
__fini_wut()
{
   if (__fini_wut_stdcpp) {
      __fini_wut_stdcpp();
   }

   if (__fini_wut_devoptab) {
      __fini_wut_devoptab();
   }

   if (__fini_wut_newlib) {
      __fini_wut_newlib();
   }
}

// Forward newlib _exit to the coreinit.rpl _Exit
extern void _Exit(int status);

void
_exit(int status)
{
   _Exit(status);
}

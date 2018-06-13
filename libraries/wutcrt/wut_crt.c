extern void __init_wut_devoptab_sd() __attribute__((weak));
extern void __init_wut_newlib() __attribute__((weak));
extern void __init_wut_stdcpp() __attribute__((weak));

extern void __fini_wut_devoptab_sd() __attribute__((weak));
extern void __fini_wut_newlib() __attribute__((weak));
extern void __fini_wut_stdcpp() __attribute__((weak));

void
__init_wut()
{
   if (__init_wut_newlib) {
      __init_wut_newlib();
   }

   if (__init_wut_devoptab_sd) {
      __init_wut_devoptab_sd();
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

   if (__fini_wut_devoptab_sd) {
      __fini_wut_devoptab_sd();
   }

   if (__fini_wut_newlib) {
      __fini_wut_newlib();
   }
}

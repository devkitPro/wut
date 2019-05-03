#### wut 1.0.0-beta9
###### Breaking changes
 - coreinit's `exit` is no longer defined in `<coreinit/exit.h>`. Please use `<stdlib.h>` instead, which pulls in newlib's exit.
 - RPL import sections (`.fimport_coreinit` etc.) are now garbage-collected when using wut-tools 1.1.0 or above (required). Code relying on weak links to Cafe functions may exhibit different behaviour.
 - Changes to CMake's linker flags may cause existing build trees to fail. Please delete any old build files and re-run CMake.
 - Two new symbols, `__rpx_start` and `__rpl_start`, are now used internally by the toolchain, while `_start` is now undefined. As usual, applications are strongly discouraged from prefixing any symbol with two underscores, in order to avoid conflicts of this type.

###### Deprecations
 - `WUT_ROOT` should no longer be defined in the user's environment, and will be set to `$DEVKITPRO/wut` internally. CMake lists and makefiles that use `$WUT_ROOT/share` to find `wut.mk` or `wut.toolchain.cmake` should be changed to `$DEVKITPRO/wut/share`.
 - All of wut's static libraries (`-lcoreinit`, `-lwhb`, etc.) have been merged into a single `libwut`, which gets automatically linked in for all builds. While empty static libraries have been provided for CMake builds to ease the transition, these will be removed eventually. Applications should remove the build flags to link any of wut's libraries.
 - Similarly, wut's build configuration options (devoptab, wutmalloc, newlib) are now integrated into `libwut`. For CMake builds, the `wut_enable_*` macros will now log a deprecation warning, and should be removed as soon as possible.
 - Use of `wut.mk` as a build system is now deprecated. Applications should move to `wut_rules` and devkitPro-style makefiles, such as those in [the samples](/samples/make). `wut.mk` will not be updated further, and will be removed in a future release.

###### Other changes
 - Builds refactored: wut now uses Makefiles to build itself, as well as providing a devkitPro-style `wut_rules` file - see the `samples/make` folder. The cmake samples are now in `samples/cmake`.
 - A new linking feature, `__rplwrap`, was added to help deal with conflicts between newlib's and Cafe's functions. Because of this, wut 1.0.0-beta9 requires wut-tools 1.1.0 or newer.
 - Using rplwrap, newlib's `exit` is now correctly chained with coreinit's - calls like `atexit` should work; whether calling `exit` or just returning from `main`. Applications using coreinit's `_Exit` are encouraged to migrate to a normal `exit` call.
 - A new header file, `<coreinit/codegen.h>`, has been added and documented for OSCodegen functionality.


#### wut 1.0.0-beta8

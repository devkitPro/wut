#### wut 1.0.0-beta9
###### Breaking changes
 - coreinit's `exit` is no longer defined in `<coreinit/exit.h>`. Please use `<stdlib.h>` instead, which pulls in newlib's exit.

###### Deprecations
 - `WUT_ROOT` should no longer be defined in the user's environment, and will be set to `$DEVKITPRO/wut` internally. CMake lists and makefiles that use `$WUT_ROOT/share` to find `wut.mk` or `wut.toolchain.cmake` should be changed to `$DEVKITPRO/wut/share`.

###### Other changes
 - Builds refactored: wut now uses Makefiles to build itself, as well as providing a devkitPro-style `wut_rules` file - see the `samples/make` folder. The cmake samples are now in `samples/cmake`.
 - A new linking feature, `__rplwrap`, was added to help deal with conflicts between newlib's and Cafe's functions. Because of this, wut 1.0.0-beta9 requires wut-tools 1.1.0 or newer.
 - Using rplwrap, newlib's `exit` is now correctly chained with coreinit's - calls like `atexit` should work; whether calling `exit` or just returning from `main`. Applications using coreinit's `_Exit` are encouraged to migrate to a normal `exit` call.


#### wut 1.0.0-beta8

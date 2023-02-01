#### wut 1.1.1
###### Important changes
- Changed license to zlib to avoiding licensing issues when linking against wut in non-GPL projects. (#257)

###### Important bug fixes
- Fixed stack alignment to match PPC EABI requirements and avoid undefined behaviour (#248)
- Fixed lseek implementation which caused undefined behaviour on SEEK_CUR (#253)
- Added fix to prevent file-offset overflow in seek implementation (#254)
- Fixed lseek implementation to work correctly on files opend with O_APPEND (#256)
- Fixed and improved usage of atomics (#258)

###### New features
- Added a trapword to the crt in case a debugger is initalized to allow debugging .rpx compiled with wut (#249)
- Added support for the O_EXCL fopen flag and the following flag combinations: `O_WRONLY | O_CREAT`, `O_WRONLY | O_APPEND` and `O_WRONLY | O_TRUNC` (#250)

###### CafeOS related changes
- Fixed invalid ACPInitialize function declaration (#247)
- Fixed order of arguments for FSOpenFileExAsync (#260)

Thanks to @exjam, @fincs, @GaryOderNichts and @Maschell for their contributions to this release.

#### wut 1.1.0
###### Important bug fixes
- Added wut_load_bounds section to prevent loader bug (thanks @GaryOderNichts)
- Make sure to always read into/write from a properly aligned buffer in the devoptab to avoid heap corruption (thanks @WinterMute, @Maschell)
- Impovements of the devoptab to properly support time and mode information and many more fixes (thanks @Maschell, @Crementif)

###### Major new features
- Moved CMake machinery to devkitPro CMake (thanks @fincs)
- Replaced the CafeOS default heap with a custom one (thanks @GaryOderNichts)

###### Minor new features
- Added support for the Logging Module (thanks @Maschell)
- Added support for nn::erreula library (thanks @exjam)

###### Minor bug fixes
- Fixed potential memory leaks in nn::swkdb. (thanks @exjam)
- Fixed return types and arguments for several sysapp functions (thanks @Maschell)
- Fixed memalign to ensure the size is aligned (thanks @Maschell)
- Added missing FSUnmount on fini (thanks @Maschell)
- Only call FSUnmount if FSMount was successful in devoptab (thanks @Maschell)
- Replaced dynamic allocation of OSMutex with static table to avoid memory leaks (thanks @fincs)
- Fixed syscall_clock implementation (thanks @Maschell)
- Fixed FSError enum (thanks @Maschell)
- Fixed setting the correct directory/file flag in devoptab (thanks @Maschell)
- Enforce ACPGetTitleMetaXml parameter alignment requirement. (thanks @Maschell)
- Fixed OSThreadLink struct (thanks @Maschell)

###### Breaking changes
- The CMPTLaunchTitle function declaration has changed to use uint64_t for the title id (thanks @Xpl0itU)
- Removed nlibcurl
- Added missing parameters to multiple functions (e.g. SYSSwitchTo*/ _SYSLaunch*, FSChangeMode/FSChangeModeAsync, HIDSetIdle) (thanks @Maschell)
- Renamed SYSTEM_APP_ID_HOME_MENU to SYSTEM_APP_ID_WII_U_MENU (thanks @Maschell)

###### CafeOS related changes
- Added FSA structs and function declarations (thanks @Maschell)
- Added mic function declarations (thanks @NessieHax)
- Added missing parameter to FSChangeMode/FSChangeModeAsync (thanks @Maschell)
- Added more coreinit function declarations (thanks @Maschell, @LRFLEW, @NessieHax, @Crementif)
- Added more gx2 function declarations (thanks @GaryOderNichts)
- Added more nn::acp function declarations (thanks @Maschell)
- Added more nn::act function declarations (thanks @Maschell)
- Added more nn::ccr function declarations (thanks @Maschell)
- Added more nn::swkdb function declarations (thanks @Fangal-Airbag, @NessieHax)
- Added more nsyshid function declarations (thanks @Maschell)
- Added more nsyshid function declarations (thanks @Maschell)
- Added more nsysnet function declarations (thanks @Maschell)
- Added more nsysuhs function declarations (thanks @GaryOderNichts)
- Added more padscore function declarations (thanks @LRFLEW)
- Added more procui function declarations (thanks @GaryOderNichts)
- Added more sysapp function declarations (thanks @Maschell)
- Added more vpad function declarations (thanks @Maschell)
- Added nn::cmpt function declarations (thanks @GaryOderNichts)
- Added nn::erreula function declarations (thanks @exjam)
- Added nn::fp function declarations (thanks @NessieHax)
- Added nn::nfp function declarations (thanks @GaryOderNichts)
- Added nn::save function declarations (thanks @GaryOderNichts)
- Added nn::sl function declarations (thanks @Maschell)
- Added nn::spm function declarations (thanks @GaryOderNichts)
- Added nn::temp function declarations (thanks @exjam)
- Added nsyskbd function declarations (thanks @Maschell)

#### wut 1.0.0-beta12
###### Important bug fixes
- Numerous improvements to linking rpl/rpx which fixes C++ exceptions and static constructors not working correctly (thanks @fincs)
- Fix `gettod` implementation returning incorrect time (thanks @GaryOderNichts)
- Fix `nn::Result` to work correctly on big endian (thanks @luigoalma)

###### Major new features
- Add Makefile build system support for producing .wuhb files, a new homebrew app bundle format intended to streamline distribution of ancilliary assets (icons, content files) and compatibility with future homebrew loading solutions (thanks @fincs, @Maschell)
- New POSIX compatible socket implementation which aims to make porting existing code to Wii U seamless (thanks @rw-r-r-0644, @GaryOderNichts, @fincs)

###### Minor bug fixes
- Add missing cleanup of filesystem clients in WHB (thanks @Maschell)
- Optimise `fread`, `fwrite` when the provided buffer is already aligned (thanks @Maschell)

###### CafeOS related changes
- Fix names for `IM{Get,Set}DimEnable{DRC,TV}` (was previously incorrectly capitalised Drc and Tv)
- Add missing enum values in gx2 and improve usage of enums from C++ by adding operator| (thanks @fincs)
- Add missing `FSErrorFlag` type for all filesystem functions (thanks @Maschell)
- Add more coreinit function declarations (thanks @Maschell)
- Add more nn_ac function declarations (thanks @Maschell)
- Add some nsysuhs function declarations (thanks @Maschell)
- Add more sndcore2 function declarations (thanks @GaryOderNichts)
- Add more vpad function declarations (thanks @Crayon2000)

#### wut 1.0.0-beta10
###### Breaking changes
- libwhb's network command server (`WHBCommandServer`) functions and the associated `<whb/commandserver.h>` header have been removed.

###### Deprecations
- The CMake macro `wut_create_rpl` has been re-implemented. The new version doesn't create a build target for the rpx/rpl binary, and only regenerates the rpx/rpl when actually necessary. The new syntax is `wut_create_rpl(<TARGET>)`. Deprecated calls in the form `wut_create_rpl(file.rpx <TARGET>)` will fall through to the old implementation.

###### API additions
- Cafe functions `inet_ntoa_r`, `inet_ntop`, and `inet_pton` have been added to `<nsysnet/socket.h>` (thanks [@Crayon2000](https://github.com/devkitPro/wut/commit/df93bf758f54c1d3a65bc7205a81a6da382c31a0)!)
- Cafe functions `VPADGetTPCalibratedPointEx`, `VPADGetTPCalibrationParam`, and `VPADSetTPCalibrationParam` have been added to `<vpad/input.h>`.
- Cafe functions `OSGetOSID` and `__OSGetProcessSDKVersion` have been added to `<coreinit/systeminfo.h>` (thanks [@Maschell](https://github.com/devkitPro/wut/commit/fe230e06ccf43f3b13d25643399dd9a04bf7eb43)!)
- Cafe function `_SYSGetSystemApplicationTitleId` has been added to `<sysapp/title.h>` (thanks [@Maschell](https://github.com/devkitPro/wut/commit/35c20d8700cddd46f5e37789617629e010a8ad1f)!)
- Cafe functions `SYSGetCallerPFID`, `_SYSGetSystemApplicationTitleIdByProdArea`, and `SYSGetCallerTitleId` have been added `<sysapp/title.h>`.
- Cafe functions `OSReportVerbose`, `OSReportInfo`, and `OSReportWarn` have been added to `<coreinit/debug.h>`.
- New libwhb functions `WHBGfxGetTVColourBuffer`, `WHBGfxGetTVDepthBuffer`, `WHBGfxGetTVContextState`, and equivalents for the DRC, have been added to `<whb/gfx.h>`.
- [Helper functions](https://github.com/devkitPro/wut/commit/f0ed4fb91ff7f738f5e36e54094935530cbbbefe) have been added to `<gx2/shaders.h>` which can look up shader uniforms by name.
- A new header file, `<nn/acp.h>`, has been added for nn_acp's meta.xml functionality (thanks [@Maschell](https://github.com/devkitPro/wut/commit/7f2c9b5d696b609d1be8f95597e4be02097f2608)!)
- Cafe structure `KPADStatus` (from `<padscore/kpad.h>`) has been documented, had accelerometer data added, and had nunchuk-specific values added (thanks [@Crayon2000](https://github.com/devkitPro/wut/commit/78ee1c51bc11ae53edd6b6025f8bdb984e05b497)!)
- Various Cafe structures in `<coreinit/mcp.h>` have been updated with newly-discovered members (thanks [@Maschell](https://github.com/devkitPro/wut/commit/b712686c388a7a9cb0a03a82358386df105ac7f7), [again](https://github.com/devkitPro/wut/commit/d1d2da63adabc55de70e82310f312b1b5fe450c2)!)
- Cafe enum `GX2PrimitiveMode` has been updated to include the `LINES_ADJACENCY`, `LINE_STRIP_ADJACENCY`, `TRIANGLES_ADJACENCY`, `TRIANGLE_STRIP_ADJACENCY`, `RECTS`, and `LINE_LOOP` primitives.

###### Other changes
- Cafe functions throughout the GX2 headers have had `const` applied as appropriate, allowing for better compiler optimisations.
- libwhb's Console and graphics helpers have been refactored to better support Cafe's multitasking and home menu overlay. Applications using WHBConsole can now be backgrounded and resumed without issue.
- Cafe's KPAD library has been documented, WPAD has been partially documented, and various fixes were made to the VPAD documentation (thanks [@Crayon2000](https://github.com/devkitPro/wut/commit/78ee1c51bc11ae53edd6b6025f8bdb984e05b497)!)
- CMake now searches for libraries in internal devkitPPC folders, allowing `find_library(m)` (and CMake pkg-config equivalents) to work as expected.
- CMake now sets the pkg-config binary to `powerpc-eabi-pkg-config`, installable from the `dkp-libs` repo as `wiiu-pkg-config`. Application scripts no longer need to set `PKG_CONFIG_EXECUTABLE`.
- wutstdc++'s threading implementation has been changed to behave more like a pre-emptive scheduler, yielding a thread after 1ms runtime. This applies to `std::thread` and `<threads.h>`, not applications working with `OSThread` directly.

#### wut 1.0.0-beta9
###### Breaking changes
 - coreinit's `exit` is no longer defined in `<coreinit/exit.h>`. Please use `<stdlib.h>` instead, which pulls in newlib's exit.
 - RPL import sections (`.fimport_coreinit` etc.) are now garbage-collected when using wut-tools 1.1.0 or above (required). Code relying on weak links to Cafe functions may exhibit different behaviour.
 - `snd_core` and `snd_user` are no longer linked, due to naming conflicts with `sndcore2` and `snduser2`. wut has never shipped headers for these libraries, but if you are using them, please switch to `sndcore2` and `snduser2`.
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

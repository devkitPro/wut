[![Build status](https://ci.appveyor.com/api/projects/status/rjmwygepioxdx1fs/branch/master?svg=true)](https://ci.appveyor.com/project/exjam/wut/branch/master) [![Build Status](https://travis-ci.org/decaf-emu/wut.svg?branch=master)](https://travis-ci.org/decaf-emu/wut)

# wut
Let's try make a Wii U Toolchain / SDK for creating rpx/rpl.

Licensed under the terms of the GNU General Public License, version 2 or later (GPLv2+).

Doxygen output can be found at https://decaf-emu.github.io/wut

If you are looking for the old Makefile based wut, that can be found on the [legacy-make](https://github.com/decaf-emu/wut/tree/legacy-make) branch.

## Binaries
The latest Windows AppVeyor build is available from:
- https://ci.appveyor.com/api/projects/exjam/wut/artifacts/build/install/wut.zip?branch=master

## Requirements
- Tested on Linux, OS X, Windows
- [devkitPPC](https://devkitpro.org/wiki/Getting_Started/devkitPPC)
- CMake
- Make

## Linux / OS X
Requires CMake + Make + [devkitPPC](https://devkitpro.org/wiki/Getting_Started/devkitPPC) + libzdev

```
export DEVKITPPC=<Path to devkitPPC>
git clone --recursive https://github.com/decaf-emu/wut.git
cd wut
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=install ../
make
make install
export WUT_ROOT=$PWD/install
```

Then for any wut project you want to build you must use the wut-toolchain.cmake script:

```
cd ../samples/helloworld
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$WUT_ROOT/cmake/wut-toolchain.cmake ../
make
```

## Windows
Requires [Windows CMake](https://cmake.org/download/) + [Windows Make](http://gnuwin32.sourceforge.net/packages/make.htm) + [devkitPPC](https://devkitpro.org/wiki/Getting_Started/devkitPPC) + Visual Studio.

```
set DEVKITPPC=<Path to devkitPPC>
git clone --recursive https://github.com/decaf-emu/wut.git
cd wut
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=install -G "Visual Studio 15 2017" ../
msbuild INSTALL.vcxproj /p:Configuration=Release /p:Platform=Win32
set WUT_ROOT=%CD%\install
```

Then for any wut project you want to build you must use Unix Makefiles with the wut-toolchain.cmake script:

```
cd ..\samples\helloworld
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=%WUT_ROOT%\cmake\wut-toolchain.cmake -G "Unix Makefiles" ../
make
```

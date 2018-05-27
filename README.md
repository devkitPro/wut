[![Build status](https://ci.appveyor.com/api/projects/status/rjmwygepioxdx1fs/branch/rewrite?svg=true)](https://ci.appveyor.com/project/exjam/wut/branch/rewrite) [![Build Status](https://travis-ci.org/decaf-emu/wut.svg?branch=rewrite)](https://travis-ci.org/decaf-emu/wut)

# wut
Let's try make a Wii U Toolchain / SDK for creating rpx/rpl.

Licensed under the terms of the GNU General Public License, version 2 or later (GPLv2+).

## Rewrite
This branch is an WIP experimental rewrite to simplify how elf2rpl works and hopefully make it more correct for more advanced C++ programs.

## Requirements
- Custom [devkitPPC](https://github.com/exjam/buildscripts)

## Linux
Requires CMake + Make + [devkitPPC](https://github.com/exjam/buildscripts) + libzdev

```
export DEVKITPPC=<Path to devkitPPC>
git clone --recursive https://github.com/decaf-emu/wut.git
cd wut
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=<path/to/install> -DDEVKITPPC=$DEVKITPPC ../
make
make install
export WUT_ROOT=<path/to/install>
```

Then for any wut project you want to build you must use the wut.toolchain.cmake script:

```
cd ../samples/helloworld
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$WUT_ROOT/share/wut.toolchain.cmake -DDEVKITPPC=$DEVKITPPC -DWUT_ROOT=$WUT_ROOT ../
make
```

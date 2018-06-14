[![Build Status](https://travis-ci.org/decaf-emu/wut.svg?branch=rewrite)](https://travis-ci.org/decaf-emu/wut)

# wut
Let's try make a Wii U Toolchain / SDK for creating rpx/rpl.

Licensed under the terms of the GNU General Public License, version 2 or later (GPLv2+).

## Requirements
- A modern compiler with C++14/17 support
- CMake
- zlib
- [devkitPPC r31+](https://devkitpro.org/wiki/Getting_Started)

## Windows
Use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) and then follow the Linux instructions.

For example, if you installed Ubuntu then you might setup your environment like:

```
sudo apt install cmake zlib1g-dev gcc-7 g++-7
wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb
sudo dpkg -i devkitpro-pacman.deb
sudo dkp-pacman -S devkitPPC wiiload
```

## Linux / MacOS
```
export DEVKITPPC=/opt/devkitpro/devkitPPC
git clone --recursive https://github.com/decaf-emu/wut.git
cd wut
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=<path/to/install> ../
make install
export WUT_ROOT=<path/to/install>
```

Then for any wut project you want to build you must use the wut.toolchain.cmake script:

```
cd ../samples/helloworld
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$WUT_ROOT/share/wut.toolchain.cmake ../
make
```

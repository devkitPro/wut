# wut
Let's try make a Wii U Toolchain / SDK for creating rpx/rpl.

Licensed under the terms of the GNU General Public License, version 2 or later (GPLv2+).

## Requirements
- devkitPRO + devkitPPC
- Only tested on Linux so far

## Usage
- git clone https://github.com/decaf-emu/wut.git
- cd wut
- export devkitPRO=...
- export devkitPPC=...
- export WUT_ROOT=$PWD
- make install
- cd samples/helloworld
- make

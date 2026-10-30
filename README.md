[![Build status](https://github.com/devkitPro/wut/workflows/C%2FC%2B%2B%20CI/badge.svg)](https://github.com/devkitPro/wut/actions?workflow=C%2FC%2B%2B+CI)

# wut
Let's try to make a Wii U Toolchain / SDK for creating rpx/rpl.

Licensed under the terms of the zlib License (see [LICENSE.txt](LICENSE.txt)).

## Install

It is recommended to follow [devkitPro's Getting Started guide](https://devkitpro.org/wiki/Getting_Started),
which will guide you through setting up a suitable homebrew development environment.
[devkitPro Pacman](https://devkitpro.org/wiki/devkitPro_pacman) is exclusively used to manage installed
homebrew development components.

The following command installs all necessary packages for Wii U homebrew development, including wut:
```
(sudo) (dkp-)pacman -Syu --needed wiiu-dev
```

## Usage
See [wiiu-examples](https://github.com/devkitPro/wiiu-examples) for examples of how to use wut.

## Building from source

**It is strongly recommended to stick to stable released packages installed with devkitPro Pacman.**

Building wut is simple as running the following commands:
```
make
(sudo -E) make install
```

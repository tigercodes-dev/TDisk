# TDisk

**Tiger Disk Management Utility** 💾💿

## Overview

This program allows you to manage disk partitions, filesystems, and even view the files on them.

## Building

### Requirements

- g++ - C++ Compiler
- make - Build system
- gdb (optional) - Debugger

### Build Command

To build the program, run `make` in the root project directory.

After the build finishes, your executable will be in the build directory.

### Installation

To install the program, run `make install`

If you want to chose where it is installed (default is /usr/local/bin), then set the `INSTALL_DIR` variable.

## Debugging

TDisk supports debugging. By default, the Makefile will create a release build, but if you want to debug, you must set the `BUILD_TYPE` variable in the make command to "debug".

This will add debugging symbols to the build so that you can debug with GDB.

## Modifying

*TDisk is open source and permits users to modify or extend the code. View COPYING to see more information.*

*Copyright (C) 2026 tigercodes-dev*
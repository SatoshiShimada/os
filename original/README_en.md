My Operationg System
====

Target: x86 IntelArchitecture 32bit

## Description

using emulator: qemu(version 2.2.1)

using compiler: gcc(version 4.9.2)

platform: Linux

Using media: Floppy disk


execute:

enter source directory, and `make run`

or `make` and copy img.os file write to FloppyDisk.


disk filesystem: FAT12

master boot loader is jump to 0xC200, and execute program of sector 2.

change to protected mode.

## memory map
0x8200: sector2(stage2.bin file)

0xc200: 0x4200 of FDD image (stage2.bin file)
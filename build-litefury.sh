#!/bin/sh

export PATH=~/riscv64-unknown-elf-gcc/bin:$PATH
export CROSS_COMPILE=riscv64-unknown-elf-
make PLATFORM=vexriscv_litefury clean all
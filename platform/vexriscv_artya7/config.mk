#
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (c) 2020 Western Digital Corporation or its affiliates.
#
# Authors:
#   Anup Patel <anup.patel@wdc.com>
#

PLATFORM_RISCV_XLEN = 32

# Compiler flags
platform-cppflags-y =
platform-cflags-y = -mabi=ilp32 -march=rv32ima -g
platform-asflags-y = -mabi=ilp32 -march=rv32ima -g
platform-ldflags-y = 

# Command for platform specific "make run"
platform-runcmd = qemu-system-riscv$(PLATFORM_RISCV_XLEN) -M virt -m 256M \
  -nographic -bios $(build_dir)/platform/generic/firmware/fw_payload.elf

# Blobs to build
FW_TEXT_START=0xC0010000
FW_DYNAMIC=n
FW_JUMP=y
FW_JUMP_ADDR=0xC0100000
FW_JUMP_FDT_ADDR=0xC0000000
FW_PAYLOAD=n
ifeq ($(PLATFORM_RISCV_XLEN), 32)
  # This needs to be 4MB aligned for 32-bit system
  FW_PAYLOAD_OFFSET=0x400000
else
  # This needs to be 2MB aligned for 64-bit system
  FW_PAYLOAD_OFFSET=0x200000
endif
FW_PAYLOAD_FDT_ADDR=$(FW_JUMP_FDT_ADDR)

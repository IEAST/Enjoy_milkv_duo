CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv64imafd -mabi=lp64f -g -Wall -mcmodel=medany

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump

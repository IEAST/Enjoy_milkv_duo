#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/*
 * QEMU RISC-V Virt machine with 16550a UART and VirtIO MMIO
 */

/*
 * maximum number of CPUs
 * see https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * #define VIRT_CPUS_MAX 8
 */
#define MAXNUM_CPU 1

/*
 * MemoryMap
 * see https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c, virt_memmap[]
 * 0x00001000 -- boot ROM, provided by qemu
 * 0x02000000 -- CLINT
 * 0x0C000000 -- PLIC
 * 0x10000000 -- UART0
 * 0x10001000 -- virtio disk
 * 0x80000000 -- boot ROM jumps here in machine mode, where we load our kernel
 */

/* This machine puts UART registers here in physical memory. */
#define UART0 0x4140000L

/*
 * UART0 interrupt source
 * see https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * enum {
 *     UART0_IRQ = 10,
 *     ......
 * };
 */
#define UART0_IRQ 44

/*
 * This machine puts platform-level interrupt controller (PLIC) here.
 * Here only list PLIC registers in Machine mode.
 * see https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * #define VIRT_PLIC_HART_CONFIG "MS"
 * #define VIRT_PLIC_NUM_SOURCES 127
 * #define VIRT_PLIC_NUM_PRIORITIES 7
 * #define VIRT_PLIC_PRIORITY_BASE 0x04
 * #define VIRT_PLIC_PENDING_BASE 0x1000
 * #define VIRT_PLIC_ENABLE_BASE 0x2000
 * #define VIRT_PLIC_ENABLE_STRIDE 0x80
 * #define VIRT_PLIC_CONTEXT_BASE 0x200000
 * #define VIRT_PLIC_CONTEXT_STRIDE 0x1000
 * #define VIRT_PLIC_SIZE(__num_context) \
 *     (VIRT_PLIC_CONTEXT_BASE + (__num_context) * VIRT_PLIC_CONTEXT_STRIDE)
 */
#define PLIC_BASE 0x70000000L
#define PLIC_PRIORITY(id) (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id) (PLIC_BASE + 0x1000 + ((id) / 32) * 4)
#define PLIC_MENABLE(id) (PLIC_BASE + 0x2000 + ((id) / 32) * 4)
#define PLIC_MTHRESHOLD (PLIC_BASE + 0x200000)
#define PLIC_MCLAIM (PLIC_BASE + 0x200004)
#define PLIC_MCOMPLETE (PLIC_BASE + 0x200004)

 /*
  * The Core Local INTerruptor (CLINT) block holds memory-mapped control and
  * status registers associated with software and timer interrupts.
  * QEMU-virt reuses sifive configuration for CLINT.
  * see https://gitee.com/qemu/qemu/blob/master/include/hw/riscv/sifive_clint.h
  * enum {
  * 	SIFIVE_SIP_BASE     = 0x0,
  * 	SIFIVE_TIMECMP_BASE = 0x4000,
  * 	SIFIVE_TIME_BASE    = 0xBFF8
  * };
  *
  * enum {
  * 	SIFIVE_CLINT_TIMEBASE_FREQ = 10000000
  * };
  *
  * Notice:
  * The machine-level MSIP bit of mip register are written by accesses to
  * memory-mapped control registers, which are used by remote harts to provide
  * machine-mode interprocessor interrupts.
  * For QEMU-virt machine, Each msip register is a 32-bit wide WARL register
  * where the upper 31 bits are tied to 0. The least significant bit is
  * reflected in the MSIP bit of the mip CSR. We can write msip to generate
  * machine-mode software interrupts. A pending machine-level software
  * interrupt can be cleared by writing 0 to the MSIP bit in mip.
  * On reset, each msip register is cleared to zero.
  */
#define CLINT_BASE 0x74000000L
#define CLINT_MSIP (CLINT_BASE)
#define CLINT_MTIMECMPL (CLINT_BASE + 0x4000)
#define CLINT_MTIMECMPH (CLINT_BASE + 0x4004)


#define CLINT_TIMEBASE_FREQ 25000000

#endif /* __PLATFORM_H__ */

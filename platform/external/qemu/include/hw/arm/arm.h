/*
 * Misc ARM declarations
 *
 * Copyright (c) 2006 CodeSourcery.
 * Written by Paul Brook
 *
 * This code is licenced under the LGPL.
 *
 */

#ifndef ARM_MISC_H
#define ARM_MISC_H 1

#include "cpu.h"
#include "hw/loader.h"

#define ARM_PIC_CPU_IRQ 0
#define ARM_PIC_CPU_FIQ 1
qemu_irq *arm_pic_init_cpu(CPUOldState *env);

qemu_irq *armv7m_init(int flash_size, int sram_size,
                      const char *kernel_filename, const char *cpu_model);

struct arm_boot_info {
    int ram_size;
    const char *kernel_filename;
    const char *kernel_cmdline;
    const char *initrd_filename;
    hwaddr loader_start;
    hwaddr smp_loader_start;
    hwaddr smp_priv_base;
    int nb_cpus;
    int board_id;
    int (*atag_board)(const struct arm_boot_info *info, void *p);
    
    int is_linux;
    hwaddr initrd_size;
    hwaddr entry;
};
void arm_load_kernel(CPUARMState *env, struct arm_boot_info *info);

extern int system_clock_scale;

#endif 

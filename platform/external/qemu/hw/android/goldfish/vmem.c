/* Copyright (C) 2007-2008 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/
#include "hw/hw.h"
#include "hw/android/goldfish/vmem.h"
#ifdef TARGET_I386
#include "sysemu/kvm.h"
#endif



int safe_memory_rw_debug(CPUState *cpu, target_ulong addr, uint8_t *buf,
                         int len, int is_write)
{
#ifdef TARGET_I386
    if (kvm_enabled()) {
        kvm_get_sregs(cpu);
    }
#endif
    return cpu_memory_rw_debug(cpu, addr, buf, len, is_write);
}

hwaddr safe_get_phys_page_debug(CPUState *cpu, target_ulong addr)
{
    CPUArchState *env = cpu->env_ptr;

#ifdef TARGET_I386
    if (kvm_enabled()) {
        kvm_get_sregs(cpu);
    }
#endif
    return cpu_get_phys_page_debug(env, addr);
}


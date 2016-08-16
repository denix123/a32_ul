/*
 * QEMU CPU model
 *
 * Copyright (c) 2012 SUSE LINUX Products GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/gpl-2.0.html>
 */
#ifndef QEMU_CPU_H
#define QEMU_CPU_H

#include <signal.h>
#include "hw/qdev-core.h"
#include "exec/hwaddr.h"
#include "qemu/queue.h"
#include "qemu/thread.h"
#include "qemu/tls.h"
#include "qemu/typedefs.h"

typedef int (*WriteCoreDumpFunction)(void *buf, size_t size, void *opaque);

typedef uint64_t vaddr;
#define VADDR_PRId PRId64
#define VADDR_PRIu PRIu64
#define VADDR_PRIo PRIo64
#define VADDR_PRIx PRIx64
#define VADDR_PRIX PRIX64
#define VADDR_MAX UINT64_MAX

typedef struct CPUState CPUState;

typedef void (*CPUUnassignedAccess)(CPUState *cpu, hwaddr addr,
                                    bool is_write, bool is_exec, int opaque,
                                    unsigned size);

struct TranslationBlock;

struct CPUState {
    int nr_cores;
    int nr_threads;
    int numa_node;

    struct QemuThread *thread;

    uint32_t host_tid; 
    int running; 
    struct QemuCond *halt_cond;
    struct qemu_work_item *queued_work_first, *queued_work_last;

    uint32_t created;
    uint32_t stop;   
    uint32_t stopped; 

    volatile sig_atomic_t exit_request;
    uint32_t interrupt_request;

    void *env_ptr; 
    struct TranslationBlock *current_tb; 
    int singlestep_enabled;
    struct GDBRegisterState *gdb_regs;
    QTAILQ_ENTRY(CPUState) node;   

    const char *cpu_model_str;

    int kvm_fd;
    int kvm_vcpu_dirty;
    struct KVMState *kvm_state;
    struct kvm_run *kvm_run;

    struct hax_vcpu_state *hax_vcpu;

    
    int cpu_index; 
    uint32_t halted; 
};

#define CPU(obj)  ((CPUState*)(obj))

QTAILQ_HEAD(CPUTailQ, CPUState);
extern struct CPUTailQ cpus;
#define CPU_NEXT(cpu) QTAILQ_NEXT(cpu, node)
#define CPU_FOREACH(cpu) QTAILQ_FOREACH(cpu, &cpus, node)
#define CPU_FOREACH_SAFE(cpu, next_cpu) \
    QTAILQ_FOREACH_SAFE(cpu, &cpus, node, next_cpu)
#define first_cpu QTAILQ_FIRST(&cpus)

DECLARE_TLS(CPUState *, current_cpu);
#define current_cpu tls_var(current_cpu)

#define cpu_single_env ((CPUArchState*)current_cpu->env_ptr)

enum CPUDumpFlags {
    CPU_DUMP_CODE = 0x00010000,
    CPU_DUMP_FPU  = 0x00020000,
    CPU_DUMP_CCOP = 0x00040000,
};

void cpu_dump_state(CPUState *cpu, FILE *f, fprintf_function cpu_fprintf,
                    int flags);

void cpu_dump_statistics(CPUState *cpu, FILE *f, fprintf_function cpu_fprintf,
                         int flags);

void cpu_reset(CPUState *cpu);

bool qemu_cpu_has_work(CPUState *cpu);

bool qemu_cpu_is_self(CPUState *cpu);

void qemu_cpu_kick(CPUState *cpu);

bool cpu_is_stopped(CPUState *cpu);

void run_on_cpu(CPUState *cpu, void (*func)(void *data), void *data);

CPUState *qemu_get_cpu(int index);

void cpu_interrupt(CPUState *cpu, int mask);

void cpu_reset_interrupt(CPUState *cpu, int mask);

void cpu_exit(CPUState *cpu);

void cpu_resume(CPUState *cpu);

void qemu_init_vcpu(CPUState *cpu);

#define SSTEP_ENABLE  0x1  
#define SSTEP_NOIRQ   0x2  
#define SSTEP_NOTIMER 0x4  

void cpu_single_step(CPUState *cpu, int enabled);

#endif  

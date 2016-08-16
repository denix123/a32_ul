/*
 * defines common to all virtual CPUs
 *
 *  Copyright (c) 2003 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CPU_ALL_H
#define CPU_ALL_H

#include "qemu-common.h"
#include "qemu/queue.h"
#include "qemu/thread.h"
#include "qemu/tls.h"
#include "exec/cpu-common.h"


#if defined(HOST_WORDS_BIGENDIAN) != defined(TARGET_WORDS_BIGENDIAN)
#define BSWAP_NEEDED
#endif

#ifdef BSWAP_NEEDED

static inline uint16_t tswap16(uint16_t s)
{
    return bswap16(s);
}

static inline uint32_t tswap32(uint32_t s)
{
    return bswap32(s);
}

static inline uint64_t tswap64(uint64_t s)
{
    return bswap64(s);
}

static inline void tswap16s(uint16_t *s)
{
    *s = bswap16(*s);
}

static inline void tswap32s(uint32_t *s)
{
    *s = bswap32(*s);
}

static inline void tswap64s(uint64_t *s)
{
    *s = bswap64(*s);
}

#else

static inline uint16_t tswap16(uint16_t s)
{
    return s;
}

static inline uint32_t tswap32(uint32_t s)
{
    return s;
}

static inline uint64_t tswap64(uint64_t s)
{
    return s;
}

static inline void tswap16s(uint16_t *s)
{
}

static inline void tswap32s(uint32_t *s)
{
}

static inline void tswap64s(uint64_t *s)
{
}

#endif

#if TARGET_LONG_SIZE == 4
#define tswapl(s) tswap32(s)
#define tswapls(s) tswap32s((uint32_t *)(s))
#define bswaptls(s) bswap32s(s)
#else
#define tswapl(s) tswap64(s)
#define tswapls(s) tswap64s((uint64_t *)(s))
#define bswaptls(s) bswap64s(s)
#endif



#if defined(TARGET_WORDS_BIGENDIAN)
#define lduw_p(p) lduw_be_p(p)
#define ldsw_p(p) ldsw_be_p(p)
#define ldl_p(p) ldl_be_p(p)
#define ldq_p(p) ldq_be_p(p)
#define ldfl_p(p) ldfl_be_p(p)
#define ldfq_p(p) ldfq_be_p(p)
#define stw_p(p, v) stw_be_p(p, v)
#define stl_p(p, v) stl_be_p(p, v)
#define stq_p(p, v) stq_be_p(p, v)
#define stfl_p(p, v) stfl_be_p(p, v)
#define stfq_p(p, v) stfq_be_p(p, v)
#else
#define lduw_p(p) lduw_le_p(p)
#define ldsw_p(p) ldsw_le_p(p)
#define ldl_p(p) ldl_le_p(p)
#define ldq_p(p) ldq_le_p(p)
#define ldfl_p(p) ldfl_le_p(p)
#define ldfq_p(p) ldfq_le_p(p)
#define stw_p(p, v) stw_le_p(p, v)
#define stl_p(p, v) stl_le_p(p, v)
#define stq_p(p, v) stq_le_p(p, v)
#define stfl_p(p, v) stfl_le_p(p, v)
#define stfq_p(p, v) stfq_le_p(p, v)
#endif


#if defined(CONFIG_USER_ONLY)
#include <assert.h>
#include "exec/user/abitypes.h"

#if defined(CONFIG_USE_GUEST_BASE)
extern unsigned long guest_base;
extern int have_guest_base;
extern unsigned long reserved_va;
#define GUEST_BASE guest_base
#define RESERVED_VA reserved_va
#else
#define GUEST_BASE 0ul
#define RESERVED_VA 0ul
#endif

#define g2h(x) ((void *)((unsigned long)(target_ulong)(x) + GUEST_BASE))

#if HOST_LONG_BITS <= TARGET_VIRT_ADDR_SPACE_BITS
#define h2g_valid(x) 1
#else
#define h2g_valid(x) ({ \
    unsigned long __guest = (unsigned long)(x) - GUEST_BASE; \
    (__guest < (1ul << TARGET_VIRT_ADDR_SPACE_BITS)) && \
    (!RESERVED_VA || (__guest < RESERVED_VA)); \
})
#endif

#define h2g_nocheck(x) ({ \
    unsigned long __ret = (unsigned long)(x) - GUEST_BASE; \
    (abi_ulong)__ret; \
})

#define h2g(x) ({ \
     \
    assert(h2g_valid(x)); \
    h2g_nocheck(x); \
})

#define saddr(x) g2h(x)
#define laddr(x) g2h(x)

#else 
#define saddr(x) (uint8_t *)(intptr_t)(x)
#define laddr(x) (uint8_t *)(intptr_t)(x)
#endif

#define ldub_raw(p) ldub_p(laddr((p)))
#define ldsb_raw(p) ldsb_p(laddr((p)))
#define lduw_raw(p) lduw_p(laddr((p)))
#define ldsw_raw(p) ldsw_p(laddr((p)))
#define ldl_raw(p) ldl_p(laddr((p)))
#define ldq_raw(p) ldq_p(laddr((p)))
#define ldfl_raw(p) ldfl_p(laddr((p)))
#define ldfq_raw(p) ldfq_p(laddr((p)))
#define stb_raw(p, v) stb_p(saddr((p)), v)
#define stw_raw(p, v) stw_p(saddr((p)), v)
#define stl_raw(p, v) stl_p(saddr((p)), v)
#define stq_raw(p, v) stq_p(saddr((p)), v)
#define stfl_raw(p, v) stfl_p(saddr((p)), v)
#define stfq_raw(p, v) stfq_p(saddr((p)), v)


#if defined(CONFIG_USER_ONLY)

#define ldub(p) ldub_raw(p)
#define ldsb(p) ldsb_raw(p)
#define lduw(p) lduw_raw(p)
#define ldsw(p) ldsw_raw(p)
#define ldl(p) ldl_raw(p)
#define ldq(p) ldq_raw(p)
#define ldfl(p) ldfl_raw(p)
#define ldfq(p) ldfq_raw(p)
#define stb(p, v) stb_raw(p, v)
#define stw(p, v) stw_raw(p, v)
#define stl(p, v) stl_raw(p, v)
#define stq(p, v) stq_raw(p, v)
#define stfl(p, v) stfl_raw(p, v)
#define stfq(p, v) stfq_raw(p, v)

#define cpu_ldub_code(env1, p) ldub_raw(p)
#define cpu_ldsb_code(env1, p) ldsb_raw(p)
#define cpu_lduw_code(env1, p) lduw_raw(p)
#define cpu_ldsw_code(env1, p) ldsw_raw(p)
#define cpu_ldl_code(env1, p) ldl_raw(p)
#define cpu_ldq_code(env1, p) ldq_raw(p)

#define cpu_ldub_data(env, addr) ldub_raw(addr)
#define cpu_lduw_data(env, addr) lduw_raw(addr)
#define cpu_ldsw_data(env, addr) ldsw_raw(addr)
#define cpu_ldl_data(env, addr) ldl_raw(addr)
#define cpu_ldq_data(env, addr) ldq_raw(addr)

#define cpu_stb_data(env, addr, data) stb_raw(addr, data)
#define cpu_stw_data(env, addr, data) stw_raw(addr, data)
#define cpu_stl_data(env, addr, data) stl_raw(addr, data)
#define cpu_stq_data(env, addr, data) stq_raw(addr, data)

#define cpu_ldub_kernel(env, addr) ldub_raw(addr)
#define cpu_lduw_kernel(env, addr) lduw_raw(addr)
#define cpu_ldsw_kernel(env, addr) ldsw_raw(addr)
#define cpu_ldl_kernel(env, addr) ldl_raw(addr)
#define cpu_ldq_kernel(env, addr) ldq_raw(addr)

#define cpu_stb_kernel(env, addr, data) stb_raw(addr, data)
#define cpu_stw_kernel(env, addr, data) stw_raw(addr, data)
#define cpu_stl_kernel(env, addr, data) stl_raw(addr, data)
#define cpu_stq_kernel(env, addr, data) stq_raw(addr, data)

#define ldub_kernel(p) ldub_raw(p)
#define ldsb_kernel(p) ldsb_raw(p)
#define lduw_kernel(p) lduw_raw(p)
#define ldsw_kernel(p) ldsw_raw(p)
#define ldl_kernel(p) ldl_raw(p)
#define ldq_kernel(p) ldq_raw(p)
#define ldfl_kernel(p) ldfl_raw(p)
#define ldfq_kernel(p) ldfq_raw(p)
#define stb_kernel(p, v) stb_raw(p, v)
#define stw_kernel(p, v) stw_raw(p, v)
#define stl_kernel(p, v) stl_raw(p, v)
#define stq_kernel(p, v) stq_raw(p, v)
#define stfl_kernel(p, v) stfl_raw(p, v)
#define stfq_kernel(p, vt) stfq_raw(p, v)

#define cpu_ldub_data(env, addr) ldub_raw(addr)
#define cpu_lduw_data(env, addr) lduw_raw(addr)
#define cpu_ldl_data(env, addr) ldl_raw(addr)

#define cpu_stb_data(env, addr, data) stb_raw(addr, data)
#define cpu_stw_data(env, addr, data) stw_raw(addr, data)
#define cpu_stl_data(env, addr, data) stl_raw(addr, data)
#endif 


#define TARGET_PAGE_SIZE (1 << TARGET_PAGE_BITS)
#define TARGET_PAGE_MASK ~(TARGET_PAGE_SIZE - 1)
#define TARGET_PAGE_ALIGN(addr) (((addr) + TARGET_PAGE_SIZE - 1) & TARGET_PAGE_MASK)
#ifdef TARGET_X86_64
#define TARGET_PTE_MASK 0x7fffffffffffULL
#endif

extern uintptr_t qemu_real_host_page_size;
extern uintptr_t qemu_host_page_size;
extern uintptr_t qemu_host_page_mask;

#define HOST_PAGE_ALIGN(addr) (((addr) + qemu_host_page_size - 1) & qemu_host_page_mask)

#define PAGE_READ      0x0001
#define PAGE_WRITE     0x0002
#define PAGE_EXEC      0x0004
#define PAGE_BITS      (PAGE_READ | PAGE_WRITE | PAGE_EXEC)
#define PAGE_VALID     0x0008
#define PAGE_WRITE_ORG 0x0010
#if defined(CONFIG_BSD) && defined(CONFIG_USER_ONLY)
#define PAGE_RESERVED  0x0020
#endif

#if defined(CONFIG_USER_ONLY)
void page_dump(FILE *f);

typedef int (*walk_memory_regions_fn)(void *, abi_ulong,
                                      abi_ulong, unsigned long);
int walk_memory_regions(void *, walk_memory_regions_fn);

int page_get_flags(target_ulong address);
void page_set_flags(target_ulong start, target_ulong end, int flags);
int page_check_range(target_ulong start, target_ulong len, int flags);
#endif

void QEMU_NORETURN cpu_abort(CPUArchState *env, const char *fmt, ...)
    GCC_FMT_ATTR(2, 3);


#define CPU_INTERRUPT_HARD        0x0002

#define CPU_INTERRUPT_EXITTB      0x0004

#define CPU_INTERRUPT_HALT        0x0020

#define CPU_INTERRUPT_DEBUG       0x0080

#define CPU_INTERRUPT_TGT_EXT_0   0x0008
#define CPU_INTERRUPT_TGT_EXT_1   0x0010
#define CPU_INTERRUPT_TGT_EXT_2   0x0040
#define CPU_INTERRUPT_TGT_EXT_3   0x0200
#define CPU_INTERRUPT_TGT_EXT_4   0x1000

#define CPU_INTERRUPT_TGT_INT_0   0x0100
#define CPU_INTERRUPT_TGT_INT_1   0x0400
#define CPU_INTERRUPT_TGT_INT_2   0x0800
#define CPU_INTERRUPT_TGT_INT_3   0x2000


#define CPU_INTERRUPT_SSTEP_MASK \
    (CPU_INTERRUPT_HARD          \
     | CPU_INTERRUPT_TGT_EXT_0   \
     | CPU_INTERRUPT_TGT_EXT_1   \
     | CPU_INTERRUPT_TGT_EXT_2   \
     | CPU_INTERRUPT_TGT_EXT_3   \
     | CPU_INTERRUPT_TGT_EXT_4)

#define BP_MEM_READ           0x01
#define BP_MEM_WRITE          0x02
#define BP_MEM_ACCESS         (BP_MEM_READ | BP_MEM_WRITE)
#define BP_STOP_BEFORE_ACCESS 0x04
#define BP_WATCHPOINT_HIT     0x08
#define BP_GDB                0x10
#define BP_CPU                0x20

int cpu_breakpoint_insert(CPUArchState *env, target_ulong pc, int flags,
                          CPUBreakpoint **breakpoint);
int cpu_breakpoint_remove(CPUArchState *env, target_ulong pc, int flags);
void cpu_breakpoint_remove_by_ref(CPUArchState *env, CPUBreakpoint *breakpoint);
void cpu_breakpoint_remove_all(CPUArchState *env, int mask);
int cpu_watchpoint_insert(CPUArchState *env, target_ulong addr, target_ulong len,
                          int flags, CPUWatchpoint **watchpoint);
int cpu_watchpoint_remove(CPUArchState *env, target_ulong addr,
                          target_ulong len, int flags);
void cpu_watchpoint_remove_by_ref(CPUArchState *env, CPUWatchpoint *watchpoint);
void cpu_watchpoint_remove_all(CPUArchState *env, int mask);

#define SSTEP_ENABLE  0x1  
#define SSTEP_NOIRQ   0x2  
#define SSTEP_NOTIMER 0x4  

void cpu_single_step(CPUState *cpu, int enabled);

#include "exec/ioport.h"

hwaddr cpu_get_phys_page_debug(CPUArchState *env, target_ulong addr);


extern int phys_ram_fd;
extern ram_addr_t ram_size;

#define RAM_PREALLOC_MASK   (1 << 0)

typedef struct RAMBlock {
    uint8_t *host;
    ram_addr_t offset;
    ram_addr_t length;
    uint32_t flags;
    char idstr[256];
    QTAILQ_ENTRY(RAMBlock) next;
    int fd;
} RAMBlock;

typedef struct RAMList {
    QemuMutex mutex;
    uint8_t *phys_dirty;
    RAMBlock *mru_block;
    QTAILQ_HEAD(ram, RAMBlock) blocks;
    uint32_t version;
} RAMList;
extern RAMList ram_list;

extern const char *mem_path;
extern int mem_prealloc;


#define TLB_INVALID_MASK   (1 << 3)
#define TLB_NOTDIRTY    (1 << 4)
#define TLB_MMIO        (1 << 5)

#define VGA_DIRTY_FLAG       0x01
#define CODE_DIRTY_FLAG      0x02
#define MIGRATION_DIRTY_FLAG 0x08

static inline int cpu_physical_memory_is_dirty(ram_addr_t addr)
{
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS] == 0xff;
}

static inline int cpu_physical_memory_get_dirty_flags(ram_addr_t addr)
{
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS];
}

static inline int cpu_physical_memory_get_dirty(ram_addr_t addr,
                                                int dirty_flags)
{
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS] & dirty_flags;
}

static inline void cpu_physical_memory_set_dirty(ram_addr_t addr)
{
    ram_list.phys_dirty[addr >> TARGET_PAGE_BITS] = 0xff;
}

static inline int cpu_physical_memory_set_dirty_flags(ram_addr_t addr,
                                                      int dirty_flags)
{
    return ram_list.phys_dirty[addr >> TARGET_PAGE_BITS] |= dirty_flags;
}

static inline void cpu_physical_memory_mask_dirty_range(ram_addr_t start,
                                                        int length,
                                                        int dirty_flags)
{
    int i, mask, len;
    uint8_t *p;

    len = length >> TARGET_PAGE_BITS;
    mask = ~dirty_flags;
    p = ram_list.phys_dirty + (start >> TARGET_PAGE_BITS);
    for (i = 0; i < len; i++) {
        p[i] &= mask;
    }
}

void cpu_physical_memory_reset_dirty(ram_addr_t start, ram_addr_t end,
                                     int dirty_flags);
void cpu_tlb_update_dirty(CPUArchState *env);

int cpu_physical_memory_set_dirty_tracking(int enable);

int cpu_physical_memory_get_dirty_tracking(void);

int cpu_physical_sync_dirty_bitmap(hwaddr start_addr,
                                   hwaddr end_addr);

void dump_exec_info(FILE *f,
                    int (*cpu_fprintf)(FILE *f, const char *fmt, ...));

void qemu_register_coalesced_mmio(hwaddr addr, ram_addr_t size);

void qemu_unregister_coalesced_mmio(hwaddr addr, ram_addr_t size);

void qemu_flush_coalesced_mmio_buffer(void);


#ifdef CONFIG_PROFILER
static inline int64_t profile_getclock(void)
{
    return cpu_get_real_ticks();
}

extern int64_t qemu_time, qemu_time_start;
extern int64_t tlb_flush_time;
extern int64_t dev_time;
#endif

int cpu_memory_rw_debug(CPUState *cpu, target_ulong addr,
                        void *buf, int len, int is_write);

void cpu_inject_x86_mce(CPUArchState *cenv, int bank, uint64_t status,
                        uint64_t mcg_status, uint64_t addr, uint64_t misc);

#endif 

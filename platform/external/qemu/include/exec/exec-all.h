/*
 * internal execution defines for qemu
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

#ifndef _EXEC_ALL_H_
#define _EXEC_ALL_H_

#include "qemu-common.h"
#include "exec/cpu-common.h"
#include "exec/cpu-all.h"

#define DEBUG_DISAS

#if defined(CONFIG_USER_ONLY)
typedef abi_ulong tb_page_addr_t;
#else
typedef ram_addr_t tb_page_addr_t;
#endif

#define DISAS_NEXT    0 
#define DISAS_JUMP    1 
#define DISAS_UPDATE  2 
#define DISAS_TB_JUMP 3 

struct TranslationBlock;
typedef struct TranslationBlock TranslationBlock;

#define MAX_OP_PER_INSTR 208

#if HOST_LONG_BITS == 32
#define MAX_OPC_PARAM_PER_ARG 2
#else
#define MAX_OPC_PARAM_PER_ARG 1
#endif
#define MAX_OPC_PARAM_IARGS 5
#define MAX_OPC_PARAM_OARGS 1
#define MAX_OPC_PARAM_ARGS (MAX_OPC_PARAM_IARGS + MAX_OPC_PARAM_OARGS)

#define MAX_OPC_PARAM (4 + (MAX_OPC_PARAM_PER_ARG * MAX_OPC_PARAM_ARGS))
#define OPC_BUF_SIZE 2048
#define OPC_MAX_SIZE (OPC_BUF_SIZE - MAX_OP_PER_INSTR)

#define TCG_MAX_OP_SIZE 192

#define OPPARAM_BUF_SIZE (OPC_BUF_SIZE * MAX_OPC_PARAM)

#include "qemu/log.h"

void gen_intermediate_code(CPUArchState *env, struct TranslationBlock *tb);
void gen_intermediate_code_pc(CPUArchState *env, struct TranslationBlock *tb);
void restore_state_to_opc(CPUArchState *env, struct TranslationBlock *tb,
                          int pc_pos);

unsigned long code_gen_max_block_size(void);
void cpu_gen_init(void);
void tcg_exec_init(unsigned long tb_size);
int cpu_gen_code(CPUArchState *env, struct TranslationBlock *tb,
                 int *gen_code_size_ptr);
bool cpu_restore_state(CPUArchState *env, uintptr_t searched_pc);

void QEMU_NORETURN cpu_resume_from_signal(CPUArchState *env1, void *puc);
void QEMU_NORETURN cpu_io_recompile(CPUArchState *env, uintptr_t retaddr);
TranslationBlock *tb_gen_code(CPUArchState *env, 
                              target_ulong pc, target_ulong cs_base, int flags,
                              int cflags);
void cpu_exec_init(CPUArchState *env);
void QEMU_NORETURN cpu_loop_exit(CPUArchState *env1);
int page_unprotect(target_ulong address, uintptr_t pc, void *puc);
void tb_invalidate_phys_page_range(tb_page_addr_t start, tb_page_addr_t end,
                                   int is_cpu_write_access);
void tb_invalidate_phys_range(tb_page_addr_t start, tb_page_addr_t end,
                              int is_cpu_write_access);
#if !defined(CONFIG_USER_ONLY)
void tlb_flush_page(CPUArchState *env, target_ulong addr);
void tlb_flush(CPUArchState *env, int flush_global);
void tlb_set_page(CPUArchState *env, target_ulong vaddr,
                  hwaddr paddr, int prot,
                  int mmu_idx, target_ulong size);
void tb_reset_jump_recursive(TranslationBlock *tb);
void tb_invalidate_phys_addr(hwaddr addr);
#else
static inline void tlb_flush_page(CPUArchState *env, target_ulong addr)
{
}

static inline void tlb_flush(CPUArchState *env, int flush_global)
{
}
#endif

typedef struct PhysPageDesc {
    
    ram_addr_t phys_offset;
    ram_addr_t region_offset;
} PhysPageDesc;

PhysPageDesc *phys_page_find(hwaddr index);
PhysPageDesc *phys_page_find_alloc(hwaddr index, int alloc);

int io_mem_watch;

#define CODE_GEN_ALIGN           16 

#define CODE_GEN_PHYS_HASH_BITS     15
#define CODE_GEN_PHYS_HASH_SIZE     (1 << CODE_GEN_PHYS_HASH_BITS)

#if defined(CONFIG_SOFTMMU)
#define CODE_GEN_AVG_BLOCK_SIZE 128
#else
#define CODE_GEN_AVG_BLOCK_SIZE 64
#endif

#if defined(__arm__) || defined(_ARCH_PPC) \
    || defined(__x86_64__) || defined(__i386__) \
    || defined(__sparc__) || defined(__aarch64__) \
    || defined(CONFIG_TCG_INTERPRETER)
#define USE_DIRECT_JUMP
#endif

struct TranslationBlock {
    target_ulong pc;   
    target_ulong cs_base; 
    uint64_t flags; 
    uint16_t size;      
    uint16_t cflags;    
#define CF_COUNT_MASK  0x7fff
#define CF_LAST_IO     0x8000 

    uint8_t *tc_ptr;    
    
    struct TranslationBlock *phys_hash_next;
    struct TranslationBlock *page_next[2];
    tb_page_addr_t page_addr[2];

    uint16_t tb_next_offset[2]; 
#ifdef USE_DIRECT_JUMP
    uint16_t tb_jmp_offset[4]; 
#else
    uintptr_t tb_next[2]; 
#endif
    struct TranslationBlock *jmp_next[2];
    struct TranslationBlock *jmp_first;
    uint32_t icount;
};

#include "exec/spinlock.h"

typedef struct TBContext TBContext;

struct TBContext {

    TranslationBlock *tbs;
    TranslationBlock *tb_phys_hash[CODE_GEN_PHYS_HASH_SIZE];
    int nb_tbs;
    
    spinlock_t tb_lock;

    
    int tb_flush_count;
    int tb_phys_invalidate_count;

    int tb_invalidated_flag;
};

static inline unsigned int tb_jmp_cache_hash_page(target_ulong pc)
{
    target_ulong tmp;
    tmp = pc ^ (pc >> (TARGET_PAGE_BITS - TB_JMP_PAGE_BITS));
    return (tmp >> (TARGET_PAGE_BITS - TB_JMP_PAGE_BITS)) & TB_JMP_PAGE_MASK;
}

static inline unsigned int tb_jmp_cache_hash_func(target_ulong pc)
{
    target_ulong tmp;
    tmp = pc ^ (pc >> (TARGET_PAGE_BITS - TB_JMP_PAGE_BITS));
    return (((tmp >> (TARGET_PAGE_BITS - TB_JMP_PAGE_BITS)) & TB_JMP_PAGE_MASK)
	    | (tmp & TB_JMP_ADDR_MASK));
}

static inline unsigned int tb_phys_hash_func(tb_page_addr_t pc)
{
    return (pc >> 2) & (CODE_GEN_PHYS_HASH_SIZE - 1);
}

void tb_free(TranslationBlock *tb);
void tb_flush(CPUArchState *env);
void tb_link_phys(TranslationBlock *tb,
                  target_ulong phys_pc, target_ulong phys_page2);
void tb_phys_invalidate(TranslationBlock *tb, tb_page_addr_t page_addr);
void tb_invalidate_phys_page_fast0(hwaddr start, int len);

extern uint8_t *code_gen_ptr;
extern int code_gen_max_blocks;

#if defined(USE_DIRECT_JUMP)

#if defined(CONFIG_TCG_INTERPRETER)
static inline void tb_set_jmp_target1(uintptr_t jmp_addr, uintptr_t addr)
{
    
    *(uint32_t *)jmp_addr = addr - (jmp_addr + 4);
    
}
#elif defined(_ARCH_PPC)
void ppc_tb_set_jmp_target(unsigned long jmp_addr, unsigned long addr);
#define tb_set_jmp_target1 ppc_tb_set_jmp_target
#elif defined(__i386__) || defined(__x86_64__)
static inline void tb_set_jmp_target1(uintptr_t jmp_addr, uintptr_t addr)
{
    
    *(uint32_t *)jmp_addr = addr - (jmp_addr + 4);
    
}
#elif defined(__aarch64__)
void aarch64_tb_set_jmp_target(uintptr_t jmp_addr, uintptr_t addr);
#define tb_set_jmp_target1 aarch64_tb_set_jmp_target
#elif defined(__arm__)
static inline void tb_set_jmp_target1(uintptr_t jmp_addr, uintptr_t addr)
{
#if !QEMU_GNUC_PREREQ(4, 1)
    register unsigned long _beg __asm ("a1");
    register unsigned long _end __asm ("a2");
    register unsigned long _flg __asm ("a3");
#endif

    
    *(uint32_t *)jmp_addr =
        (*(uint32_t *)jmp_addr & ~0xffffff)
        | (((addr - (jmp_addr + 8)) >> 2) & 0xffffff);

#if QEMU_GNUC_PREREQ(4, 1)
    __builtin___clear_cache((char *) jmp_addr, (char *) jmp_addr + 4);
#else
    
    _beg = jmp_addr;
    _end = jmp_addr + 4;
    _flg = 0;
    __asm __volatile__ ("swi 0x9f0002" : : "r" (_beg), "r" (_end), "r" (_flg));
#endif
}
#elif defined(__sparc__)
void tb_set_jmp_target1(uintptr_t jmp_addr, uintptr_t addr);
#else
#error tb_set_jmp_target1 is missing
#endif

static inline void tb_set_jmp_target(TranslationBlock *tb,
                                     int n, uintptr_t addr)
{
    uint16_t offset = tb->tb_jmp_offset[n];
    tb_set_jmp_target1((uintptr_t)(tb->tc_ptr + offset), addr);
    offset = tb->tb_jmp_offset[n + 2];
    if (offset != 0xffff)
        tb_set_jmp_target1((uintptr_t)(tb->tc_ptr + offset), addr);
}

#else

static inline void tb_set_jmp_target(TranslationBlock *tb,
                                     int n, uintptr_t addr)
{
    tb->tb_next[n] = addr;
}

#endif

static inline void tb_add_jump(TranslationBlock *tb, int n,
                               TranslationBlock *tb_next)
{
    
    if (!tb->jmp_next[n]) {
        
        tb_set_jmp_target(tb, n, (uintptr_t)tb_next->tc_ptr);

        
        tb->jmp_next[n] = tb_next->jmp_first;
        tb_next->jmp_first = (TranslationBlock *)((uintptr_t)(tb) | (n));
    }
}

#if defined(CONFIG_TCG_INTERPRETER)
extern uintptr_t tci_tb_ptr;
# define GETRA() tci_tb_ptr
#else
# define GETRA() \
    ((uintptr_t)__builtin_extract_return_addr(__builtin_return_address(0)))
#endif

#if defined(CONFIG_TCG_INTERPRETER)
# define GETPC_ADJ   0
#else
# define GETPC_ADJ   2
#endif

#define GETPC()  (GETRA() - GETPC_ADJ)

#if !defined(CONFIG_USER_ONLY)

void phys_mem_set_alloc(void *(*alloc)(size_t));

TranslationBlock *tb_find_pc(uintptr_t pc_ptr);

uint64_t io_mem_read(int index, hwaddr addr, unsigned size);
void io_mem_write(int index, hwaddr addr, uint64_t value, unsigned size);

extern CPUWriteMemoryFunc *_io_mem_write[IO_MEM_NB_ENTRIES][4];
extern CPUReadMemoryFunc *_io_mem_read[IO_MEM_NB_ENTRIES][4];
extern void *io_mem_opaque[IO_MEM_NB_ENTRIES];

void tlb_fill(CPUArchState *env1, target_ulong addr, int is_write, int mmu_idx,
              uintptr_t retaddr);

uint8_t helper_ldb_cmmu(CPUArchState *env, target_ulong addr, int mmu_idx);
uint16_t helper_ldw_cmmu(CPUArchState *env, target_ulong addr, int mmu_idx);
uint32_t helper_ldl_cmmu(CPUArchState *env, target_ulong addr, int mmu_idx);
uint64_t helper_ldq_cmmu(CPUArchState *env, target_ulong addr, int mmu_idx);

#define ACCESS_TYPE (NB_MMU_MODES + 1)
#define MEMSUFFIX _code

#define DATA_SIZE 1
#include "exec/softmmu_header.h"

#define DATA_SIZE 2
#include "exec/softmmu_header.h"

#define DATA_SIZE 4
#include "exec/softmmu_header.h"

#define DATA_SIZE 8
#include "exec/softmmu_header.h"

#undef ACCESS_TYPE
#undef MEMSUFFIX

#endif

#if defined(CONFIG_USER_ONLY)
static inline tb_page_addr_t get_page_addr_code(CPUArchState *env1, target_ulong addr)
{
    return addr;
}
#else
tb_page_addr_t get_page_addr_code(CPUArchState *env1, target_ulong addr);
#endif

typedef void (CPUDebugExcpHandler)(CPUArchState *env);

void cpu_set_debug_excp_handler(CPUDebugExcpHandler *handler);

extern int singlestep;

extern volatile sig_atomic_t exit_request;

static inline int can_do_io(CPUArchState *env)
{
    if (!use_icount) {
        return 1;
    }
    
    if (env->current_tb == NULL) {
        return 1;
    }
    return env->can_do_io != 0;
}

#endif

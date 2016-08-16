/*
 * ARM virtual CPU header
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
#ifndef CPU_ARM_H
#define CPU_ARM_H

#include "config.h"

#include "kvm-consts.h"

#if defined(TARGET_AARCH64)
  
#  define TARGET_LONG_BITS 64
#  define ELF_MACHINE EM_AARCH64
#else
#  define TARGET_LONG_BITS 32
#  define ELF_MACHINE EM_ARM
#endif

#define CPUOldState struct CPUARMState

#define CPUArchState struct CPUARMState

#include "qemu-common.h"
#include "exec/cpu-defs.h"

#include "fpu/softfloat.h"

#define TARGET_HAS_ICE 1

#define EXCP_UDEF            1   
#define EXCP_SWI             2   
#define EXCP_PREFETCH_ABORT  3
#define EXCP_DATA_ABORT      4
#define EXCP_IRQ             5
#define EXCP_FIQ             6
#define EXCP_BKPT            7
#define EXCP_EXCEPTION_EXIT  8   
#define EXCP_KERNEL_TRAP     9   
#define EXCP_STREX          10
#define EXCP_SMC            11   

#define ARMV7M_EXCP_RESET   1
#define ARMV7M_EXCP_NMI     2
#define ARMV7M_EXCP_HARD    3
#define ARMV7M_EXCP_MEM     4
#define ARMV7M_EXCP_BUS     5
#define ARMV7M_EXCP_USAGE   6
#define ARMV7M_EXCP_SVC     11
#define ARMV7M_EXCP_DEBUG   12
#define ARMV7M_EXCP_PENDSV  14
#define ARMV7M_EXCP_SYSTICK 15

#define CPU_INTERRUPT_FIQ   CPU_INTERRUPT_TGT_EXT_1

#define ARM_CPU_IRQ 0
#define ARM_CPU_FIQ 1

typedef void ARMWriteCPFunc(void *opaque, int cp_info,
                            int srcreg, int operand, uint32_t value,
                            void *retaddr);
typedef uint32_t ARMReadCPFunc(void *opaque, int cp_info,
                               int dstreg, int operand,
                               void *retaddr);

struct arm_boot_info;

#define NB_MMU_MODES 2


typedef struct ARMGenericTimer {
    uint64_t cval; 
    uint32_t ctl; 
} ARMGenericTimer;

#define GTIMER_PHYS 0
#define GTIMER_VIRT 1
#define NUM_GTIMERS 2

#define GTIMER_SCALE 16

typedef struct CPUARMState {
    
    uint32_t regs[16];
    uint32_t uncached_cpsr;
    uint32_t spsr;

    
    uint32_t banked_spsr[7];
    uint32_t banked_r13[7];
    uint32_t banked_r14[7];

    
    uint32_t usr_regs[5];
    uint32_t fiq_regs[5];

    
    uint32_t CF; 
    uint32_t VF; 
    uint32_t NF; 
    uint32_t ZF; 
    uint32_t QF; 
    uint32_t GE; 
    uint32_t thumb; 
    uint32_t condexec_bits; 

    
    struct {
        uint32_t c0_cpuid;
        uint32_t c0_cachetype;
        uint32_t c0_ccsid[16]; 
        uint32_t c0_clid; 
        uint32_t c0_cssel; 
        uint32_t c0_c1[8]; 
        uint32_t c0_c2[8]; 
        uint32_t c1_sys; 
        uint32_t c1_coproc; 
        uint32_t c1_xscaleauxcr; 
        uint32_t c1_secfg; 
        uint32_t c1_sedbg; 
        uint32_t c1_nseac; 
        uint32_t c2_base0; 
        uint32_t c2_base1; 
        uint32_t c2_control; 
        uint32_t c2_mask; 
        uint32_t c2_base_mask; 
        uint32_t c2_data; 
        uint32_t c2_insn; 
        uint32_t c3; 
        uint32_t c5_insn; 
        uint32_t c5_data;
        uint32_t c6_region[8]; 
        uint32_t c6_insn; 
        uint32_t c6_data;
        uint32_t c7_par;  
        uint32_t c9_insn; 
        uint32_t c9_data;
        uint32_t c9_pmcr; 
        uint32_t c9_pmcnten; 
        uint32_t c9_pmovsr; 
        uint32_t c9_pmxevtyper; 
        uint32_t c9_pmuserenr; 
        uint32_t c9_pminten; 
        uint32_t c12_vbar; 
        uint32_t c12_mvbar; 
        uint32_t c13_fcse; 
        uint32_t c13_context; 
        uint32_t c13_tls1; 
        uint32_t c13_tls2; 
        uint32_t c13_tls3; 
        uint32_t c15_cpar; 
        uint32_t c15_ticonfig; 
        uint32_t c15_i_max; 
        uint32_t c15_i_min; 
        uint32_t c15_threadid; 
    } cp15;

    struct {
        uint32_t other_sp;
        uint32_t vecbase;
        uint32_t basepri;
        uint32_t control;
        int current_sp;
        int exception;
        int pending_exception;
    } v7m;

    
    uint32_t cp14_dbgdidr;

    
    uint32_t teecr;
    uint32_t teehbr;

    
    uint32_t features;

    
    struct {
        float64 regs[32];

        uint32_t xregs[16];
        
        int vec_len;
        int vec_stride;

        
        uint32_t scratch[8];

        float_status fp_status;
        float_status standard_fp_status;
    } vfp;
    uint32_t exclusive_addr;
    uint32_t exclusive_val;
    uint32_t exclusive_high;
#if defined(CONFIG_USER_ONLY)
    uint32_t exclusive_test;
    uint32_t exclusive_info;
#endif

    
    struct {
        uint64_t regs[16];
        uint64_t val;

        uint32_t cregs[16];
    } iwmmxt;

#if defined(CONFIG_USER_ONLY)
    
    int eabi;
#endif

    CPU_COMMON

    

    
    struct {
        ARMReadCPFunc *cp_read;
        ARMWriteCPFunc *cp_write;
        void *opaque;
    } cp[15];
    void *nvic;
    const struct arm_boot_info *boot_info;
} CPUARMState;

#include "cpu-qom.h"

CPUARMState *cpu_arm_init(const char *cpu_model);
void arm_translate_init(void);
int cpu_arm_exec(CPUARMState *s);
void cpu_arm_close(CPUARMState *s);
void do_interrupt(CPUARMState *);
void switch_mode(CPUARMState *, int);
uint32_t do_arm_semihosting(CPUARMState *env);

static inline bool is_a64(CPUARMState *env)
{
#ifdef CONFIG_ANDROID 
    return 0;
#else
    return env->aarch64;
#endif
}

#define PSTATE_N_SHIFT 3
#define PSTATE_N  (1 << PSTATE_N_SHIFT)
#define PSTATE_Z_SHIFT 2
#define PSTATE_Z  (1 << PSTATE_Z_SHIFT)
#define PSTATE_C_SHIFT 1
#define PSTATE_C  (1 << PSTATE_C_SHIFT)
#define PSTATE_V_SHIFT 0
#define PSTATE_V  (1 << PSTATE_V_SHIFT)

int cpu_arm_signal_handler(int host_signum, void *pinfo,
                           void *puc);
int cpu_arm_handle_mmu_fault (CPUARMState *env, target_ulong address, int rw,
                              int mmu_idx);
#define cpu_handle_mmu_fault cpu_arm_handle_mmu_fault

static inline void cpu_set_tls(CPUARMState *env, target_ulong newtls)
{
  env->cp15.c13_tls2 = newtls;
}

#define CPSR_M (0x1fU)
#define CPSR_T (1U << 5)
#define CPSR_F (1U << 6)
#define CPSR_I (1U << 7)
#define CPSR_A (1U << 8)
#define CPSR_E (1U << 9)
#define CPSR_IT_2_7 (0xfc00U)
#define CPSR_GE (0xfU << 16)
#define CPSR_RESERVED (0xfU << 20)
#define CPSR_J (1U << 24)
#define CPSR_IT_0_1 (3U << 25)
#define CPSR_Q (1U << 27)
#define CPSR_V (1U << 28)
#define CPSR_C (1U << 29)
#define CPSR_Z (1U << 30)
#define CPSR_N (1U << 31)
#define CPSR_NZCV (CPSR_N | CPSR_Z | CPSR_C | CPSR_V)

#define CPSR_IT (CPSR_IT_0_1 | CPSR_IT_2_7)
#define CACHED_CPSR_BITS (CPSR_T | CPSR_GE | CPSR_IT | CPSR_Q | CPSR_NZCV)
#define CPSR_USER (CPSR_NZCV | CPSR_Q | CPSR_GE)
#define CPSR_EXEC (CPSR_T | CPSR_IT | CPSR_J)

uint32_t cpsr_read(CPUARMState *env);
void cpsr_write(CPUARMState *env, uint32_t val, uint32_t mask);

static inline uint32_t xpsr_read(CPUARMState *env)
{
    int ZF;
    ZF = (env->ZF == 0);
    return (env->NF & 0x80000000) | (ZF << 30)
        | (env->CF << 29) | ((env->VF & 0x80000000) >> 3) | (env->QF << 27)
        | (env->thumb << 24) | ((env->condexec_bits & 3) << 25)
        | ((env->condexec_bits & 0xfc) << 8)
        | env->v7m.exception;
}

static inline void xpsr_write(CPUARMState *env, uint32_t val, uint32_t mask)
{
    if (mask & CPSR_NZCV) {
        env->ZF = (~val) & CPSR_Z;
        env->NF = val;
        env->CF = (val >> 29) & 1;
        env->VF = (val << 3) & 0x80000000;
    }
    if (mask & CPSR_Q)
        env->QF = ((val & CPSR_Q) != 0);
    if (mask & (1 << 24))
        env->thumb = ((val & (1 << 24)) != 0);
    if (mask & CPSR_IT_0_1) {
        env->condexec_bits &= ~3;
        env->condexec_bits |= (val >> 25) & 3;
    }
    if (mask & CPSR_IT_2_7) {
        env->condexec_bits &= 3;
        env->condexec_bits |= (val >> 8) & 0xfc;
    }
    if (mask & 0x1ff) {
        env->v7m.exception = val & 0x1ff;
    }
}

uint32_t vfp_get_fpscr(CPUARMState *env);
void vfp_set_fpscr(CPUARMState *env, uint32_t val);

enum arm_cpu_mode {
  ARM_CPU_MODE_USR = 0x10,
  ARM_CPU_MODE_FIQ = 0x11,
  ARM_CPU_MODE_IRQ = 0x12,
  ARM_CPU_MODE_SVC = 0x13,
  ARM_CPU_MODE_SMC = 0x16,
  ARM_CPU_MODE_ABT = 0x17,
  ARM_CPU_MODE_UND = 0x1b,
  ARM_CPU_MODE_SYS = 0x1f
};

#define ARM_VFP_FPSID   0
#define ARM_VFP_FPSCR   1
#define ARM_VFP_MVFR1   6
#define ARM_VFP_MVFR0   7
#define ARM_VFP_FPEXC   8
#define ARM_VFP_FPINST  9
#define ARM_VFP_FPINST2 10

#define ARM_IWMMXT_wCID		0
#define ARM_IWMMXT_wCon		1
#define ARM_IWMMXT_wCSSF	2
#define ARM_IWMMXT_wCASF	3
#define ARM_IWMMXT_wCGR0	8
#define ARM_IWMMXT_wCGR1	9
#define ARM_IWMMXT_wCGR2	10
#define ARM_IWMMXT_wCGR3	11

enum arm_features {
    ARM_FEATURE_VFP,
    ARM_FEATURE_AUXCR,  
    ARM_FEATURE_XSCALE, 
    ARM_FEATURE_IWMMXT, 
    ARM_FEATURE_V6,
    ARM_FEATURE_V6K,
    ARM_FEATURE_V7,
    ARM_FEATURE_THUMB2,
    ARM_FEATURE_MPU,    
    ARM_FEATURE_VFP3,
    ARM_FEATURE_VFP_FP16,
    ARM_FEATURE_NEON,
    ARM_FEATURE_DIV,
    ARM_FEATURE_M, 
    ARM_FEATURE_OMAPCP, 
    ARM_FEATURE_THUMB2EE,
    ARM_FEATURE_V7MP,    
    ARM_FEATURE_V4T,
    ARM_FEATURE_V5,
    ARM_FEATURE_STRONGARM,
    ARM_FEATURE_VAPA, 
    ARM_FEATURE_TRUSTZONE, 
};

static inline int arm_feature(CPUARMState *env, int feature)
{
    return (env->features & (1ULL << feature)) != 0;
}

void arm_cpu_list(FILE *f, fprintf_function cpu_fprintf);

void armv7m_nvic_set_pending(void *opaque, int irq);
int armv7m_nvic_acknowledge_irq(void *opaque);
void armv7m_nvic_complete_irq(void *opaque, int irq);


#define ENCODE_CP_REG(cp, is64, crn, crm, opc1, opc2)   \
    (((cp) << 16) | ((is64) << 15) | ((crn) << 11) |    \
     ((crm) << 7) | ((opc1) << 3) | (opc2))

static inline uint32_t kvm_to_cpreg_id(uint64_t kvmid)
{
    uint32_t cpregid = kvmid;
    if ((kvmid & CP_REG_SIZE_MASK) == CP_REG_SIZE_U64) {
        cpregid |= (1 << 15);
    }
    return cpregid;
}

static inline uint64_t cpreg_to_kvm_id(uint32_t cpregid)
{
    uint64_t kvmid = cpregid & ~(1 << 15);
    if (cpregid & (1 << 15)) {
        kvmid |= CP_REG_SIZE_U64 | CP_REG_ARM;
    } else {
        kvmid |= CP_REG_SIZE_U32 | CP_REG_ARM;
    }
    return kvmid;
}

#define ARM_CP_SPECIAL 1
#define ARM_CP_CONST 2
#define ARM_CP_64BIT 4
#define ARM_CP_SUPPRESS_TB_END 8
#define ARM_CP_OVERRIDE 16
#define ARM_CP_NO_MIGRATE 32
#define ARM_CP_IO 64
#define ARM_CP_NOP (ARM_CP_SPECIAL | (1 << 8))
#define ARM_CP_WFI (ARM_CP_SPECIAL | (2 << 8))
#define ARM_LAST_SPECIAL ARM_CP_WFI
#define ARM_CP_SENTINEL 0xffff
#define ARM_CP_FLAG_MASK 0x7f

static inline bool cptype_valid(int cptype)
{
    return ((cptype & ~ARM_CP_FLAG_MASK) == 0)
        || ((cptype & ARM_CP_SPECIAL) &&
            ((cptype & ~ARM_CP_FLAG_MASK) <= ARM_LAST_SPECIAL));
}

#define PL3_R 0x80
#define PL3_W 0x40
#define PL2_R (0x20 | PL3_R)
#define PL2_W (0x10 | PL3_W)
#define PL1_R (0x08 | PL2_R)
#define PL1_W (0x04 | PL2_W)
#define PL0_R (0x02 | PL1_R)
#define PL0_W (0x01 | PL1_W)

#define PL3_RW (PL3_R | PL3_W)
#define PL2_RW (PL2_R | PL2_W)
#define PL1_RW (PL1_R | PL1_W)
#define PL0_RW (PL0_R | PL0_W)

static inline int arm_current_pl(CPUARMState *env)
{
    if ((env->uncached_cpsr & 0x1f) == ARM_CPU_MODE_USR) {
        return 0;
    }
    return 1;
}

typedef struct ARMCPRegInfo ARMCPRegInfo;

/* Access functions for coprocessor registers. These should return
 * 0 on success, or one of the EXCP_* constants if access should cause
 * an exception (in which case *value is not written).
 */
typedef int CPReadFn(CPUARMState *env, const ARMCPRegInfo *opaque,
                     uint64_t *value);
typedef int CPWriteFn(CPUARMState *env, const ARMCPRegInfo *opaque,
                      uint64_t value);
typedef void CPResetFn(CPUARMState *env, const ARMCPRegInfo *opaque);

#define CP_ANY 0xff

struct ARMCPRegInfo {
    
    const char *name;
    uint8_t cp;
    uint8_t crn;
    uint8_t crm;
    uint8_t opc1;
    uint8_t opc2;
    
    int type;
    
    int access;
    void *opaque;
    uint64_t resetvalue;
    ptrdiff_t fieldoffset; 
    CPReadFn *readfn;
    CPWriteFn *writefn;
    CPReadFn *raw_readfn;
    CPWriteFn *raw_writefn;
    CPResetFn *resetfn;
};

#define CPREG_FIELD32(env, ri) \
    (*(uint32_t *)((char *)(env) + (ri)->fieldoffset))
#define CPREG_FIELD64(env, ri) \
    (*(uint64_t *)((char *)(env) + (ri)->fieldoffset))

#define REGINFO_SENTINEL { .type = ARM_CP_SENTINEL }

#ifndef CONFIG_ANDROID  
void define_arm_cp_regs_with_opaque(ARMCPU *cpu,
                                    const ARMCPRegInfo *regs, void *opaque);
void define_one_arm_cp_reg_with_opaque(ARMCPU *cpu,
                                       const ARMCPRegInfo *regs, void *opaque);
static inline void define_arm_cp_regs(ARMCPU *cpu, const ARMCPRegInfo *regs)
{
    define_arm_cp_regs_with_opaque(cpu, regs, 0);
}
static inline void define_one_arm_cp_reg(ARMCPU *cpu, const ARMCPRegInfo *regs)
{
    define_one_arm_cp_reg_with_opaque(cpu, regs, 0);
}
const ARMCPRegInfo *get_arm_cp_reginfo(ARMCPU *cpu, uint32_t encoded_cp);
#endif  

int arm_cp_write_ignore(CPUARMState *env, const ARMCPRegInfo *ri,
                        uint64_t value);
int arm_cp_read_zero(CPUARMState *env, const ARMCPRegInfo *ri, uint64_t *value);

static inline bool cp_access_ok(CPUARMState *env,
                                const ARMCPRegInfo *ri, int isread)
{
    return (ri->access >> ((arm_current_pl(env) * 2) + isread)) & 1;
}

#ifndef CONFIG_ANDROID  
/**
 * write_list_to_cpustate
 * @cpu: ARMCPU
 *
 * For each register listed in the ARMCPU cpreg_indexes list, write
 * its value from the cpreg_values list into the ARMCPUARMState structure.
 * This updates TCG's working data structures from KVM data or
 * from incoming migration state.
 *
 * Returns: true if all register values were updated correctly,
 * false if some register was unknown or could not be written.
 * Note that we do not stop early on failure -- we will attempt
 * writing all registers in the list.
 */
bool write_list_to_cpustate(ARMCPU *cpu);

bool write_cpustate_to_list(ARMCPU *cpu);
#endif  

void cpu_arm_set_cp_io(CPUARMState *env, int cpnum,
                       ARMReadCPFunc *cp_read, ARMWriteCPFunc *cp_write,
                       void *opaque);


#define IS_M(env) arm_feature(env, ARM_FEATURE_M)
#define ARM_CPUID(env) (env->cp15.c0_cpuid)

#define ARM_CPUID_ARM1026     0x4106a262
#define ARM_CPUID_ARM926      0x41069265
#define ARM_CPUID_ARM946      0x41059461
#define ARM_CPUID_TI915T      0x54029152
#define ARM_CPUID_TI925T      0x54029252
#define ARM_CPUID_SA1100      0x4401A11B
#define ARM_CPUID_SA1110      0x6901B119
#define ARM_CPUID_PXA250      0x69052100
#define ARM_CPUID_PXA255      0x69052d00
#define ARM_CPUID_PXA260      0x69052903
#define ARM_CPUID_PXA261      0x69052d05
#define ARM_CPUID_PXA262      0x69052d06
#define ARM_CPUID_PXA270      0x69054110
#define ARM_CPUID_PXA270_A0   0x69054110
#define ARM_CPUID_PXA270_A1   0x69054111
#define ARM_CPUID_PXA270_B0   0x69054112
#define ARM_CPUID_PXA270_B1   0x69054113
#define ARM_CPUID_PXA270_C0   0x69054114
#define ARM_CPUID_PXA270_C5   0x69054117
#define ARM_CPUID_ARM1136     0x4117b363
#define ARM_CPUID_ARM1136_R2  0x4107b362
#define ARM_CPUID_ARM1176     0x410fb767
#define ARM_CPUID_ARM11MPCORE 0x410fb022
#define ARM_CPUID_CORTEXA8    0x410fc080
#define ARM_CPUID_CORTEXA8_R2 0x412fc083
#define ARM_CPUID_CORTEXA9    0x410fc090
#define ARM_CPUID_CORTEXM3    0x410fc231
#define ARM_CPUID_ANY         0xffffffff

#if defined(CONFIG_USER_ONLY)
#define TARGET_PAGE_BITS 12
#else
#define TARGET_PAGE_BITS 10
#endif

#if defined(TARGET_AARCH64)
#  define TARGET_PHYS_ADDR_SPACE_BITS 48
#  define TARGET_VIRT_ADDR_SPACE_BITS 64
#else
#  define TARGET_PHYS_ADDR_SPACE_BITS 40
#  define TARGET_VIRT_ADDR_SPACE_BITS 32
#endif

#define cpu_init cpu_arm_init
#define cpu_exec cpu_arm_exec
#define cpu_gen_code cpu_arm_gen_code
#define cpu_signal_handler cpu_arm_signal_handler
#define cpu_list arm_cpu_list

#define CPU_SAVE_VERSION 4

#define MMU_MODE0_SUFFIX _kernel
#define MMU_MODE1_SUFFIX _user
#define MMU_USER_IDX 1
static inline int cpu_mmu_index (CPUARMState *env)
{
    return (env->uncached_cpsr & CPSR_M) == ARM_CPU_MODE_USR ? 1 : 0;
}

static inline int is_cpu_user (CPUARMState *env)
{
#ifdef CONFIG_USER_ONLY
    return 1;
#else
    return (env->uncached_cpsr & CPSR_M) == ARM_CPU_MODE_USR;
#endif  
}

#if defined(CONFIG_USER_ONLY)
static inline void cpu_clone_regs(CPUARMState *env, target_ulong newsp)
{
    if (newsp)
        env->regs[13] = newsp;
    env->regs[0] = 0;
}
#endif

#include "exec/cpu-all.h"

#define ARM_TBFLAG_AARCH64_STATE_SHIFT 31
#define ARM_TBFLAG_AARCH64_STATE_MASK  (1U << ARM_TBFLAG_AARCH64_STATE_SHIFT)

#define ARM_TBFLAG_THUMB_SHIFT      0
#define ARM_TBFLAG_THUMB_MASK       (1 << ARM_TBFLAG_THUMB_SHIFT)
#define ARM_TBFLAG_VECLEN_SHIFT     1
#define ARM_TBFLAG_VECLEN_MASK      (0x7 << ARM_TBFLAG_VECLEN_SHIFT)
#define ARM_TBFLAG_VECSTRIDE_SHIFT  4
#define ARM_TBFLAG_VECSTRIDE_MASK   (0x3 << ARM_TBFLAG_VECSTRIDE_SHIFT)
#define ARM_TBFLAG_PRIV_SHIFT       6
#define ARM_TBFLAG_PRIV_MASK        (1 << ARM_TBFLAG_PRIV_SHIFT)
#define ARM_TBFLAG_VFPEN_SHIFT      7
#define ARM_TBFLAG_VFPEN_MASK       (1 << ARM_TBFLAG_VFPEN_SHIFT)
#define ARM_TBFLAG_CONDEXEC_SHIFT   8
#define ARM_TBFLAG_CONDEXEC_MASK    (0xff << ARM_TBFLAG_CONDEXEC_SHIFT)
#define ARM_TBFLAG_BSWAP_CODE_SHIFT 16
#define ARM_TBFLAG_BSWAP_CODE_MASK  (1 << ARM_TBFLAG_BSWAP_CODE_SHIFT)


#define ARM_TBFLAG_AARCH64_STATE(F) \
    (((F) & ARM_TBFLAG_AARCH64_STATE_MASK) >> ARM_TBFLAG_AARCH64_STATE_SHIFT)
#define ARM_TBFLAG_THUMB(F) \
    (((F) & ARM_TBFLAG_THUMB_MASK) >> ARM_TBFLAG_THUMB_SHIFT)
#define ARM_TBFLAG_VECLEN(F) \
    (((F) & ARM_TBFLAG_VECLEN_MASK) >> ARM_TBFLAG_VECLEN_SHIFT)
#define ARM_TBFLAG_VECSTRIDE(F) \
    (((F) & ARM_TBFLAG_VECSTRIDE_MASK) >> ARM_TBFLAG_VECSTRIDE_SHIFT)
#define ARM_TBFLAG_PRIV(F) \
    (((F) & ARM_TBFLAG_PRIV_MASK) >> ARM_TBFLAG_PRIV_SHIFT)
#define ARM_TBFLAG_VFPEN(F) \
    (((F) & ARM_TBFLAG_VFPEN_MASK) >> ARM_TBFLAG_VFPEN_SHIFT)
#define ARM_TBFLAG_CONDEXEC(F) \
    (((F) & ARM_TBFLAG_CONDEXEC_MASK) >> ARM_TBFLAG_CONDEXEC_SHIFT)
#define ARM_TBFLAG_BSWAP_CODE(F) \
    (((F) & ARM_TBFLAG_BSWAP_CODE_MASK) >> ARM_TBFLAG_BSWAP_CODE_SHIFT)

static inline void cpu_get_tb_cpu_state(CPUARMState *env, target_ulong *pc,
                                        target_ulong *cs_base, int *flags)
{
    if (is_a64(env)) {
        *pc = env->regs[15];
        *flags = ARM_TBFLAG_AARCH64_STATE_MASK;
    } else {
        int privmode;
        *pc = env->regs[15];
        *flags = (env->thumb << ARM_TBFLAG_THUMB_SHIFT)
            | (env->vfp.vec_len << ARM_TBFLAG_VECLEN_SHIFT)
            | (env->vfp.vec_stride << ARM_TBFLAG_VECSTRIDE_SHIFT)
            | (env->condexec_bits << ARM_TBFLAG_CONDEXEC_SHIFT);
            
        if (arm_feature(env, ARM_FEATURE_M)) {
            privmode = !((env->v7m.exception == 0) && (env->v7m.control & 1));
        } else {
            privmode = (env->uncached_cpsr & CPSR_M) != ARM_CPU_MODE_USR;
        }
        if (privmode) {
            *flags |= ARM_TBFLAG_PRIV_MASK;
        }
        if (env->vfp.xregs[ARM_VFP_FPEXC] & (1 << 30)) {
            *flags |= ARM_TBFLAG_VFPEN_MASK;
        }
    }

    *cs_base = 0;
}

static inline bool cpu_has_work(CPUState *cpu)
{
    return (cpu->interrupt_request &
            (CPU_INTERRUPT_FIQ | CPU_INTERRUPT_HARD | CPU_INTERRUPT_EXITTB));
}

#include "exec/exec-all.h"

static inline void cpu_pc_from_tb(CPUARMState *env, TranslationBlock *tb)
{
    env->regs[15] = tb->pc;
}

#endif

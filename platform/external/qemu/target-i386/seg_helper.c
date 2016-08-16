/*
 *  x86 segmentation related helpers:
 *  TSS, interrupts, system calls, jumps and call/task gates, descriptors
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

#include "cpu.h"
#include "qemu/log.h"
#include "helper.h"

#if !defined(CONFIG_USER_ONLY)
#include "exec/softmmu_exec.h"
#endif 



#ifdef DEBUG_PCALL
#  define LOG_PCALL(...) qemu_log_mask(CPU_LOG_PCALL, ## __VA_ARGS__)
#  define LOG_PCALL_STATE(env) \
          log_cpu_state_mask(CPU_LOG_PCALL, (env), X86_DUMP_CCOP)
#else
#  define LOG_PCALL(...) do { } while (0)
#  define LOG_PCALL_STATE(env) do { } while (0)
#endif

static inline int load_segment(CPUX86State *env,
                               uint32_t *e1_ptr, uint32_t *e2_ptr,
                               int selector)
{
    SegmentCache *dt;
    int index;
    target_ulong ptr;

    if (selector & 0x4)
        dt = &env->ldt;
    else
        dt = &env->gdt;
    index = selector & ~7;
    if ((index + 7) > dt->limit)
        return -1;
    ptr = dt->base + index;
    *e1_ptr = cpu_ldl_kernel(env, ptr);
    *e2_ptr = cpu_ldl_kernel(env, ptr + 4);
    return 0;
}

static inline unsigned int get_seg_limit(uint32_t e1, uint32_t e2)
{
    unsigned int limit;
    limit = (e1 & 0xffff) | (e2 & 0x000f0000);
    if (e2 & DESC_G_MASK)
        limit = (limit << 12) | 0xfff;
    return limit;
}

static inline uint32_t get_seg_base(uint32_t e1, uint32_t e2)
{
    return ((e1 >> 16) | ((e2 & 0xff) << 16) | (e2 & 0xff000000));
}

static inline void load_seg_cache_raw_dt(SegmentCache *sc, uint32_t e1, uint32_t e2)
{
    sc->base = get_seg_base(e1, e2);
    sc->limit = get_seg_limit(e1, e2);
    sc->flags = e2;
}

static inline void load_seg_vm(CPUX86State *env, int seg, int selector)
{
    selector &= 0xffff;
    cpu_x86_load_seg_cache(env, seg, selector,
                           (selector << 4), 0xffff, 0);
}

static inline void get_ss_esp_from_tss(CPUX86State *env,
                                       uint32_t *ss_ptr,
                                       uint32_t *esp_ptr, int dpl)
{
    int type, index, shift;

#if 0
    {
        int i;
        printf("TR: base=%p limit=%x\n", env->tr.base, env->tr.limit);
        for(i=0;i<env->tr.limit;i++) {
            printf("%02x ", env->tr.base[i]);
            if ((i & 7) == 7) printf("\n");
        }
        printf("\n");
    }
#endif

    if (!(env->tr.flags & DESC_P_MASK))
        cpu_abort(env, "invalid tss");
    type = (env->tr.flags >> DESC_TYPE_SHIFT) & 0xf;
    if ((type & 7) != 1)
        cpu_abort(env, "invalid tss type");
    shift = type >> 3;
    index = (dpl * 4 + 2) << shift;
    if (index + (4 << shift) - 1 > env->tr.limit)
        raise_exception_err(env, EXCP0A_TSS, env->tr.selector & 0xfffc);
    if (shift == 0) {
        *esp_ptr = cpu_lduw_kernel(env, env->tr.base + index);
        *ss_ptr = cpu_lduw_kernel(env, env->tr.base + index + 2);
    } else {
        *esp_ptr = cpu_ldl_kernel(env, env->tr.base + index);
        *ss_ptr = cpu_lduw_kernel(env, env->tr.base + index + 4);
    }
}

static void tss_load_seg(CPUX86State *env, int seg_reg, int selector)
{
    uint32_t e1, e2;
    int rpl, dpl, cpl;

    if ((selector & 0xfffc) != 0) {
        if (load_segment(env, &e1, &e2, selector) != 0)
            raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
        if (!(e2 & DESC_S_MASK))
            raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
        rpl = selector & 3;
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        cpl = env->hflags & HF_CPL_MASK;
        if (seg_reg == R_CS) {
            if (!(e2 & DESC_CS_MASK))
                raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
            
            if (dpl != rpl)
                raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
            if ((e2 & DESC_C_MASK) && dpl > rpl)
                raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
        } else if (seg_reg == R_SS) {
            
            if ((e2 & DESC_CS_MASK) || !(e2 & DESC_W_MASK))
                raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
            if (dpl != cpl || dpl != rpl)
                raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
        } else {
            
            if ((e2 & DESC_CS_MASK) && !(e2 & DESC_R_MASK))
                raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
            
            if (((e2 >> DESC_TYPE_SHIFT) & 0xf) < 12) {
                if (dpl < cpl || dpl < rpl)
                    raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
            }
        }
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);
        cpu_x86_load_seg_cache(env, seg_reg, selector,
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
    } else {
        if (seg_reg == R_SS || seg_reg == R_CS)
            raise_exception_err(env, EXCP0A_TSS, selector & 0xfffc);
    }
}

#define SWITCH_TSS_JMP  0
#define SWITCH_TSS_IRET 1
#define SWITCH_TSS_CALL 2

static void switch_tss(CPUX86State *env,
                       int tss_selector,
                       uint32_t e1, uint32_t e2, int source,
                       uint32_t next_eip)
{
    int tss_limit, tss_limit_max, type, old_tss_limit_max, old_type, v1, v2, i;
    target_ulong tss_base;
    uint32_t new_regs[8], new_segs[6];
    uint32_t new_eflags, new_eip, new_cr3, new_ldt;
    uint32_t old_eflags, eflags_mask;
    SegmentCache *dt;
    int index;
    target_ulong ptr;

    type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
    LOG_PCALL("switch_tss: sel=0x%04x type=%d src=%d\n", tss_selector, type, source);

    
    if (type == 5) {
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, tss_selector & 0xfffc);
        tss_selector = e1 >> 16;
        if (tss_selector & 4)
            raise_exception_err(env, EXCP0A_TSS, tss_selector & 0xfffc);
        if (load_segment(env, &e1, &e2, tss_selector) != 0)
            raise_exception_err(env, EXCP0D_GPF, tss_selector & 0xfffc);
        if (e2 & DESC_S_MASK)
            raise_exception_err(env, EXCP0D_GPF, tss_selector & 0xfffc);
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        if ((type & 7) != 1)
            raise_exception_err(env, EXCP0D_GPF, tss_selector & 0xfffc);
    }

    if (!(e2 & DESC_P_MASK))
        raise_exception_err(env, EXCP0B_NOSEG, tss_selector & 0xfffc);

    if (type & 8)
        tss_limit_max = 103;
    else
        tss_limit_max = 43;
    tss_limit = get_seg_limit(e1, e2);
    tss_base = get_seg_base(e1, e2);
    if ((tss_selector & 4) != 0 ||
        tss_limit < tss_limit_max)
        raise_exception_err(env, EXCP0A_TSS, tss_selector & 0xfffc);
    old_type = (env->tr.flags >> DESC_TYPE_SHIFT) & 0xf;
    if (old_type & 8)
        old_tss_limit_max = 103;
    else
        old_tss_limit_max = 43;

    
    if (type & 8) {
        
        new_cr3 = cpu_ldl_kernel(env, tss_base + 0x1c);
        new_eip = cpu_ldl_kernel(env, tss_base + 0x20);
        new_eflags = cpu_ldl_kernel(env, tss_base + 0x24);
        for(i = 0; i < 8; i++)
            new_regs[i] = cpu_ldl_kernel(env, tss_base + (0x28 + i * 4));
        for(i = 0; i < 6; i++)
            new_segs[i] = cpu_lduw_kernel(env, tss_base + (0x48 + i * 4));
        new_ldt = cpu_lduw_kernel(env, tss_base + 0x60);
        cpu_ldl_kernel(env, tss_base + 0x64);
    } else {
        
        new_cr3 = 0;
        new_eip = cpu_lduw_kernel(env, tss_base + 0x0e);
        new_eflags = cpu_lduw_kernel(env, tss_base + 0x10);
        for(i = 0; i < 8; i++)
            new_regs[i] = cpu_lduw_kernel(env, tss_base + (0x12 + i * 2)) | 0xffff0000;
        for(i = 0; i < 4; i++)
            new_segs[i] = cpu_lduw_kernel(env, tss_base + (0x22 + i * 4));
        new_ldt = cpu_lduw_kernel(env, tss_base + 0x2a);
        new_segs[R_FS] = 0;
        new_segs[R_GS] = 0;
    }


    v1 = cpu_ldub_kernel(env, env->tr.base);
    v2 = cpu_ldub_kernel(env, env->tr.base + old_tss_limit_max);
    cpu_stb_kernel(env, env->tr.base, v1);
    cpu_stb_kernel(env, env->tr.base + old_tss_limit_max, v2);

    
    if (source == SWITCH_TSS_JMP || source == SWITCH_TSS_IRET) {
        target_ulong ptr;
        uint32_t e2;
        ptr = env->gdt.base + (env->tr.selector & ~7);
        e2 = cpu_ldl_kernel(env, ptr + 4);
        e2 &= ~DESC_TSS_BUSY_MASK;
        cpu_stl_kernel(env, ptr + 4, e2);
    }
    old_eflags = cpu_compute_eflags(env);
    if (source == SWITCH_TSS_IRET)
        old_eflags &= ~NT_MASK;

    
    if (type & 8) {
        
        cpu_stl_kernel(env, env->tr.base + 0x20, next_eip);
        cpu_stl_kernel(env, env->tr.base + 0x24, old_eflags);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 0 * 4), EAX);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 1 * 4), ECX);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 2 * 4), EDX);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 3 * 4), EBX);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 4 * 4), ESP);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 5 * 4), EBP);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 6 * 4), ESI);
        cpu_stl_kernel(env, env->tr.base + (0x28 + 7 * 4), EDI);
        for(i = 0; i < 6; i++)
            cpu_stw_kernel(env, env->tr.base + (0x48 + i * 4), env->segs[i].selector);
    } else {
        
        cpu_stw_kernel(env, env->tr.base + 0x0e, next_eip);
        cpu_stw_kernel(env, env->tr.base + 0x10, old_eflags);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 0 * 2), EAX);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 1 * 2), ECX);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 2 * 2), EDX);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 3 * 2), EBX);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 4 * 2), ESP);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 5 * 2), EBP);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 6 * 2), ESI);
        cpu_stw_kernel(env, env->tr.base + (0x12 + 7 * 2), EDI);
        for(i = 0; i < 4; i++)
            cpu_stw_kernel(env, env->tr.base + (0x22 + i * 4), env->segs[i].selector);
    }


    if (source == SWITCH_TSS_CALL) {
        cpu_stw_kernel(env, tss_base, env->tr.selector);
        new_eflags |= NT_MASK;
    }

    
    if (source == SWITCH_TSS_JMP || source == SWITCH_TSS_CALL) {
        target_ulong ptr;
        uint32_t e2;
        ptr = env->gdt.base + (tss_selector & ~7);
        e2 = cpu_ldl_kernel(env, ptr + 4);
        e2 |= DESC_TSS_BUSY_MASK;
        cpu_stl_kernel(env, ptr + 4, e2);
    }

    
    
    env->cr[0] |= CR0_TS_MASK;
    env->hflags |= HF_TS_MASK;
    env->tr.selector = tss_selector;
    env->tr.base = tss_base;
    env->tr.limit = tss_limit;
    env->tr.flags = e2 & ~DESC_TSS_BUSY_MASK;

    if ((type & 8) && (env->cr[0] & CR0_PG_MASK)) {
        cpu_x86_update_cr3(env, new_cr3);
    }

    env->eip = new_eip;
    eflags_mask = TF_MASK | AC_MASK | ID_MASK |
        IF_MASK | IOPL_MASK | VM_MASK | RF_MASK | NT_MASK;
    if (!(type & 8))
        eflags_mask &= 0xffff;
    cpu_load_eflags(env, new_eflags, eflags_mask);
    
    EAX = new_regs[0];
    ECX = new_regs[1];
    EDX = new_regs[2];
    EBX = new_regs[3];
    ESP = new_regs[4];
    EBP = new_regs[5];
    ESI = new_regs[6];
    EDI = new_regs[7];
    if (new_eflags & VM_MASK) {
        for(i = 0; i < 6; i++)
            load_seg_vm(env, i, new_segs[i]);
        
        cpu_x86_set_cpl(env, 3);
    } else {
        
        cpu_x86_set_cpl(env, new_segs[R_CS] & 3);
        
        for(i = 0; i < 6; i++)
            cpu_x86_load_seg_cache(env, i, new_segs[i], 0, 0, 0);
    }

    env->ldt.selector = new_ldt & ~4;
    env->ldt.base = 0;
    env->ldt.limit = 0;
    env->ldt.flags = 0;

    
    if (new_ldt & 4)
        raise_exception_err(env, EXCP0A_TSS, new_ldt & 0xfffc);

    if ((new_ldt & 0xfffc) != 0) {
        dt = &env->gdt;
        index = new_ldt & ~7;
        if ((index + 7) > dt->limit)
            raise_exception_err(env, EXCP0A_TSS, new_ldt & 0xfffc);
        ptr = dt->base + index;
        e1 = cpu_ldl_kernel(env, ptr);
        e2 = cpu_ldl_kernel(env, ptr + 4);
        if ((e2 & DESC_S_MASK) || ((e2 >> DESC_TYPE_SHIFT) & 0xf) != 2)
            raise_exception_err(env, EXCP0A_TSS, new_ldt & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0A_TSS, new_ldt & 0xfffc);
        load_seg_cache_raw_dt(&env->ldt, e1, e2);
    }

    
    if (!(new_eflags & VM_MASK)) {
        tss_load_seg(env, R_CS, new_segs[R_CS]);
        tss_load_seg(env, R_SS, new_segs[R_SS]);
        tss_load_seg(env, R_ES, new_segs[R_ES]);
        tss_load_seg(env, R_DS, new_segs[R_DS]);
        tss_load_seg(env, R_FS, new_segs[R_FS]);
        tss_load_seg(env, R_GS, new_segs[R_GS]);
    }

    
    if (new_eip > env->segs[R_CS].limit) {
        
        raise_exception_err(env, EXCP0D_GPF, 0);
    }

#ifndef CONFIG_USER_ONLY
    
    if (env->dr[7] & 0x55) {
        for (i = 0; i < 4; i++) {
            if (hw_breakpoint_enabled(env->dr[7], i) == 0x1)
                hw_breakpoint_remove(env, i);
        }
        env->dr[7] &= ~0x55;
    }
#endif
}

static inline unsigned int get_sp_mask(unsigned int e2)
{
    if (e2 & DESC_B_MASK)
        return 0xffffffff;
    else
        return 0xffff;
}

static int exeption_has_error_code(int intno)
{
        switch(intno) {
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 17:
            return 1;
        }
        return 0;
}

#ifdef TARGET_X86_64
#define SET_ESP(val, sp_mask)\
do {\
    if ((sp_mask) == 0xffff)\
        ESP = (ESP & ~0xffff) | ((val) & 0xffff);\
    else if ((sp_mask) == 0xffffffffLL)\
        ESP = (uint32_t)(val);\
    else\
        ESP = (val);\
} while (0)
#else
#define SET_ESP(val, sp_mask) ESP = (ESP & ~(sp_mask)) | ((val) & (sp_mask))
#endif

#define SEG_ADDL(ssp, sp, sp_mask) ((uint32_t)((ssp) + (sp & (sp_mask))))

#define PUSHW(ssp, sp, sp_mask, val)\
{\
    sp -= 2;\
    cpu_stw_kernel(env, (ssp) + (sp & (sp_mask)), (val));\
}

#define PUSHL(ssp, sp, sp_mask, val)\
{\
    sp -= 4;\
    cpu_stl_kernel(env, SEG_ADDL(ssp, sp, sp_mask), (uint32_t)(val));\
}

#define POPW(ssp, sp, sp_mask, val)\
{\
    val = cpu_lduw_kernel(env, (ssp) + (sp & (sp_mask)));\
    sp += 2;\
}

#define POPL(ssp, sp, sp_mask, val)\
{\
    val = (uint32_t)cpu_ldl_kernel(env, SEG_ADDL(ssp, sp, sp_mask));\
    sp += 4;\
}

static void do_interrupt_protected(CPUX86State *env,
                                   int intno, int is_int, int error_code,
                                   unsigned int next_eip, int is_hw)
{
    SegmentCache *dt;
    target_ulong ptr, ssp;
    int type, dpl, selector, ss_dpl, cpl;
    int has_error_code, new_stack, shift;
    uint32_t e1, e2, offset, ss = 0, esp, ss_e1 = 0, ss_e2 = 0;
    uint32_t old_eip, sp_mask;

    has_error_code = 0;
    if (!is_int && !is_hw)
        has_error_code = exeption_has_error_code(intno);
    if (is_int)
        old_eip = next_eip;
    else
        old_eip = env->eip;

    dt = &env->idt;
    if (intno * 8 + 7 > dt->limit)
        raise_exception_err(env, EXCP0D_GPF, intno * 8 + 2);
    ptr = dt->base + intno * 8;
    e1 = cpu_ldl_kernel(env, ptr);
    e2 = cpu_ldl_kernel(env, ptr + 4);
    
    type = (e2 >> DESC_TYPE_SHIFT) & 0x1f;
    switch(type) {
    case 5: 
        
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, intno * 8 + 2);
        switch_tss(env, intno * 8, e1, e2, SWITCH_TSS_CALL, old_eip);
        if (has_error_code) {
            int type;
            uint32_t mask;
            
            type = (env->tr.flags >> DESC_TYPE_SHIFT) & 0xf;
            shift = type >> 3;
            if (env->segs[R_SS].flags & DESC_B_MASK)
                mask = 0xffffffff;
            else
                mask = 0xffff;
            esp = (ESP - (2 << shift)) & mask;
            ssp = env->segs[R_SS].base + esp;
            if (shift)
                cpu_stl_kernel(env, ssp, error_code);
            else
                cpu_stw_kernel(env, ssp, error_code);
            SET_ESP(esp, mask);
        }
        return;
    case 6: 
    case 7: 
    case 14: 
    case 15: 
        break;
    default:
        raise_exception_err(env, EXCP0D_GPF, intno * 8 + 2);
        break;
    }
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    
    if (is_int && dpl < cpl)
        raise_exception_err(env, EXCP0D_GPF, intno * 8 + 2);
    
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(env, EXCP0B_NOSEG, intno * 8 + 2);
    selector = e1 >> 16;
    offset = (e2 & 0xffff0000) | (e1 & 0x0000ffff);
    if ((selector & 0xfffc) == 0)
        raise_exception_err(env, EXCP0D_GPF, 0);

    if (load_segment(env, &e1, &e2, selector) != 0)
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
    if (!(e2 & DESC_S_MASK) || !(e2 & (DESC_CS_MASK)))
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    if (dpl > cpl)
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);
    if (!(e2 & DESC_C_MASK) && dpl < cpl) {
        
        get_ss_esp_from_tss(env, &ss, &esp, dpl);
        if ((ss & 0xfffc) == 0)
            raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
        if ((ss & 3) != dpl)
            raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
        if (load_segment(env, &ss_e1, &ss_e2, ss) != 0)
            raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
        ss_dpl = (ss_e2 >> DESC_DPL_SHIFT) & 3;
        if (ss_dpl != dpl)
            raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
        if (!(ss_e2 & DESC_S_MASK) ||
            (ss_e2 & DESC_CS_MASK) ||
            !(ss_e2 & DESC_W_MASK))
            raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
        if (!(ss_e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
        new_stack = 1;
        sp_mask = get_sp_mask(ss_e2);
        ssp = get_seg_base(ss_e1, ss_e2);
    } else if ((e2 & DESC_C_MASK) || dpl == cpl) {
        
        if (env->eflags & VM_MASK)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        new_stack = 0;
        sp_mask = get_sp_mask(env->segs[R_SS].flags);
        ssp = env->segs[R_SS].base;
        esp = ESP;
        dpl = cpl;
    } else {
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        new_stack = 0; 
        sp_mask = 0; 
        ssp = 0; 
        esp = 0; 
    }

    shift = type >> 3;

#if 0
    
    push_size = 6 + (new_stack << 2) + (has_error_code << 1);
    if (env->eflags & VM_MASK)
        push_size += 8;
    push_size <<= shift;
#endif
    if (shift == 1) {
        if (new_stack) {
            if (env->eflags & VM_MASK) {
                PUSHL(ssp, esp, sp_mask, env->segs[R_GS].selector);
                PUSHL(ssp, esp, sp_mask, env->segs[R_FS].selector);
                PUSHL(ssp, esp, sp_mask, env->segs[R_DS].selector);
                PUSHL(ssp, esp, sp_mask, env->segs[R_ES].selector);
            }
            PUSHL(ssp, esp, sp_mask, env->segs[R_SS].selector);
            PUSHL(ssp, esp, sp_mask, ESP);
        }
        PUSHL(ssp, esp, sp_mask, cpu_compute_eflags(env));
        PUSHL(ssp, esp, sp_mask, env->segs[R_CS].selector);
        PUSHL(ssp, esp, sp_mask, old_eip);
        if (has_error_code) {
            PUSHL(ssp, esp, sp_mask, error_code);
        }
    } else {
        if (new_stack) {
            if (env->eflags & VM_MASK) {
                PUSHW(ssp, esp, sp_mask, env->segs[R_GS].selector);
                PUSHW(ssp, esp, sp_mask, env->segs[R_FS].selector);
                PUSHW(ssp, esp, sp_mask, env->segs[R_DS].selector);
                PUSHW(ssp, esp, sp_mask, env->segs[R_ES].selector);
            }
            PUSHW(ssp, esp, sp_mask, env->segs[R_SS].selector);
            PUSHW(ssp, esp, sp_mask, ESP);
        }
        PUSHW(ssp, esp, sp_mask, cpu_compute_eflags(env));
        PUSHW(ssp, esp, sp_mask, env->segs[R_CS].selector);
        PUSHW(ssp, esp, sp_mask, old_eip);
        if (has_error_code) {
            PUSHW(ssp, esp, sp_mask, error_code);
        }
    }

    if (new_stack) {
        if (env->eflags & VM_MASK) {
            cpu_x86_load_seg_cache(env, R_ES, 0, 0, 0, 0);
            cpu_x86_load_seg_cache(env, R_DS, 0, 0, 0, 0);
            cpu_x86_load_seg_cache(env, R_FS, 0, 0, 0, 0);
            cpu_x86_load_seg_cache(env, R_GS, 0, 0, 0, 0);
        }
        ss = (ss & ~3) | dpl;
        cpu_x86_load_seg_cache(env, R_SS, ss,
                               ssp, get_seg_limit(ss_e1, ss_e2), ss_e2);
    }
    SET_ESP(esp, sp_mask);

    selector = (selector & ~3) | dpl;
    cpu_x86_load_seg_cache(env, R_CS, selector,
                   get_seg_base(e1, e2),
                   get_seg_limit(e1, e2),
                   e2);
    cpu_x86_set_cpl(env, dpl);
    env->eip = offset;

    
    if ((type & 1) == 0) {
        env->eflags &= ~IF_MASK;
    }
    env->eflags &= ~(TF_MASK | VM_MASK | RF_MASK | NT_MASK);
}

#ifdef TARGET_X86_64

#define PUSHQ(sp, val)\
{\
    sp -= 8;\
    cpu_stq_kernel(env, sp, (val));\
}

#define POPQ(sp, val)\
{\
    val = cpu_ldq_kernel(env, sp);\
    sp += 8;\
}

static inline target_ulong get_rsp_from_tss(CPUX86State *env, int level)
{
    int index;

#if 0
    printf("TR: base=" TARGET_FMT_lx " limit=%x\n",
           env->tr.base, env->tr.limit);
#endif

    if (!(env->tr.flags & DESC_P_MASK))
        cpu_abort(env, "invalid tss");
    index = 8 * level + 4;
    if ((index + 7) > env->tr.limit)
        raise_exception_err(env, EXCP0A_TSS, env->tr.selector & 0xfffc);
    return cpu_ldq_kernel(env, env->tr.base + index);
}

static void do_interrupt64(CPUX86State *env,
                           int intno, int is_int, int error_code,
                           target_ulong next_eip, int is_hw)
{
    SegmentCache *dt;
    target_ulong ptr;
    int type, dpl, selector, cpl, ist;
    int has_error_code, new_stack;
    uint32_t e1, e2, e3, ss;
    target_ulong old_eip, esp, offset;

    has_error_code = 0;
    if (!is_int && !is_hw)
        has_error_code = exeption_has_error_code(intno);
    if (is_int)
        old_eip = next_eip;
    else
        old_eip = env->eip;

    dt = &env->idt;
    if (intno * 16 + 15 > dt->limit)
        raise_exception_err(env, EXCP0D_GPF, intno * 16 + 2);
    ptr = dt->base + intno * 16;
    e1 = cpu_ldl_kernel(env, ptr);
    e2 = cpu_ldl_kernel(env, ptr + 4);
    e3 = cpu_ldl_kernel(env, ptr + 8);
    
    type = (e2 >> DESC_TYPE_SHIFT) & 0x1f;
    switch(type) {
    case 14: 
    case 15: 
        break;
    default:
        raise_exception_err(env, EXCP0D_GPF, intno * 16 + 2);
        break;
    }
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    
    if (is_int && dpl < cpl)
        raise_exception_err(env, EXCP0D_GPF, intno * 16 + 2);
    
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(env, EXCP0B_NOSEG, intno * 16 + 2);
    selector = e1 >> 16;
    offset = ((target_ulong)e3 << 32) | (e2 & 0xffff0000) | (e1 & 0x0000ffff);
    ist = e2 & 7;
    if ((selector & 0xfffc) == 0)
        raise_exception_err(env, EXCP0D_GPF, 0);

    if (load_segment(env, &e1, &e2, selector) != 0)
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
    if (!(e2 & DESC_S_MASK) || !(e2 & (DESC_CS_MASK)))
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    if (dpl > cpl)
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);
    if (!(e2 & DESC_L_MASK) || (e2 & DESC_B_MASK))
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
    if ((!(e2 & DESC_C_MASK) && dpl < cpl) || ist != 0) {
        
        if (ist != 0)
            esp = get_rsp_from_tss(env, ist + 3);
        else
            esp = get_rsp_from_tss(env, dpl);
        esp &= ~0xfLL; 
        ss = 0;
        new_stack = 1;
    } else if ((e2 & DESC_C_MASK) || dpl == cpl) {
        
        if (env->eflags & VM_MASK)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        new_stack = 0;
        if (ist != 0)
            esp = get_rsp_from_tss(env, ist + 3);
        else
            esp = ESP;
        esp &= ~0xfLL; 
        dpl = cpl;
    } else {
        raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        new_stack = 0; 
        esp = 0; 
    }

    PUSHQ(esp, env->segs[R_SS].selector);
    PUSHQ(esp, ESP);
    PUSHQ(esp, cpu_compute_eflags(env));
    PUSHQ(esp, env->segs[R_CS].selector);
    PUSHQ(esp, old_eip);
    if (has_error_code) {
        PUSHQ(esp, error_code);
    }

    if (new_stack) {
        ss = 0 | dpl;
        cpu_x86_load_seg_cache(env, R_SS, ss, 0, 0, 0);
    }
    ESP = esp;

    selector = (selector & ~3) | dpl;
    cpu_x86_load_seg_cache(env, R_CS, selector,
                   get_seg_base(e1, e2),
                   get_seg_limit(e1, e2),
                   e2);
    cpu_x86_set_cpl(env, dpl);
    env->eip = offset;

    
    if ((type & 1) == 0) {
        env->eflags &= ~IF_MASK;
    }
    env->eflags &= ~(TF_MASK | VM_MASK | RF_MASK | NT_MASK);
}
#endif

#ifdef TARGET_X86_64
#if defined(CONFIG_USER_ONLY)
void helper_syscall(CPUX86State *env, int next_eip_addend)
{
    env->exception_index = EXCP_SYSCALL;
    env->exception_next_eip = env->eip + next_eip_addend;
    cpu_loop_exit(env);
}
#else
void helper_syscall(CPUX86State *env, int next_eip_addend)
{
    int selector;

    if (!(env->efer & MSR_EFER_SCE)) {
        raise_exception_err(env, EXCP06_ILLOP, 0);
    }
    selector = (env->star >> 32) & 0xffff;
    if (env->hflags & HF_LMA_MASK) {
        int code64;

        ECX = env->eip + next_eip_addend;
        env->regs[11] = cpu_compute_eflags(env);

        code64 = env->hflags & HF_CS64_MASK;

        cpu_x86_set_cpl(env, 0);
        cpu_x86_load_seg_cache(env, R_CS, selector & 0xfffc,
                           0, 0xffffffff,
                               DESC_G_MASK | DESC_P_MASK |
                               DESC_S_MASK |
                               DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK | DESC_L_MASK);
        cpu_x86_load_seg_cache(env, R_SS, (selector + 8) & 0xfffc,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK |
                               DESC_W_MASK | DESC_A_MASK);
        env->eflags &= ~env->fmask;
        cpu_load_eflags(env, env->eflags, 0);
        if (code64)
            env->eip = env->lstar;
        else
            env->eip = env->cstar;
    } else {
        ECX = (uint32_t)(env->eip + next_eip_addend);

        cpu_x86_set_cpl(env, 0);
        cpu_x86_load_seg_cache(env, R_CS, selector & 0xfffc,
                           0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK |
                               DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK);
        cpu_x86_load_seg_cache(env, R_SS, (selector + 8) & 0xfffc,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK |
                               DESC_W_MASK | DESC_A_MASK);
        env->eflags &= ~(IF_MASK | RF_MASK | VM_MASK);
        env->eip = (uint32_t)env->star;
    }
}
#endif
#endif

#ifdef TARGET_X86_64
void helper_sysret(CPUX86State *env, int dflag)
{
    int cpl, selector;

    if (!(env->efer & MSR_EFER_SCE)) {
        raise_exception_err(env, EXCP06_ILLOP, 0);
    }
    cpl = env->hflags & HF_CPL_MASK;
    if (!(env->cr[0] & CR0_PE_MASK) || cpl != 0) {
        raise_exception_err(env, EXCP0D_GPF, 0);
    }
    selector = (env->star >> 48) & 0xffff;
    if (env->hflags & HF_LMA_MASK) {
        if (dflag == 2) {
            cpu_x86_load_seg_cache(env, R_CS, (selector + 16) | 3,
                                   0, 0xffffffff,
                                   DESC_G_MASK | DESC_P_MASK |
                                   DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                                   DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK |
                                   DESC_L_MASK);
            env->eip = ECX;
        } else {
            cpu_x86_load_seg_cache(env, R_CS, selector | 3,
                                   0, 0xffffffff,
                                   DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                                   DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                                   DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK);
            env->eip = (uint32_t)ECX;
        }
        cpu_x86_load_seg_cache(env, R_SS, selector + 8,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                               DESC_W_MASK | DESC_A_MASK);
        cpu_load_eflags(env, (uint32_t)(env->regs[11]), TF_MASK | AC_MASK | ID_MASK |
                    IF_MASK | IOPL_MASK | VM_MASK | RF_MASK | NT_MASK);
        cpu_x86_set_cpl(env, 3);
    } else {
        cpu_x86_load_seg_cache(env, R_CS, selector | 3,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                               DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK);
        env->eip = (uint32_t)ECX;
        cpu_x86_load_seg_cache(env, R_SS, selector + 8,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                               DESC_W_MASK | DESC_A_MASK);
        env->eflags |= IF_MASK;
        cpu_x86_set_cpl(env, 3);
    }
}
#endif

static void do_interrupt_real(CPUX86State *env,
                              int intno, int is_int, int error_code,
                              unsigned int next_eip)
{
    SegmentCache *dt;
    target_ulong ptr, ssp;
    int selector;
    uint32_t offset, esp;
    uint32_t old_cs, old_eip;

    
    dt = &env->idt;
    if (intno * 4 + 3 > dt->limit)
        raise_exception_err(env, EXCP0D_GPF, intno * 8 + 2);
    ptr = dt->base + intno * 4;
    offset = cpu_lduw_kernel(env, ptr);
    selector = cpu_lduw_kernel(env, ptr + 2);
    esp = ESP;
    ssp = env->segs[R_SS].base;
    if (is_int)
        old_eip = next_eip;
    else
        old_eip = env->eip;
    old_cs = env->segs[R_CS].selector;
    
    PUSHW(ssp, esp, 0xffff, cpu_compute_eflags(env));
    PUSHW(ssp, esp, 0xffff, old_cs);
    PUSHW(ssp, esp, 0xffff, old_eip);

    
    ESP = (ESP & ~0xffff) | (esp & 0xffff);
    env->eip = offset;
    env->segs[R_CS].selector = selector;
    env->segs[R_CS].base = (selector << 4);
    env->eflags &= ~(IF_MASK | TF_MASK | AC_MASK | RF_MASK);
}

#if defined(CONFIG_USER_ONLY)
static void do_interrupt_user(CPUX86State *env,
                              int intno, int is_int, int error_code,
                              target_ulong next_eip)
{
    SegmentCache *dt;
    target_ulong ptr;
    int dpl, cpl, shift;
    uint32_t e2;

    dt = &env->idt;
    if (env->hflags & HF_LMA_MASK) {
        shift = 4;
    } else {
        shift = 3;
    }
    ptr = dt->base + (intno << shift);
    e2 = cpu_ldl_kernel(env, ptr + 4);

    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    
    if (is_int && dpl < cpl)
        raise_exception_err(env, EXCP0D_GPF, (intno << shift) + 2);

    if (is_int)
        EIP = next_eip;
}

#else

static void handle_even_inj(CPUX86State *env,
                            int intno, int is_int, int error_code,
                            int is_hw, int rm)
{
    uint32_t event_inj = ldl_phys(env->vm_vmcb + offsetof(struct vmcb, control.event_inj));
    if (!(event_inj & SVM_EVTINJ_VALID)) {
            int type;
            if (is_int)
                    type = SVM_EVTINJ_TYPE_SOFT;
            else
                    type = SVM_EVTINJ_TYPE_EXEPT;
            event_inj = intno | type | SVM_EVTINJ_VALID;
            if (!rm && exeption_has_error_code(intno)) {
                    event_inj |= SVM_EVTINJ_VALID_ERR;
                    stl_phys(env->vm_vmcb + offsetof(struct vmcb, control.event_inj_err), error_code);
            }
            stl_phys(env->vm_vmcb + offsetof(struct vmcb, control.event_inj), event_inj);
    }
}
#endif

static void do_interrupt_all(CPUX86State *env,
                             int intno, int is_int, int error_code,
                             target_ulong next_eip, int is_hw)
{
    if (qemu_loglevel_mask(CPU_LOG_INT)) {
        if ((env->cr[0] & CR0_PE_MASK)) {
            static int count;
            qemu_log("%6d: v=%02x e=%04x i=%d cpl=%d IP=%04x:" TARGET_FMT_lx " pc=" TARGET_FMT_lx " SP=%04x:" TARGET_FMT_lx,
                    count, intno, error_code, is_int,
                    env->hflags & HF_CPL_MASK,
                    env->segs[R_CS].selector, EIP,
                    (int)env->segs[R_CS].base + EIP,
                    env->segs[R_SS].selector, ESP);
            if (intno == 0x0e) {
                qemu_log(" CR2=" TARGET_FMT_lx, env->cr[2]);
            } else {
                qemu_log(" EAX=" TARGET_FMT_lx, EAX);
            }
            qemu_log("\n");
            log_cpu_state(ENV_GET_CPU(env), X86_DUMP_CCOP);
#if 0
            {
                int i;
                uint8_t *ptr;
                qemu_log("       code=");
                ptr = env->segs[R_CS].base + env->eip;
                for(i = 0; i < 16; i++) {
                    qemu_log(" %02x", ldub(ptr + i));
                }
                qemu_log("\n");
            }
#endif
            count++;
        }
    }
    if (env->cr[0] & CR0_PE_MASK) {
#if !defined(CONFIG_USER_ONLY)
        if (env->hflags & HF_SVMI_MASK)
            handle_even_inj(env, intno, is_int, error_code, is_hw, 0);
#endif
#ifdef TARGET_X86_64
        if (env->hflags & HF_LMA_MASK) {
            do_interrupt64(env, intno, is_int, error_code, next_eip, is_hw);
        } else
#endif
        {
            do_interrupt_protected(env, intno, is_int, error_code, next_eip, is_hw);
        }
    } else {
#if !defined(CONFIG_USER_ONLY)
        if (env->hflags & HF_SVMI_MASK)
            handle_even_inj(env, intno, is_int, error_code, is_hw, 1);
#endif
        do_interrupt_real(env, intno, is_int, error_code, next_eip);
    }

#if !defined(CONFIG_USER_ONLY)
    if (env->hflags & HF_SVMI_MASK) {
        uint32_t event_inj = ldl_phys(env->vm_vmcb + offsetof(struct vmcb, control.event_inj));
        stl_phys(env->vm_vmcb + offsetof(struct vmcb, control.event_inj), event_inj & ~SVM_EVTINJ_VALID);
    }
#endif
}

void do_interrupt(CPUX86State *env)
{
#if defined(CONFIG_USER_ONLY)
    do_interrupt_user(env,
                      env->exception_index,
                      env->exception_is_int,
                      env->error_code,
                      env->exception_next_eip);
    
    env->old_exception = -1;
#else
    do_interrupt_all(env,
                     env->exception_index,
                     env->exception_is_int,
                     env->error_code,
                     env->exception_next_eip, 0);
    
    env->old_exception = -1;
#endif
}

void do_interrupt_x86_hardirq(CPUX86State *env, int intno, int is_hw)
{
    do_interrupt_all(env, intno, 0, 0, 0, is_hw);
}

void qemu_system_reset_request(void);

void helper_enter_level(CPUX86State *env,
                        int level, int data32, target_ulong t1)
{
    target_ulong ssp;
    uint32_t esp_mask, esp, ebp;

    esp_mask = get_sp_mask(env->segs[R_SS].flags);
    ssp = env->segs[R_SS].base;
    ebp = EBP;
    esp = ESP;
    if (data32) {
        
        esp -= 4;
        while (--level) {
            esp -= 4;
            ebp -= 4;
            cpu_stl_data(env, ssp + (esp & esp_mask),
                         cpu_ldl_data(env, ssp + (ebp & esp_mask)));
        }
        esp -= 4;
        cpu_stl_data(env, ssp + (esp & esp_mask), t1);
    } else {
        
        esp -= 2;
        while (--level) {
            esp -= 2;
            ebp -= 2;
            cpu_stw_data(env, ssp + (esp & esp_mask),
                         cpu_lduw_data(env, ssp + (ebp & esp_mask)));
        }
        esp -= 2;
        cpu_stw_data(env, ssp + (esp & esp_mask), t1);
    }
}

#ifdef TARGET_X86_64
void helper_enter64_level(CPUX86State *env,
                          int level, int data64, target_ulong t1)
{
    target_ulong esp, ebp;
    ebp = EBP;
    esp = ESP;

    if (data64) {
        
        esp -= 8;
        while (--level) {
            esp -= 8;
            ebp -= 8;
            cpu_stq_data(env, esp, cpu_ldq_data(env, ebp));
        }
        esp -= 8;
        cpu_stq_data(env, esp, t1);
    } else {
        
        esp -= 2;
        while (--level) {
            esp -= 2;
            ebp -= 2;
            cpu_stw_data(env, esp, cpu_lduw_data(env, ebp));
        }
        esp -= 2;
        cpu_stw_data(env, esp, t1);
    }
}
#endif

void helper_lldt(CPUX86State *env, int selector)
{
    SegmentCache *dt;
    uint32_t e1, e2;
    int index, entry_limit;
    target_ulong ptr;

    selector &= 0xffff;
    if ((selector & 0xfffc) == 0) {
        
        env->ldt.base = 0;
        env->ldt.limit = 0;
    } else {
        if (selector & 0x4)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        dt = &env->gdt;
        index = selector & ~7;
#ifdef TARGET_X86_64
        if (env->hflags & HF_LMA_MASK)
            entry_limit = 15;
        else
#endif
            entry_limit = 7;
        if ((index + entry_limit) > dt->limit)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        ptr = dt->base + index;
        e1 = cpu_ldl_kernel(env, ptr);
        e2 = cpu_ldl_kernel(env, ptr + 4);
        if ((e2 & DESC_S_MASK) || ((e2 >> DESC_TYPE_SHIFT) & 0xf) != 2)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);
#ifdef TARGET_X86_64
        if (env->hflags & HF_LMA_MASK) {
            uint32_t e3;
            e3 = cpu_ldl_kernel(env, ptr + 8);
            load_seg_cache_raw_dt(&env->ldt, e1, e2);
            env->ldt.base |= (target_ulong)e3 << 32;
        } else
#endif
        {
            load_seg_cache_raw_dt(&env->ldt, e1, e2);
        }
    }
    env->ldt.selector = selector;
}

void helper_ltr(CPUX86State *env, int selector)
{
    SegmentCache *dt;
    uint32_t e1, e2;
    int index, type, entry_limit;
    target_ulong ptr;

    selector &= 0xffff;
    if ((selector & 0xfffc) == 0) {
        
        env->tr.base = 0;
        env->tr.limit = 0;
        env->tr.flags = 0;
    } else {
        if (selector & 0x4)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        dt = &env->gdt;
        index = selector & ~7;
#ifdef TARGET_X86_64
        if (env->hflags & HF_LMA_MASK)
            entry_limit = 15;
        else
#endif
            entry_limit = 7;
        if ((index + entry_limit) > dt->limit)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        ptr = dt->base + index;
        e1 = cpu_ldl_kernel(env, ptr);
        e2 = cpu_ldl_kernel(env, ptr + 4);
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        if ((e2 & DESC_S_MASK) ||
            (type != 1 && type != 9))
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);
#ifdef TARGET_X86_64
        if (env->hflags & HF_LMA_MASK) {
            uint32_t e3, e4;
            e3 = cpu_ldl_kernel(env, ptr + 8);
            e4 = cpu_ldl_kernel(env, ptr + 12);
            if ((e4 >> DESC_TYPE_SHIFT) & 0xf)
                raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
            load_seg_cache_raw_dt(&env->tr, e1, e2);
            env->tr.base |= (target_ulong)e3 << 32;
        } else
#endif
        {
            load_seg_cache_raw_dt(&env->tr, e1, e2);
        }
        e2 |= DESC_TSS_BUSY_MASK;
        cpu_stl_kernel(env, ptr + 4, e2);
    }
    env->tr.selector = selector;
}

void helper_load_seg(CPUX86State *env, int seg_reg, int selector)
{
    uint32_t e1, e2;
    int cpl, dpl, rpl;
    SegmentCache *dt;
    int index;
    target_ulong ptr;

    selector &= 0xffff;
    cpl = env->hflags & HF_CPL_MASK;
    if ((selector & 0xfffc) == 0) {
        
        if (seg_reg == R_SS
#ifdef TARGET_X86_64
            && (!(env->hflags & HF_CS64_MASK) || cpl == 3)
#endif
            )
            raise_exception_err(env, EXCP0D_GPF, 0);
        cpu_x86_load_seg_cache(env, seg_reg, selector, 0, 0, 0);
    } else {

        if (selector & 0x4)
            dt = &env->ldt;
        else
            dt = &env->gdt;
        index = selector & ~7;
        if ((index + 7) > dt->limit)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        ptr = dt->base + index;
        e1 = cpu_ldl_kernel(env, ptr);
        e2 = cpu_ldl_kernel(env, ptr + 4);

        if (!(e2 & DESC_S_MASK))
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        rpl = selector & 3;
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        if (seg_reg == R_SS) {
            
            if ((e2 & DESC_CS_MASK) || !(e2 & DESC_W_MASK))
                raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
            if (rpl != cpl || dpl != cpl)
                raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        } else {
            
            if ((e2 & (DESC_CS_MASK | DESC_R_MASK)) == DESC_CS_MASK)
                raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);

            if (!(e2 & DESC_CS_MASK) || !(e2 & DESC_C_MASK)) {
                
                if (dpl < cpl || dpl < rpl)
                    raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
            }
        }

        if (!(e2 & DESC_P_MASK)) {
            if (seg_reg == R_SS)
                raise_exception_err(env, EXCP0C_STACK, selector & 0xfffc);
            else
                raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);
        }

        
        if (!(e2 & DESC_A_MASK)) {
            e2 |= DESC_A_MASK;
            cpu_stl_kernel(env, ptr + 4, e2);
        }

        cpu_x86_load_seg_cache(env, seg_reg, selector,
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
#if 0
        qemu_log("load_seg: sel=0x%04x base=0x%08lx limit=0x%08lx flags=%08x\n",
                selector, (unsigned long)sc->base, sc->limit, sc->flags);
#endif
    }
}

void helper_ljmp_protected(CPUX86State *env,
                           int new_cs, target_ulong new_eip,
                           int next_eip_addend)
{
    int gate_cs, type;
    uint32_t e1, e2, cpl, dpl, rpl, limit;
    target_ulong next_eip;

    if ((new_cs & 0xfffc) == 0)
        raise_exception_err(env, EXCP0D_GPF, 0);
    if (load_segment(env, &e1, &e2, new_cs) != 0)
        raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_S_MASK) {
        if (!(e2 & DESC_CS_MASK))
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        if (e2 & DESC_C_MASK) {
            
            if (dpl > cpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        } else {
            
            rpl = new_cs & 3;
            if (rpl > cpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            if (dpl != cpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        }
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, new_cs & 0xfffc);
        limit = get_seg_limit(e1, e2);
        if (new_eip > limit &&
            !(env->hflags & HF_LMA_MASK) && !(e2 & DESC_L_MASK))
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        cpu_x86_load_seg_cache(env, R_CS, (new_cs & 0xfffc) | cpl,
                       get_seg_base(e1, e2), limit, e2);
        EIP = new_eip;
    } else {
        
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        rpl = new_cs & 3;
        cpl = env->hflags & HF_CPL_MASK;
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        switch(type) {
        case 1: 
        case 9: 
        case 5: 
            if (dpl < cpl || dpl < rpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            next_eip = env->eip + next_eip_addend;
            switch_tss(env, new_cs, e1, e2, SWITCH_TSS_JMP, next_eip);
            CC_OP = CC_OP_EFLAGS;
            break;
        case 4: 
        case 12: 
            if ((dpl < cpl) || (dpl < rpl))
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            if (!(e2 & DESC_P_MASK))
                raise_exception_err(env, EXCP0B_NOSEG, new_cs & 0xfffc);
            gate_cs = e1 >> 16;
            new_eip = (e1 & 0xffff);
            if (type == 12)
                new_eip |= (e2 & 0xffff0000);
            if (load_segment(env, &e1, &e2, gate_cs) != 0)
                raise_exception_err(env, EXCP0D_GPF, gate_cs & 0xfffc);
            dpl = (e2 >> DESC_DPL_SHIFT) & 3;
            
            if (((e2 & (DESC_S_MASK | DESC_CS_MASK)) !=
                 (DESC_S_MASK | DESC_CS_MASK)))
                raise_exception_err(env, EXCP0D_GPF, gate_cs & 0xfffc);
            if (((e2 & DESC_C_MASK) && (dpl > cpl)) ||
                (!(e2 & DESC_C_MASK) && (dpl != cpl)))
                raise_exception_err(env, EXCP0D_GPF, gate_cs & 0xfffc);
            if (!(e2 & DESC_P_MASK))
                raise_exception_err(env, EXCP0D_GPF, gate_cs & 0xfffc);
            limit = get_seg_limit(e1, e2);
            if (new_eip > limit)
                raise_exception_err(env, EXCP0D_GPF, 0);
            cpu_x86_load_seg_cache(env, R_CS, (gate_cs & 0xfffc) | cpl,
                                   get_seg_base(e1, e2), limit, e2);
            EIP = new_eip;
            break;
        default:
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            break;
        }
    }
}

void helper_lcall_real(CPUX86State *env,
                       int new_cs, target_ulong new_eip1,
                       int shift, int next_eip)
{
    int new_eip;
    uint32_t esp, esp_mask;
    target_ulong ssp;

    new_eip = new_eip1;
    esp = ESP;
    esp_mask = get_sp_mask(env->segs[R_SS].flags);
    ssp = env->segs[R_SS].base;
    if (shift) {
        PUSHL(ssp, esp, esp_mask, env->segs[R_CS].selector);
        PUSHL(ssp, esp, esp_mask, next_eip);
    } else {
        PUSHW(ssp, esp, esp_mask, env->segs[R_CS].selector);
        PUSHW(ssp, esp, esp_mask, next_eip);
    }

    SET_ESP(esp, esp_mask);
    env->eip = new_eip;
    env->segs[R_CS].selector = new_cs;
    env->segs[R_CS].base = (new_cs << 4);
}

void helper_lcall_protected(CPUX86State *env,
                            int new_cs, target_ulong new_eip,
                            int shift, int next_eip_addend)
{
    int new_stack, i;
    uint32_t e1, e2, cpl, dpl, rpl, selector, offset, param_count;
    uint32_t ss = 0, ss_e1 = 0, ss_e2 = 0, sp, type, ss_dpl, sp_mask;
    uint32_t val, limit, old_sp_mask;
    target_ulong ssp, old_ssp, next_eip;

    next_eip = env->eip + next_eip_addend;
    LOG_PCALL("lcall %04x:%08x s=%d\n", new_cs, (uint32_t)new_eip, shift);
    LOG_PCALL_STATE(env);
    if ((new_cs & 0xfffc) == 0)
        raise_exception_err(env, EXCP0D_GPF, 0);
    if (load_segment(env, &e1, &e2, new_cs) != 0)
        raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    cpl = env->hflags & HF_CPL_MASK;
    LOG_PCALL("desc=%08x:%08x\n", e1, e2);
    if (e2 & DESC_S_MASK) {
        if (!(e2 & DESC_CS_MASK))
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        if (e2 & DESC_C_MASK) {
            
            if (dpl > cpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        } else {
            
            rpl = new_cs & 3;
            if (rpl > cpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            if (dpl != cpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        }
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, new_cs & 0xfffc);

#ifdef TARGET_X86_64
        
        if (shift == 2) {
            target_ulong rsp;
            
            rsp = ESP;
            PUSHQ(rsp, env->segs[R_CS].selector);
            PUSHQ(rsp, next_eip);
            
            ESP = rsp;
            cpu_x86_load_seg_cache(env, R_CS, (new_cs & 0xfffc) | cpl,
                                   get_seg_base(e1, e2),
                                   get_seg_limit(e1, e2), e2);
            EIP = new_eip;
        } else
#endif
        {
            sp = ESP;
            sp_mask = get_sp_mask(env->segs[R_SS].flags);
            ssp = env->segs[R_SS].base;
            if (shift) {
                PUSHL(ssp, sp, sp_mask, env->segs[R_CS].selector);
                PUSHL(ssp, sp, sp_mask, next_eip);
            } else {
                PUSHW(ssp, sp, sp_mask, env->segs[R_CS].selector);
                PUSHW(ssp, sp, sp_mask, next_eip);
            }

            limit = get_seg_limit(e1, e2);
            if (new_eip > limit)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            
            SET_ESP(sp, sp_mask);
            cpu_x86_load_seg_cache(env, R_CS, (new_cs & 0xfffc) | cpl,
                                   get_seg_base(e1, e2), limit, e2);
            EIP = new_eip;
        }
    } else {
        
        type = (e2 >> DESC_TYPE_SHIFT) & 0x1f;
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        rpl = new_cs & 3;
        switch(type) {
        case 1: 
        case 9: 
        case 5: 
            if (dpl < cpl || dpl < rpl)
                raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            switch_tss(env, new_cs, e1, e2, SWITCH_TSS_CALL, next_eip);
            CC_OP = CC_OP_EFLAGS;
            return;
        case 4: 
        case 12: 
            break;
        default:
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
            break;
        }
        shift = type >> 3;

        if (dpl < cpl || dpl < rpl)
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
        
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG,  new_cs & 0xfffc);
        selector = e1 >> 16;
        offset = (e2 & 0xffff0000) | (e1 & 0x0000ffff);
        param_count = e2 & 0x1f;
        if ((selector & 0xfffc) == 0)
            raise_exception_err(env, EXCP0D_GPF, 0);

        if (load_segment(env, &e1, &e2, selector) != 0)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_S_MASK) || !(e2 & (DESC_CS_MASK)))
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        if (dpl > cpl)
            raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);

        if (!(e2 & DESC_C_MASK) && dpl < cpl) {
            
            get_ss_esp_from_tss(env, &ss, &sp, dpl);
            LOG_PCALL("new ss:esp=%04x:%08x param_count=%d ESP=" TARGET_FMT_lx "\n",
                        ss, sp, param_count, ESP);
            if ((ss & 0xfffc) == 0)
                raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
            if ((ss & 3) != dpl)
                raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
            if (load_segment(env, &ss_e1, &ss_e2, ss) != 0)
                raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
            ss_dpl = (ss_e2 >> DESC_DPL_SHIFT) & 3;
            if (ss_dpl != dpl)
                raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
            if (!(ss_e2 & DESC_S_MASK) ||
                (ss_e2 & DESC_CS_MASK) ||
                !(ss_e2 & DESC_W_MASK))
                raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);
            if (!(ss_e2 & DESC_P_MASK))
                raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);

            

            old_sp_mask = get_sp_mask(env->segs[R_SS].flags);
            old_ssp = env->segs[R_SS].base;

            sp_mask = get_sp_mask(ss_e2);
            ssp = get_seg_base(ss_e1, ss_e2);
            if (shift) {
                PUSHL(ssp, sp, sp_mask, env->segs[R_SS].selector);
                PUSHL(ssp, sp, sp_mask, ESP);
                for(i = param_count - 1; i >= 0; i--) {
                    val = cpu_ldl_kernel(env, old_ssp + ((ESP + i * 4) & old_sp_mask));
                    PUSHL(ssp, sp, sp_mask, val);
                }
            } else {
                PUSHW(ssp, sp, sp_mask, env->segs[R_SS].selector);
                PUSHW(ssp, sp, sp_mask, ESP);
                for(i = param_count - 1; i >= 0; i--) {
                    val = cpu_lduw_kernel(env, old_ssp + ((ESP + i * 2) & old_sp_mask));
                    PUSHW(ssp, sp, sp_mask, val);
                }
            }
            new_stack = 1;
        } else {
            
            sp = ESP;
            sp_mask = get_sp_mask(env->segs[R_SS].flags);
            ssp = env->segs[R_SS].base;
            
            new_stack = 0;
        }

        if (shift) {
            PUSHL(ssp, sp, sp_mask, env->segs[R_CS].selector);
            PUSHL(ssp, sp, sp_mask, next_eip);
        } else {
            PUSHW(ssp, sp, sp_mask, env->segs[R_CS].selector);
            PUSHW(ssp, sp, sp_mask, next_eip);
        }

        

        if (new_stack) {
            ss = (ss & ~3) | dpl;
            cpu_x86_load_seg_cache(env, R_SS, ss,
                                   ssp,
                                   get_seg_limit(ss_e1, ss_e2),
                                   ss_e2);
        }

        selector = (selector & ~3) | dpl;
        cpu_x86_load_seg_cache(env, R_CS, selector,
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
        cpu_x86_set_cpl(env, dpl);
        SET_ESP(sp, sp_mask);
        EIP = offset;
    }
}

void helper_iret_real(CPUX86State *env, int shift)
{
    uint32_t sp, new_cs, new_eip, new_eflags, sp_mask;
    target_ulong ssp;
    int eflags_mask;

    sp_mask = 0xffff; 
    sp = ESP;
    ssp = env->segs[R_SS].base;
    if (shift == 1) {
        
        POPL(ssp, sp, sp_mask, new_eip);
        POPL(ssp, sp, sp_mask, new_cs);
        new_cs &= 0xffff;
        POPL(ssp, sp, sp_mask, new_eflags);
    } else {
        
        POPW(ssp, sp, sp_mask, new_eip);
        POPW(ssp, sp, sp_mask, new_cs);
        POPW(ssp, sp, sp_mask, new_eflags);
    }
    ESP = (ESP & ~sp_mask) | (sp & sp_mask);
    env->segs[R_CS].selector = new_cs;
    env->segs[R_CS].base = (new_cs << 4);
    env->eip = new_eip;
    if (env->eflags & VM_MASK)
        eflags_mask = TF_MASK | AC_MASK | ID_MASK | IF_MASK | RF_MASK | NT_MASK;
    else
        eflags_mask = TF_MASK | AC_MASK | ID_MASK | IF_MASK | IOPL_MASK | RF_MASK | NT_MASK;
    if (shift == 0)
        eflags_mask &= 0xffff;
    cpu_load_eflags(env, new_eflags, eflags_mask);
    env->hflags2 &= ~HF2_NMI_MASK;
}

static inline void validate_seg(CPUX86State *env, int seg_reg, int cpl)
{
    int dpl;
    uint32_t e2;

    if ((seg_reg == R_FS || seg_reg == R_GS) &&
        (env->segs[seg_reg].selector & 0xfffc) == 0)
        return;

    e2 = env->segs[seg_reg].flags;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    if (!(e2 & DESC_CS_MASK) || !(e2 & DESC_C_MASK)) {
        
        if (dpl < cpl) {
            cpu_x86_load_seg_cache(env, seg_reg, 0, 0, 0, 0);
        }
    }
}

static inline void helper_ret_protected(CPUX86State *env,
                                        int shift, int is_iret, int addend)
{
    uint32_t new_cs, new_eflags, new_ss;
    uint32_t new_es, new_ds, new_fs, new_gs;
    uint32_t e1, e2, ss_e1, ss_e2;
    int cpl, dpl, rpl, eflags_mask, iopl;
    target_ulong ssp, sp, new_eip, new_esp, sp_mask;

#ifdef TARGET_X86_64
    if (shift == 2)
        sp_mask = -1;
    else
#endif
        sp_mask = get_sp_mask(env->segs[R_SS].flags);
    sp = ESP;
    ssp = env->segs[R_SS].base;
    new_eflags = 0; 
#ifdef TARGET_X86_64
    if (shift == 2) {
        POPQ(sp, new_eip);
        POPQ(sp, new_cs);
        new_cs &= 0xffff;
        if (is_iret) {
            POPQ(sp, new_eflags);
        }
    } else
#endif
    if (shift == 1) {
        
        POPL(ssp, sp, sp_mask, new_eip);
        POPL(ssp, sp, sp_mask, new_cs);
        new_cs &= 0xffff;
        if (is_iret) {
            POPL(ssp, sp, sp_mask, new_eflags);
            if (new_eflags & VM_MASK)
                goto return_to_vm86;
        }
    } else {
        
        POPW(ssp, sp, sp_mask, new_eip);
        POPW(ssp, sp, sp_mask, new_cs);
        if (is_iret)
            POPW(ssp, sp, sp_mask, new_eflags);
    }
    LOG_PCALL("lret new %04x:" TARGET_FMT_lx " s=%d addend=0x%x\n",
              new_cs, new_eip, shift, addend);
    LOG_PCALL_STATE(env);
    if ((new_cs & 0xfffc) == 0)
        raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    if (load_segment(env, &e1, &e2, new_cs) != 0)
        raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    if (!(e2 & DESC_S_MASK) ||
        !(e2 & DESC_CS_MASK))
        raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    cpl = env->hflags & HF_CPL_MASK;
    rpl = new_cs & 3;
    if (rpl < cpl)
        raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    if (e2 & DESC_C_MASK) {
        if (dpl > rpl)
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    } else {
        if (dpl != rpl)
            raise_exception_err(env, EXCP0D_GPF, new_cs & 0xfffc);
    }
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(env, EXCP0B_NOSEG, new_cs & 0xfffc);

    sp += addend;
    if (rpl == cpl && (!(env->hflags & HF_CS64_MASK) ||
                       ((env->hflags & HF_CS64_MASK) && !is_iret))) {
        
        cpu_x86_load_seg_cache(env, R_CS, new_cs,
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
    } else {
        
#ifdef TARGET_X86_64
        if (shift == 2) {
            POPQ(sp, new_esp);
            POPQ(sp, new_ss);
            new_ss &= 0xffff;
        } else
#endif
        if (shift == 1) {
            
            POPL(ssp, sp, sp_mask, new_esp);
            POPL(ssp, sp, sp_mask, new_ss);
            new_ss &= 0xffff;
        } else {
            
            POPW(ssp, sp, sp_mask, new_esp);
            POPW(ssp, sp, sp_mask, new_ss);
        }
        LOG_PCALL("new ss:esp=%04x:" TARGET_FMT_lx "\n",
                    new_ss, new_esp);
        if ((new_ss & 0xfffc) == 0) {
#ifdef TARGET_X86_64
            
            
            if ((env->hflags & HF_LMA_MASK) && rpl != 3) {
                cpu_x86_load_seg_cache(env, R_SS, new_ss,
                                       0, 0xffffffff,
                                       DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                                       DESC_S_MASK | (rpl << DESC_DPL_SHIFT) |
                                       DESC_W_MASK | DESC_A_MASK);
                ss_e2 = DESC_B_MASK; 
            } else
#endif
            {
                raise_exception_err(env, EXCP0D_GPF, 0);
            }
        } else {
            if ((new_ss & 3) != rpl)
                raise_exception_err(env, EXCP0D_GPF, new_ss & 0xfffc);
            if (load_segment(env, &ss_e1, &ss_e2, new_ss) != 0)
                raise_exception_err(env, EXCP0D_GPF, new_ss & 0xfffc);
            if (!(ss_e2 & DESC_S_MASK) ||
                (ss_e2 & DESC_CS_MASK) ||
                !(ss_e2 & DESC_W_MASK))
                raise_exception_err(env, EXCP0D_GPF, new_ss & 0xfffc);
            dpl = (ss_e2 >> DESC_DPL_SHIFT) & 3;
            if (dpl != rpl)
                raise_exception_err(env, EXCP0D_GPF, new_ss & 0xfffc);
            if (!(ss_e2 & DESC_P_MASK))
                raise_exception_err(env, EXCP0B_NOSEG, new_ss & 0xfffc);
            cpu_x86_load_seg_cache(env, R_SS, new_ss,
                                   get_seg_base(ss_e1, ss_e2),
                                   get_seg_limit(ss_e1, ss_e2),
                                   ss_e2);
        }

        cpu_x86_load_seg_cache(env, R_CS, new_cs,
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
        cpu_x86_set_cpl(env, rpl);
        sp = new_esp;
#ifdef TARGET_X86_64
        if (env->hflags & HF_CS64_MASK)
            sp_mask = -1;
        else
#endif
            sp_mask = get_sp_mask(ss_e2);

        
        validate_seg(env, R_ES, rpl);
        validate_seg(env, R_DS, rpl);
        validate_seg(env, R_FS, rpl);
        validate_seg(env, R_GS, rpl);

        sp += addend;
    }
    SET_ESP(sp, sp_mask);
    env->eip = new_eip;
    if (is_iret) {
        
        eflags_mask = TF_MASK | AC_MASK | ID_MASK | RF_MASK | NT_MASK;
        if (cpl == 0)
            eflags_mask |= IOPL_MASK;
        iopl = (env->eflags >> IOPL_SHIFT) & 3;
        if (cpl <= iopl)
            eflags_mask |= IF_MASK;
        if (shift == 0)
            eflags_mask &= 0xffff;
        cpu_load_eflags(env, new_eflags, eflags_mask);
    }
    return;

 return_to_vm86:
    POPL(ssp, sp, sp_mask, new_esp);
    POPL(ssp, sp, sp_mask, new_ss);
    POPL(ssp, sp, sp_mask, new_es);
    POPL(ssp, sp, sp_mask, new_ds);
    POPL(ssp, sp, sp_mask, new_fs);
    POPL(ssp, sp, sp_mask, new_gs);

    
    cpu_load_eflags(env, new_eflags, TF_MASK | AC_MASK | ID_MASK |
                IF_MASK | IOPL_MASK | VM_MASK | NT_MASK | VIF_MASK | VIP_MASK);
    load_seg_vm(env, R_CS, new_cs & 0xffff);
    cpu_x86_set_cpl(env, 3);
    load_seg_vm(env, R_SS, new_ss & 0xffff);
    load_seg_vm(env, R_ES, new_es & 0xffff);
    load_seg_vm(env, R_DS, new_ds & 0xffff);
    load_seg_vm(env, R_FS, new_fs & 0xffff);
    load_seg_vm(env, R_GS, new_gs & 0xffff);

    env->eip = new_eip & 0xffff;
    ESP = new_esp;
}

void helper_iret_protected(CPUX86State *env, int shift, int next_eip)
{
    int tss_selector, type;
    uint32_t e1, e2;

    
    if (env->eflags & NT_MASK) {
#ifdef TARGET_X86_64
        if (env->hflags & HF_LMA_MASK)
            raise_exception_err(env, EXCP0D_GPF, 0);
#endif
        tss_selector = cpu_lduw_kernel(env, env->tr.base + 0);
        if (tss_selector & 4)
            raise_exception_err(env, EXCP0A_TSS, tss_selector & 0xfffc);
        if (load_segment(env, &e1, &e2, tss_selector) != 0)
            raise_exception_err(env, EXCP0A_TSS, tss_selector & 0xfffc);
        type = (e2 >> DESC_TYPE_SHIFT) & 0x17;
        
        if (type != 3)
            raise_exception_err(env, EXCP0A_TSS, tss_selector & 0xfffc);
        switch_tss(env, tss_selector, e1, e2, SWITCH_TSS_IRET, next_eip);
    } else {
        helper_ret_protected(env, shift, 1, 0);
    }
    env->hflags2 &= ~HF2_NMI_MASK;
}

void helper_lret_protected(CPUX86State *env, int shift, int addend)
{
    helper_ret_protected(env, shift, 0, addend);
}

void helper_sysenter(CPUX86State *env)
{
    if (env->sysenter_cs == 0) {
        raise_exception_err(env, EXCP0D_GPF, 0);
    }
    env->eflags &= ~(VM_MASK | IF_MASK | RF_MASK);
    cpu_x86_set_cpl(env, 0);

#ifdef TARGET_X86_64
    if (env->hflags & HF_LMA_MASK) {
        cpu_x86_load_seg_cache(env, R_CS, env->sysenter_cs & 0xfffc,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK |
                               DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK | DESC_L_MASK);
    } else
#endif
    {
        cpu_x86_load_seg_cache(env, R_CS, env->sysenter_cs & 0xfffc,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK |
                               DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK);
    }
    cpu_x86_load_seg_cache(env, R_SS, (env->sysenter_cs + 8) & 0xfffc,
                           0, 0xffffffff,
                           DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                           DESC_S_MASK |
                           DESC_W_MASK | DESC_A_MASK);
    ESP = env->sysenter_esp;
    EIP = env->sysenter_eip;
}

void helper_sysexit(CPUX86State *env, int dflag)
{
    int cpl;

    cpl = env->hflags & HF_CPL_MASK;
    if (env->sysenter_cs == 0 || cpl != 0) {
        raise_exception_err(env, EXCP0D_GPF, 0);
    }
    cpu_x86_set_cpl(env, 3);
#ifdef TARGET_X86_64
    if (dflag == 2) {
        cpu_x86_load_seg_cache(env, R_CS, ((env->sysenter_cs + 32) & 0xfffc) | 3,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                               DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK | DESC_L_MASK);
        cpu_x86_load_seg_cache(env, R_SS, ((env->sysenter_cs + 40) & 0xfffc) | 3,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                               DESC_W_MASK | DESC_A_MASK);
    } else
#endif
    {
        cpu_x86_load_seg_cache(env, R_CS, ((env->sysenter_cs + 16) & 0xfffc) | 3,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                               DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK);
        cpu_x86_load_seg_cache(env, R_SS, ((env->sysenter_cs + 24) & 0xfffc) | 3,
                               0, 0xffffffff,
                               DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                               DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                               DESC_W_MASK | DESC_A_MASK);
    }
    ESP = ECX;
    EIP = EDX;
}

target_ulong helper_lsl(CPUX86State *env, target_ulong selector1)
{
    unsigned int limit;
    uint32_t e1, e2, eflags, selector;
    int rpl, dpl, cpl, type;

    selector = selector1 & 0xffff;
    eflags = helper_cc_compute_all(env, CC_OP);
    if ((selector & 0xfffc) == 0)
        goto fail;
    if (load_segment(env, &e1, &e2, selector) != 0)
        goto fail;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_S_MASK) {
        if ((e2 & DESC_CS_MASK) && (e2 & DESC_C_MASK)) {
            
        } else {
            if (dpl < cpl || dpl < rpl)
                goto fail;
        }
    } else {
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        switch(type) {
        case 1:
        case 2:
        case 3:
        case 9:
        case 11:
            break;
        default:
            goto fail;
        }
        if (dpl < cpl || dpl < rpl) {
        fail:
            CC_SRC = eflags & ~CC_Z;
            return 0;
        }
    }
    limit = get_seg_limit(e1, e2);
    CC_SRC = eflags | CC_Z;
    return limit;
}

target_ulong helper_lar(CPUX86State *env, target_ulong selector1)
{
    uint32_t e1, e2, eflags, selector;
    int rpl, dpl, cpl, type;

    selector = selector1 & 0xffff;
    eflags = helper_cc_compute_all(env, CC_OP);
    if ((selector & 0xfffc) == 0)
        goto fail;
    if (load_segment(env, &e1, &e2, selector) != 0)
        goto fail;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_S_MASK) {
        if ((e2 & DESC_CS_MASK) && (e2 & DESC_C_MASK)) {
            
        } else {
            if (dpl < cpl || dpl < rpl)
                goto fail;
        }
    } else {
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        switch(type) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 9:
        case 11:
        case 12:
            break;
        default:
            goto fail;
        }
        if (dpl < cpl || dpl < rpl) {
        fail:
            CC_SRC = eflags & ~CC_Z;
            return 0;
        }
    }
    CC_SRC = eflags | CC_Z;
    return e2 & 0x00f0ff00;
}

void helper_verr(CPUX86State *env, target_ulong selector1)
{
    uint32_t e1, e2, eflags, selector;
    int rpl, dpl, cpl;

    selector = selector1 & 0xffff;
    eflags = helper_cc_compute_all(env, CC_OP);
    if ((selector & 0xfffc) == 0)
        goto fail;
    if (load_segment(env, &e1, &e2, selector) != 0)
        goto fail;
    if (!(e2 & DESC_S_MASK))
        goto fail;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_CS_MASK) {
        if (!(e2 & DESC_R_MASK))
            goto fail;
        if (!(e2 & DESC_C_MASK)) {
            if (dpl < cpl || dpl < rpl)
                goto fail;
        }
    } else {
        if (dpl < cpl || dpl < rpl) {
        fail:
            CC_SRC = eflags & ~CC_Z;
            return;
        }
    }
    CC_SRC = eflags | CC_Z;
}

void helper_verw(CPUX86State *env, target_ulong selector1)
{
    uint32_t e1, e2, eflags, selector;
    int rpl, dpl, cpl;

    selector = selector1 & 0xffff;
    eflags = helper_cc_compute_all(env, CC_OP);
    if ((selector & 0xfffc) == 0)
        goto fail;
    if (load_segment(env, &e1, &e2, selector) != 0)
        goto fail;
    if (!(e2 & DESC_S_MASK))
        goto fail;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_CS_MASK) {
        goto fail;
    } else {
        if (dpl < cpl || dpl < rpl)
            goto fail;
        if (!(e2 & DESC_W_MASK)) {
        fail:
            CC_SRC = eflags & ~CC_Z;
            return;
        }
    }
    CC_SRC = eflags | CC_Z;
}

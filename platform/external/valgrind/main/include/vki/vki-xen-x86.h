#ifndef __VKI_XEN_X86_H
#define __VKI_XEN_X86_H

#if defined(__i386__)
#define ___DEFINE_VKI_XEN_GUEST_HANDLE(name, type)			\
    typedef struct { type *p; }						\
        __vki_xen_guest_handle_ ## name;                                \
    typedef struct { union { type *p; vki_xen_uint64_aligned_t q; }; }  \
        __vki_xen_guest_handle_64_ ## name
#define vki_xen_uint64_aligned_t vki_uint64_t __attribute__((aligned(8)))
#define __VKI_XEN_GUEST_HANDLE_64(name) __vki_xen_guest_handle_64_ ## name
#define VKI_XEN_GUEST_HANDLE_64(name) __VKI_XEN_GUEST_HANDLE_64(name)
#else
#define ___DEFINE_VKI_XEN_GUEST_HANDLE(name, type) \
    typedef struct { type *p; } __vki_xen_guest_handle_ ## name
#define vki_xen_uint64_aligned_t vki_uint64_t
#define __DEFINE_VKI_XEN_GUEST_HANDLE(name, type) \
    ___DEFINE_VKI_XEN_GUEST_HANDLE(name, type);   \
    ___DEFINE_VKI_XEN_GUEST_HANDLE(const_##name, const type)
#define DEFINE_VKI_XEN_GUEST_HANDLE(name)   __DEFINE_VKI_XEN_GUEST_HANDLE(name, name)
#define VKI_XEN_GUEST_HANDLE_64(name) VKI_XEN_GUEST_HANDLE(name)
#endif

#define __VKI_XEN_GUEST_HANDLE(name)  __vki_xen_guest_handle_ ## name
#define VKI_XEN_GUEST_HANDLE(name)    __VKI_XEN_GUEST_HANDLE(name)

typedef unsigned long vki_xen_pfn_t;
typedef unsigned long vki_xen_ulong_t;

#if defined(__i386__)
struct vki_xen_cpu_user_regs {
    vki_uint32_t ebx;
    vki_uint32_t ecx;
    vki_uint32_t edx;
    vki_uint32_t esi;
    vki_uint32_t edi;
    vki_uint32_t ebp;
    vki_uint32_t eax;
    vki_uint16_t error_code;    
    vki_uint16_t entry_vector;  
    vki_uint32_t eip;
    vki_uint16_t cs;
    vki_uint8_t  saved_upcall_mask;
    vki_uint8_t  _pad0;
    vki_uint32_t eflags;        
    vki_uint32_t esp;
    vki_uint16_t ss, _pad1;
    vki_uint16_t es, _pad2;
    vki_uint16_t ds, _pad3;
    vki_uint16_t fs, _pad4;
    vki_uint16_t gs, _pad5;
};
#else
struct vki_xen_cpu_user_regs {
    vki_uint64_t r15;
    vki_uint64_t r14;
    vki_uint64_t r13;
    vki_uint64_t r12;
    vki_uint64_t rbp;
    vki_uint64_t rbx;
    vki_uint64_t r11;
    vki_uint64_t r10;
    vki_uint64_t r9;
    vki_uint64_t r8;
    vki_uint64_t rax;
    vki_uint64_t rcx;
    vki_uint64_t rdx;
    vki_uint64_t rsi;
    vki_uint64_t rdi;
    vki_uint32_t error_code;    
    vki_uint32_t entry_vector;  
    vki_uint64_t rip;
    vki_uint16_t cs, _pad0[1];
    vki_uint8_t  saved_upcall_mask;
    vki_uint8_t  _pad1[3];
    vki_uint64_t rflags;      
    vki_uint64_t rsp;
    vki_uint16_t ss, _pad2[3];
    vki_uint16_t es, _pad3[3];
    vki_uint16_t ds, _pad4[3];
    vki_uint16_t fs, _pad5[3]; 
    vki_uint16_t gs, _pad6[3]; 
};
#endif

struct vki_xen_trap_info {
    vki_uint8_t   vector;  
    vki_uint8_t   flags;   
    vki_uint16_t  cs;      
    unsigned long address; 
};

struct vki_xen_vcpu_guest_context {
    
    struct { char x[512]; } fpu_ctxt;       
    unsigned long flags;                    
    struct vki_xen_cpu_user_regs user_regs; 
    struct vki_xen_trap_info trap_ctxt[256];
    unsigned long ldt_base, ldt_ents;       
    unsigned long gdt_frames[16], gdt_ents; 
    unsigned long kernel_ss, kernel_sp;     
    
    unsigned long ctrlreg[8];               
    unsigned long debugreg[8];              
#ifdef __i386__
    unsigned long event_callback_cs;        
    unsigned long event_callback_eip;
    unsigned long failsafe_callback_cs;     
    unsigned long failsafe_callback_eip;
#else
    unsigned long event_callback_eip;
    unsigned long failsafe_callback_eip;
    unsigned long syscall_callback_eip;
#endif
    unsigned long vm_assist;                
#ifdef __x86_64__
    
    vki_uint64_t  fs_base;
    vki_uint64_t  gs_base_kernel;
    vki_uint64_t  gs_base_user;
#endif
};
typedef struct vki_xen_vcpu_guest_context vki_xen_vcpu_guest_context_t;
DEFINE_VKI_XEN_GUEST_HANDLE(vki_xen_vcpu_guest_context_t);

#endif 


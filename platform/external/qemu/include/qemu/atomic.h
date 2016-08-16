/*
 * Simple interface for atomic operations.
 *
 * Copyright (C) 2013 Red Hat, Inc.
 *
 * Author: Paolo Bonzini <pbonzini@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef __QEMU_ATOMIC_H
#define __QEMU_ATOMIC_H 1

#include "qemu/compiler.h"


#define barrier()   ({ asm volatile("" ::: "memory"); (void)0; })

#ifndef __ATOMIC_RELAXED

#if defined(__i386__) || defined(__x86_64__)
#if !QEMU_GNUC_PREREQ(4, 4)
#if defined __x86_64__
#define smp_mb()    ({ asm volatile("mfence" ::: "memory"); (void)0; })
#else
#define smp_mb()    ({ asm volatile("lock; addl $0,0(%%esp) " ::: "memory"); (void)0; })
#endif
#endif
#endif


#ifdef __alpha__
#define smp_read_barrier_depends()   asm volatile("mb":::"memory")
#endif

#if defined(__i386__) || defined(__x86_64__) || defined(__s390x__)

#define smp_wmb()   barrier()
#define smp_rmb()   barrier()

#define atomic_xchg(ptr, i)    (barrier(), __sync_lock_test_and_set(ptr, i))

#define atomic_mb_set(ptr, i)  ((void)atomic_xchg(ptr, i))

#elif defined(_ARCH_PPC)

#define smp_wmb()   ({ asm volatile("eieio" ::: "memory"); (void)0; })
#if defined(__powerpc64__)
#define smp_rmb()   ({ asm volatile("lwsync" ::: "memory"); (void)0; })
#else
#define smp_rmb()   ({ asm volatile("sync" ::: "memory"); (void)0; })
#endif
#define smp_mb()    ({ asm volatile("sync" ::: "memory"); (void)0; })

#endif 

#endif 

#ifndef smp_mb
#define smp_mb()    __sync_synchronize()
#endif

#ifndef smp_wmb
#ifdef __ATOMIC_RELEASE
#define smp_wmb()   __atomic_thread_fence(__ATOMIC_RELEASE)
#else
#define smp_wmb()   __sync_synchronize()
#endif
#endif

#ifndef smp_rmb
#ifdef __ATOMIC_ACQUIRE
#define smp_rmb()   __atomic_thread_fence(__ATOMIC_ACQUIRE)
#else
#define smp_rmb()   __sync_synchronize()
#endif
#endif

#ifndef smp_read_barrier_depends
#ifdef __ATOMIC_CONSUME
#define smp_read_barrier_depends()   __atomic_thread_fence(__ATOMIC_CONSUME)
#else
#define smp_read_barrier_depends()   barrier()
#endif
#endif

#ifndef atomic_read
#define atomic_read(ptr)       (*(__typeof__(*ptr) *volatile) (ptr))
#endif

#ifndef atomic_set
#define atomic_set(ptr, i)     ((*(__typeof__(*ptr) *volatile) (ptr)) = (i))
#endif

#ifndef atomic_mb_read
#define atomic_mb_read(ptr)    ({           \
    typeof(*ptr) _val = atomic_read(ptr);   \
    smp_rmb();                              \
    _val;                                   \
})
#endif

#ifndef atomic_mb_set
#define atomic_mb_set(ptr, i)  do {         \
    smp_wmb();                              \
    atomic_set(ptr, i);                     \
    smp_mb();                               \
} while (0)
#endif

#ifndef atomic_xchg
#if defined(__clang__)
#define atomic_xchg(ptr, i)    __sync_swap(ptr, i)
#elif defined(__ATOMIC_SEQ_CST)
#define atomic_xchg(ptr, i)    ({                           \
    typeof(*ptr) _new = (i), _old;                          \
    __atomic_exchange(ptr, &_new, &_old, __ATOMIC_SEQ_CST); \
    _old;                                                   \
})
#else
#define atomic_xchg(ptr, i)    (smp_mb(), __sync_lock_test_and_set(ptr, i))
#endif
#endif

#define atomic_fetch_inc(ptr)  __sync_fetch_and_add(ptr, 1)
#define atomic_fetch_dec(ptr)  __sync_fetch_and_add(ptr, -1)
#define atomic_fetch_add       __sync_fetch_and_add
#define atomic_fetch_sub       __sync_fetch_and_sub
#define atomic_fetch_and       __sync_fetch_and_and
#define atomic_fetch_or        __sync_fetch_and_or
#define atomic_cmpxchg         __sync_val_compare_and_swap

#define atomic_inc(ptr)        ((void) __sync_fetch_and_add(ptr, 1))
#define atomic_dec(ptr)        ((void) __sync_fetch_and_add(ptr, -1))
#define atomic_add(ptr, n)     ((void) __sync_fetch_and_add(ptr, n))
#define atomic_sub(ptr, n)     ((void) __sync_fetch_and_sub(ptr, n))
#define atomic_and(ptr, n)     ((void) __sync_fetch_and_and(ptr, n))
#define atomic_or(ptr, n)      ((void) __sync_fetch_and_or(ptr, n))

#endif

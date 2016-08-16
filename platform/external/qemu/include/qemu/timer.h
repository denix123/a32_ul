#ifndef QEMU_TIMER_H
#define QEMU_TIMER_H

#include "qemu/typedefs.h"
#include "qemu-common.h"
#include "qemu/notify.h"


#define SCALE_MS 1000000
#define SCALE_US 1000
#define SCALE_NS 1


typedef enum {
    QEMU_CLOCK_REALTIME = 0,
    QEMU_CLOCK_VIRTUAL = 1,
    QEMU_CLOCK_HOST = 2,
    QEMU_CLOCK_MAX
} QEMUClockType;

typedef struct QEMUTimerList QEMUTimerList;

struct QEMUTimerListGroup {
    QEMUTimerList *tl[QEMU_CLOCK_MAX];
};

typedef void QEMUTimerCB(void *opaque);
typedef void QEMUTimerListNotifyCB(void *opaque);

struct QEMUTimer {
    int64_t expire_time;        
    QEMUTimerList *timer_list;
    QEMUTimerCB *cb;
    void *opaque;
    QEMUTimer *next;
    int scale;
};

extern QEMUTimerListGroup main_loop_tlg;


int64_t qemu_clock_get_ns(QEMUClockType type);

static inline int64_t qemu_clock_get_ms(QEMUClockType type)
{
    return qemu_clock_get_ns(type) / SCALE_MS;
}

static inline int64_t qemu_clock_get_us(QEMUClockType type)
{
    return qemu_clock_get_ns(type) / SCALE_US;
}

bool qemu_clock_has_timers(QEMUClockType type);

bool qemu_clock_expired(QEMUClockType type);

bool qemu_clock_use_for_deadline(QEMUClockType type);

int64_t qemu_clock_deadline_ns_all(QEMUClockType type);

QEMUTimerList *qemu_clock_get_main_loop_timerlist(QEMUClockType type);

void qemu_clock_notify(QEMUClockType type);

void qemu_clock_enable(QEMUClockType type, bool enabled);

void qemu_clock_warp(QEMUClockType type);

void qemu_clock_register_reset_notifier(QEMUClockType type,
                                        Notifier *notifier);

void qemu_clock_unregister_reset_notifier(QEMUClockType type,
                                          Notifier *notifier);

bool qemu_clock_run_timers(QEMUClockType type);

bool qemu_clock_run_all_timers(void);


QEMUTimerList *timerlist_new(QEMUClockType type,
                             QEMUTimerListNotifyCB *cb, void *opaque);

void timerlist_free(QEMUTimerList *timer_list);

bool timerlist_has_timers(QEMUTimerList *timer_list);

bool timerlist_expired(QEMUTimerList *timer_list);

int64_t timerlist_deadline_ns(QEMUTimerList *timer_list);

QEMUClockType timerlist_get_clock(QEMUTimerList *timer_list);

bool timerlist_run_timers(QEMUTimerList *timer_list);

void timerlist_notify(QEMUTimerList *timer_list);


void timerlistgroup_init(QEMUTimerListGroup *tlg,
                         QEMUTimerListNotifyCB *cb, void *opaque);

void timerlistgroup_deinit(QEMUTimerListGroup *tlg);

bool timerlistgroup_run_timers(QEMUTimerListGroup *tlg);

int64_t timerlistgroup_deadline_ns(QEMUTimerListGroup *tlg);


void timer_init(QEMUTimer *ts,
                QEMUTimerList *timer_list, int scale,
                QEMUTimerCB *cb, void *opaque);

static inline QEMUTimer *timer_new_tl(QEMUTimerList *timer_list,
                                      int scale,
                                      QEMUTimerCB *cb,
                                      void *opaque)
{
    QEMUTimer *ts = g_malloc0(sizeof(QEMUTimer));
    timer_init(ts, timer_list, scale, cb, opaque);
    return ts;
}

static inline QEMUTimer *timer_new(QEMUClockType type, int scale,
                                   QEMUTimerCB *cb, void *opaque)
{
    return timer_new_tl(main_loop_tlg.tl[type], scale, cb, opaque);
}

static inline QEMUTimer *timer_new_ns(QEMUClockType type, QEMUTimerCB *cb,
                                      void *opaque)
{
    return timer_new(type, SCALE_NS, cb, opaque);
}

static inline QEMUTimer *timer_new_us(QEMUClockType type, QEMUTimerCB *cb,
                                      void *opaque)
{
    return timer_new(type, SCALE_US, cb, opaque);
}

static inline QEMUTimer *timer_new_ms(QEMUClockType type, QEMUTimerCB *cb,
                                      void *opaque)
{
    return timer_new(type, SCALE_MS, cb, opaque);
}

void timer_free(QEMUTimer *ts);

void timer_del(QEMUTimer *ts);

void timer_mod_ns(QEMUTimer *ts, int64_t expire_time);

void timer_mod_anticipate_ns(QEMUTimer *ts, int64_t expire_time);

void timer_mod(QEMUTimer *ts, int64_t expire_timer);

void timer_mod_anticipate(QEMUTimer *ts, int64_t expire_time);

bool timer_pending(QEMUTimer *ts);

bool timer_expired(QEMUTimer *timer_head, int64_t current_time);

uint64_t timer_expire_time_ns(QEMUTimer *ts);

void timer_get(QEMUFile *f, QEMUTimer *ts);

void timer_put(QEMUFile *f, QEMUTimer *ts);


int qemu_timeout_ns_to_ms(int64_t ns);

int qemu_poll_ns(GPollFD *fds, guint nfds, int64_t timeout);

static inline int64_t qemu_soonest_timeout(int64_t timeout1, int64_t timeout2)
{
    return ((uint64_t) timeout1 < (uint64_t) timeout2) ? timeout1 : timeout2;
}

void init_clocks(void);

int64_t cpu_get_ticks(void);
void cpu_enable_ticks(void);
void cpu_disable_ticks(void);

static inline int64_t get_ticks_per_sec(void)
{
    return 1000000000LL;
}


static inline int64_t get_clock_realtime(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000000LL + (tv.tv_usec * 1000);
}

#ifdef _WIN32
extern int64_t clock_freq;

static inline int64_t get_clock(void)
{
    LARGE_INTEGER ti;
    QueryPerformanceCounter(&ti);
    return muldiv64(ti.QuadPart, get_ticks_per_sec(), clock_freq);
}

#else

extern int use_rt_clock;

static inline int64_t get_clock(void)
{
#ifdef CLOCK_MONOTONIC
    if (use_rt_clock) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec * 1000000000LL + ts.tv_nsec;
    } else
#endif
    {
        return get_clock_realtime();
    }
}
#endif

int64_t cpu_get_icount(void);
int64_t cpu_get_clock(void);


#if defined(_ARCH_PPC)

static inline int64_t cpu_get_real_ticks(void)
{
    int64_t retval;
#ifdef _ARCH_PPC64
    __asm__ __volatile__ ("mftb    %0\n\t"
                          "cmpwi   %0,0\n\t"
                          "beq-    $-8"
                          : "=r" (retval));
#else
    
    unsigned long junk;
    __asm__ __volatile__ ("mfspr   %1,269\n\t"  
                          "mfspr   %L0,268\n\t" 
                          "mfspr   %0,269\n\t"  
                          "cmpw    %0,%1\n\t"
                          "bne     $-16"
                          : "=r" (retval), "=r" (junk));
#endif
    return retval;
}

#elif defined(__i386__)

static inline int64_t cpu_get_real_ticks(void)
{
    int64_t val;
    asm volatile ("rdtsc" : "=A" (val));
    return val;
}

#elif defined(__x86_64__)

static inline int64_t cpu_get_real_ticks(void)
{
    uint32_t low,high;
    int64_t val;
    asm volatile("rdtsc" : "=a" (low), "=d" (high));
    val = high;
    val <<= 32;
    val |= low;
    return val;
}

#elif defined(__hppa__)

static inline int64_t cpu_get_real_ticks(void)
{
    int val;
    asm volatile ("mfctl %%cr16, %0" : "=r"(val));
    return val;
}

#elif defined(__ia64)

static inline int64_t cpu_get_real_ticks(void)
{
    int64_t val;
    asm volatile ("mov %0 = ar.itc" : "=r"(val) :: "memory");
    return val;
}

#elif defined(__s390__)

static inline int64_t cpu_get_real_ticks(void)
{
    int64_t val;
    asm volatile("stck 0(%1)" : "=m" (val) : "a" (&val) : "cc");
    return val;
}

#elif defined(__sparc__)

static inline int64_t cpu_get_real_ticks (void)
{
#if defined(_LP64)
    uint64_t        rval;
    asm volatile("rd %%tick,%0" : "=r"(rval));
    return rval;
#else
    union {
        uint64_t i64;
        struct {
            uint32_t high;
            uint32_t low;
        }       i32;
    } rval;
    asm volatile("rd %%tick,%%g1; srlx %%g1,32,%0; mov %%g1,%1"
                 : "=r"(rval.i32.high), "=r"(rval.i32.low) : : "g1");
    return rval.i64;
#endif
}

#elif defined(__mips__) && \
    ((defined(__mips_isa_rev) && __mips_isa_rev >= 2) || defined(__linux__))
#define MIPS_RDHWR(rd, value) {                         \
        __asm__ __volatile__ (".set   push\n\t"         \
                              ".set mips32r2\n\t"       \
                              "rdhwr  %0, "rd"\n\t"     \
                              ".set   pop"              \
                              : "=r" (value));          \
    }

static inline int64_t cpu_get_real_ticks(void)
{
    
    uint32_t count;
    static uint32_t cyc_per_count = 0;

    if (!cyc_per_count) {
        MIPS_RDHWR("$3", cyc_per_count);
    }

    MIPS_RDHWR("$2", count);
    return (int64_t)(count * cyc_per_count);
}

#elif defined(__alpha__)

static inline int64_t cpu_get_real_ticks(void)
{
    uint64_t cc;
    uint32_t cur, ofs;

    asm volatile("rpcc %0" : "=r"(cc));
    cur = cc;
    ofs = cc >> 32;
    return cur - ofs;
}

#else
static inline int64_t cpu_get_real_ticks (void)
{
    static int64_t ticks = 0;
    return ticks++;
}
#endif

#ifdef CONFIG_PROFILER
static inline int64_t profile_getclock(void)
{
    return cpu_get_real_ticks();
}

extern int64_t qemu_time, qemu_time_start;
extern int64_t tlb_flush_time;
extern int64_t dev_time;
#endif

#endif

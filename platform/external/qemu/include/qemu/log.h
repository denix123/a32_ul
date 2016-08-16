#ifndef QEMU_LOG_H
#define QEMU_LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "qemu/compiler.h"
#ifdef NEED_CPU_H
#include "disas/disas.h"
#endif

extern FILE *qemu_logfile;
extern int qemu_loglevel;



static inline bool qemu_log_enabled(void)
{
    return qemu_logfile != NULL;
}

#define CPU_LOG_TB_OUT_ASM (1 << 0)
#define CPU_LOG_TB_IN_ASM  (1 << 1)
#define CPU_LOG_TB_OP      (1 << 2)
#define CPU_LOG_TB_OP_OPT  (1 << 3)
#define CPU_LOG_INT        (1 << 4)
#define CPU_LOG_EXEC       (1 << 5)
#define CPU_LOG_PCALL      (1 << 6)
#define CPU_LOG_IOPORT     (1 << 7)
#define CPU_LOG_TB_CPU     (1 << 8)
#define CPU_LOG_RESET      (1 << 9)
#define LOG_UNIMP          (1 << 10)
#define LOG_GUEST_ERROR    (1 << 11)

static inline bool qemu_loglevel_mask(int mask)
{
    return (qemu_loglevel & mask) != 0;
}


void GCC_FMT_ATTR(1, 2) qemu_log(const char *fmt, ...);

static inline void GCC_FMT_ATTR(1, 0)
qemu_log_vprintf(const char *fmt, va_list va)
{
    if (qemu_logfile) {
        vfprintf(qemu_logfile, fmt, va);
    }
}

void GCC_FMT_ATTR(2, 3) qemu_log_mask(int mask, const char *fmt, ...);



#ifdef NEED_CPU_H

static inline void log_cpu_state(CPUState *cpu, int flags)
{
    if (qemu_log_enabled()) {
        cpu_dump_state(cpu, qemu_logfile, fprintf, flags);
    }
}
static inline void log_cpu_state_mask(int mask, CPUState *cpu, int flags)
{
    if (qemu_loglevel & mask) {
        log_cpu_state(cpu, flags);
    }
}

void target_disas(FILE*, CPUArchState*, target_ulong, target_ulong, int);

static inline void log_target_disas(CPUArchState *env, target_ulong start,
                                    target_ulong len, int flags)
{
    target_disas(qemu_logfile, env, start, len, flags);
}

void disas(FILE*, void*, unsigned long);
static inline void log_disas(void *code, unsigned long size)
{
    disas(qemu_logfile, code, size);
}

#if defined(CONFIG_USER_ONLY)
static inline void log_page_dump(void)
{
    page_dump(qemu_logfile);
}
#endif
#endif  



static inline void qemu_log_flush(void)
{
    fflush(qemu_logfile);
}

static inline void qemu_log_close(void)
{
    if (qemu_logfile) {
        if (qemu_logfile != stderr) {
            fclose(qemu_logfile);
        }
        qemu_logfile = NULL;
    }
}

static inline void qemu_log_set_file(FILE *f)
{
    qemu_logfile = f;
}

typedef struct QEMULogItem {
    int mask;
    const char *name;
    const char *help;
} QEMULogItem;

extern const QEMULogItem qemu_log_items[];

void do_qemu_set_log(int log_flags, bool use_own_buffers);

static inline void qemu_set_log(int log_flags)
{
#ifdef CONFIG_USER_ONLY
    do_qemu_set_log(log_flags, true);
#else
    do_qemu_set_log(log_flags, false);
#endif
}

void qemu_set_log_filename(const char *filename);
int qemu_str_to_log_mask(const char *str);

void qemu_print_log_usage(FILE *f);

#endif

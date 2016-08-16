/*
 * Win32 implementation for mutex/cond/thread functions
 *
 * Copyright Red Hat, Inc. 2010
 *
 * Author:
 *  Paolo Bonzini <pbonzini@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */
#include "qemu-common.h"
#include "qemu/thread.h"
#include <process.h>
#include <assert.h>
#include <limits.h>

static void error_exit(int err, const char *msg)
{
    char *pstr;

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                  NULL, err, 0, (LPTSTR)&pstr, 2, NULL);
    fprintf(stderr, "qemu: %s: %s\n", msg, pstr);
    LocalFree(pstr);
    abort();
}

void qemu_mutex_init(QemuMutex *mutex)
{
    mutex->owner = 0;
    InitializeCriticalSection(&mutex->lock);
}

void qemu_mutex_destroy(QemuMutex *mutex)
{
    assert(mutex->owner == 0);
    DeleteCriticalSection(&mutex->lock);
}

void qemu_mutex_lock(QemuMutex *mutex)
{
    EnterCriticalSection(&mutex->lock);

    assert(mutex->owner == 0);
    mutex->owner = GetCurrentThreadId();
}

int qemu_mutex_trylock(QemuMutex *mutex)
{
    int owned;

    owned = TryEnterCriticalSection(&mutex->lock);
    if (owned) {
        assert(mutex->owner == 0);
        mutex->owner = GetCurrentThreadId();
    }
    return !owned;
}

void qemu_mutex_unlock(QemuMutex *mutex)
{
    assert(mutex->owner == GetCurrentThreadId());
    mutex->owner = 0;
    LeaveCriticalSection(&mutex->lock);
}

void qemu_cond_init(QemuCond *cond)
{
    memset(cond, 0, sizeof(*cond));

    cond->sema = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
    if (!cond->sema) {
        error_exit(GetLastError(), __func__);
    }
    cond->continue_event = CreateEvent(NULL,    
                                       FALSE,   
                                       FALSE,   
                                       NULL);   
    if (!cond->continue_event) {
        error_exit(GetLastError(), __func__);
    }
}

void qemu_cond_destroy(QemuCond *cond)
{
    BOOL result;
    result = CloseHandle(cond->continue_event);
    if (!result) {
        error_exit(GetLastError(), __func__);
    }
    cond->continue_event = 0;
    result = CloseHandle(cond->sema);
    if (!result) {
        error_exit(GetLastError(), __func__);
    }
    cond->sema = 0;
}

void qemu_cond_signal(QemuCond *cond)
{
    DWORD result;

    if (cond->waiters == 0) {
        return;
    }

    cond->target = cond->waiters - 1;
    result = SignalObjectAndWait(cond->sema, cond->continue_event,
                                 INFINITE, FALSE);
    if (result == WAIT_ABANDONED || result == WAIT_FAILED) {
        error_exit(GetLastError(), __func__);
    }
}

void qemu_cond_broadcast(QemuCond *cond)
{
    BOOLEAN result;
    if (cond->waiters == 0) {
        return;
    }

    cond->target = 0;
    result = ReleaseSemaphore(cond->sema, cond->waiters, NULL);
    if (!result) {
        error_exit(GetLastError(), __func__);
    }

    WaitForSingleObject(cond->continue_event, INFINITE);
}

void qemu_cond_wait(QemuCond *cond, QemuMutex *mutex)
{
    cond->waiters++;

    qemu_mutex_unlock(mutex);
    WaitForSingleObject(cond->sema, INFINITE);

    if (InterlockedDecrement(&cond->waiters) == cond->target) {
        SetEvent(cond->continue_event);
    }

    qemu_mutex_lock(mutex);
}

void qemu_sem_init(QemuSemaphore *sem, int init)
{
    
    sem->sema = CreateSemaphore(NULL, init, LONG_MAX, NULL);
}

void qemu_sem_destroy(QemuSemaphore *sem)
{
    CloseHandle(sem->sema);
}

void qemu_sem_post(QemuSemaphore *sem)
{
    ReleaseSemaphore(sem->sema, 1, NULL);
}

int qemu_sem_timedwait(QemuSemaphore *sem, int ms)
{
    int rc = WaitForSingleObject(sem->sema, ms);
    if (rc == WAIT_OBJECT_0) {
        return 0;
    }
    if (rc != WAIT_TIMEOUT) {
        error_exit(GetLastError(), __func__);
    }
    return -1;
}

void qemu_sem_wait(QemuSemaphore *sem)
{
    if (WaitForSingleObject(sem->sema, INFINITE) != WAIT_OBJECT_0) {
        error_exit(GetLastError(), __func__);
    }
}

void qemu_event_init(QemuEvent *ev, bool init)
{
    
    ev->event = CreateEvent(NULL, TRUE, init, NULL);
}

void qemu_event_destroy(QemuEvent *ev)
{
    CloseHandle(ev->event);
}

void qemu_event_set(QemuEvent *ev)
{
    SetEvent(ev->event);
}

void qemu_event_reset(QemuEvent *ev)
{
    ResetEvent(ev->event);
}

void qemu_event_wait(QemuEvent *ev)
{
    WaitForSingleObject(ev->event, INFINITE);
}

struct QemuThreadData {
    
    void             *(*start_routine)(void *);
    void             *arg;
    short             mode;

    
    bool              exited;
    void             *ret;
    CRITICAL_SECTION  cs;
};

static __thread QemuThreadData *qemu_thread_data;

static unsigned __stdcall win32_start_routine(void *arg)
{
    QemuThreadData *data = (QemuThreadData *) arg;
    void *(*start_routine)(void *) = data->start_routine;
    void *thread_arg = data->arg;

    if (data->mode == QEMU_THREAD_DETACHED) {
        g_free(data);
        data = NULL;
    }
    qemu_thread_data = data;
    qemu_thread_exit(start_routine(thread_arg));
    abort();
}

void qemu_thread_exit(void *arg)
{
    QemuThreadData *data = qemu_thread_data;

    if (data) {
        assert(data->mode != QEMU_THREAD_DETACHED);
        data->ret = arg;
        EnterCriticalSection(&data->cs);
        data->exited = true;
        LeaveCriticalSection(&data->cs);
    }
    _endthreadex(0);
}

void *qemu_thread_join(QemuThread *thread)
{
    QemuThreadData *data;
    void *ret;
    HANDLE handle;

    data = thread->data;
    if (!data) {
        return NULL;
    }
    handle = qemu_thread_get_handle(thread);
    if (handle) {
        WaitForSingleObject(handle, INFINITE);
        CloseHandle(handle);
    }
    ret = data->ret;
    assert(data->mode != QEMU_THREAD_DETACHED);
    DeleteCriticalSection(&data->cs);
    g_free(data);
    return ret;
}

void qemu_thread_create(QemuThread *thread,
                       void *(*start_routine)(void *),
                       void *arg, int mode)
{
    HANDLE hThread;
    struct QemuThreadData *data;

    data = g_malloc(sizeof *data);
    data->start_routine = start_routine;
    data->arg = arg;
    data->mode = mode;
    data->exited = false;

    if (data->mode != QEMU_THREAD_DETACHED) {
        InitializeCriticalSection(&data->cs);
    }

    hThread = (HANDLE) _beginthreadex(NULL, 0, win32_start_routine,
                                      data, 0, &thread->tid);
    if (!hThread) {
        error_exit(GetLastError(), __func__);
    }
    CloseHandle(hThread);
    thread->data = (mode == QEMU_THREAD_DETACHED) ? NULL : data;
}

void qemu_thread_get_self(QemuThread *thread)
{
    thread->data = qemu_thread_data;
    thread->tid = GetCurrentThreadId();
}

HANDLE qemu_thread_get_handle(QemuThread *thread)
{
    QemuThreadData *data;
    HANDLE handle;

    data = thread->data;
    if (!data) {
        return NULL;
    }

    assert(data->mode != QEMU_THREAD_DETACHED);
    EnterCriticalSection(&data->cs);
    if (!data->exited) {
        handle = OpenThread(SYNCHRONIZE | THREAD_SUSPEND_RESUME, FALSE,
                            thread->tid);
    } else {
        handle = NULL;
    }
    LeaveCriticalSection(&data->cs);
    return handle;
}

bool qemu_thread_is_self(QemuThread *thread)
{
    return GetCurrentThreadId() == thread->tid;
}

/*
 * QEMU System Emulator
 *
 * Copyright (c) 2003-2008 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef QEMU_FILE_H
#define QEMU_FILE_H 1

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>  
#include <sys/types.h>  

#include "qemu/typedefs.h"  

struct iovec;


typedef int (QEMUFilePutBufferFunc)(void *opaque, const uint8_t *buf,
                                    int64_t pos, int size);

typedef int (QEMUFileGetBufferFunc)(void *opaque, uint8_t *buf,
                                    int64_t pos, int size);

typedef int (QEMUFileCloseFunc)(void *opaque);

typedef int (QEMUFileGetFD)(void *opaque);

typedef ssize_t (QEMUFileWritevBufferFunc)(void *opaque, struct iovec *iov,
                                           int iovcnt, int64_t pos);

typedef int (QEMURamHookFunc)(QEMUFile *f, void *opaque, uint64_t flags);

#define RAM_CONTROL_SETUP    0
#define RAM_CONTROL_ROUND    1
#define RAM_CONTROL_HOOK     2
#define RAM_CONTROL_FINISH   3

typedef size_t (QEMURamSaveFunc)(QEMUFile *f, void *opaque,
                               uint64_t block_offset,
                               uint64_t offset,
                               size_t size,
                               int *bytes_sent);

typedef struct QEMUFileOps {
    QEMUFilePutBufferFunc *put_buffer;
    QEMUFileGetBufferFunc *get_buffer;
    QEMUFileCloseFunc *close;
    QEMUFileGetFD *get_fd;
    QEMUFileWritevBufferFunc *writev_buffer;
    QEMURamHookFunc *before_ram_iterate;
    QEMURamHookFunc *after_ram_iterate;
    QEMURamHookFunc *hook_ram_load;
    QEMURamSaveFunc *save_page;
} QEMUFileOps;

QEMUFile *qemu_fopen_ops(void *opaque, const QEMUFileOps *ops);
QEMUFile *qemu_fopen(const char *filename, const char *mode);
QEMUFile *qemu_fdopen(int fd, const char *mode);
QEMUFile *qemu_fopen_socket(int fd, const char *mode);
QEMUFile *qemu_popen_cmd(const char *command, const char *mode);
int qemu_get_fd(QEMUFile *f);
int qemu_fclose(QEMUFile *f);
int64_t qemu_ftell(QEMUFile *f);
void qemu_put_buffer(QEMUFile *f, const uint8_t *buf, int size);
void qemu_put_byte(QEMUFile *f, int v);

void qemu_file_set_error(QEMUFile* f, int error);
int qemu_file_has_error(QEMUFile* f);
void qemu_file_put_notify(QEMUFile* f);

void qemu_put_buffer_async(QEMUFile *f, const uint8_t *buf, int size);
bool qemu_file_mode_is_not_valid(const char *mode);

static inline void qemu_put_ubyte(QEMUFile *f, unsigned int v)
{
    qemu_put_byte(f, (int)v);
}

#define qemu_put_sbyte qemu_put_byte

void qemu_put_be16(QEMUFile *f, unsigned int v);
void qemu_put_be32(QEMUFile *f, unsigned int v);
void qemu_put_be64(QEMUFile *f, uint64_t v);
int qemu_get_buffer(QEMUFile *f, uint8_t *buf, int size);
int qemu_get_byte(QEMUFile *f);
#ifdef CONFIG_ANDROID
void qemu_put_float(QEMUFile *f, float v);
#endif

void qemu_update_position(QEMUFile *f, size_t size);

static inline unsigned int qemu_get_ubyte(QEMUFile *f)
{
    return (unsigned int)qemu_get_byte(f);
}

#define qemu_get_sbyte qemu_get_byte

unsigned int qemu_get_be16(QEMUFile *f);
unsigned int qemu_get_be32(QEMUFile *f);
uint64_t qemu_get_be64(QEMUFile *f);
#ifdef CONFIG_ANDROID
float qemu_get_float(QEMUFile *f);
#endif
int qemu_file_rate_limit(QEMUFile *f);
void qemu_file_reset_rate_limit(QEMUFile *f);
void qemu_file_set_rate_limit(QEMUFile *f, int64_t new_rate);
int64_t qemu_file_get_rate_limit(QEMUFile *f);
int qemu_file_get_error(QEMUFile *f);
void qemu_fflush(QEMUFile *f);

static inline void qemu_put_be64s(QEMUFile *f, const uint64_t *pv)
{
    qemu_put_be64(f, *pv);
}

static inline void qemu_put_be32s(QEMUFile *f, const uint32_t *pv)
{
    qemu_put_be32(f, *pv);
}

static inline void qemu_put_be16s(QEMUFile *f, const uint16_t *pv)
{
    qemu_put_be16(f, *pv);
}

static inline void qemu_put_8s(QEMUFile *f, const uint8_t *pv)
{
    qemu_put_byte(f, *pv);
}

static inline void qemu_get_be64s(QEMUFile *f, uint64_t *pv)
{
    *pv = qemu_get_be64(f);
}

static inline void qemu_get_be32s(QEMUFile *f, uint32_t *pv)
{
    *pv = qemu_get_be32(f);
}

static inline void qemu_get_be16s(QEMUFile *f, uint16_t *pv)
{
    *pv = qemu_get_be16(f);
}

static inline void qemu_get_8s(QEMUFile *f, uint8_t *pv)
{
    *pv = qemu_get_byte(f);
}

static inline void qemu_put_sbuffer(QEMUFile *f, const int8_t *buf, int size)
{
    qemu_put_buffer(f, (const uint8_t *)buf, size);
}

static inline void qemu_put_sbe16(QEMUFile *f, int v)
{
    qemu_put_be16(f, (unsigned int)v);
}

static inline void qemu_put_sbe32(QEMUFile *f, int v)
{
    qemu_put_be32(f, (unsigned int)v);
}

static inline void qemu_put_sbe64(QEMUFile *f, int64_t v)
{
    qemu_put_be64(f, (uint64_t)v);
}

static inline size_t qemu_get_sbuffer(QEMUFile *f, int8_t *buf, int size)
{
    return qemu_get_buffer(f, (uint8_t *)buf, size);
}

static inline int qemu_get_sbe16(QEMUFile *f)
{
    return (int)qemu_get_be16(f);
}

static inline int qemu_get_sbe32(QEMUFile *f)
{
    return (int)qemu_get_be32(f);
}

static inline int64_t qemu_get_sbe64(QEMUFile *f)
{
    return (int64_t)qemu_get_be64(f);
}

static inline void qemu_put_s8s(QEMUFile *f, const int8_t *pv)
{
    qemu_put_8s(f, (const uint8_t *)pv);
}

static inline void qemu_put_sbe16s(QEMUFile *f, const int16_t *pv)
{
    qemu_put_be16s(f, (const uint16_t *)pv);
}

static inline void qemu_put_sbe32s(QEMUFile *f, const int32_t *pv)
{
    qemu_put_be32s(f, (const uint32_t *)pv);
}

static inline void qemu_put_sbe64s(QEMUFile *f, const int64_t *pv)
{
    qemu_put_be64s(f, (const uint64_t *)pv);
}

static inline void qemu_get_s8s(QEMUFile *f, int8_t *pv)
{
    qemu_get_8s(f, (uint8_t *)pv);
}

static inline void qemu_get_sbe16s(QEMUFile *f, int16_t *pv)
{
    qemu_get_be16s(f, (uint16_t *)pv);
}

static inline void qemu_get_sbe32s(QEMUFile *f, int32_t *pv)
{
    qemu_get_be32s(f, (uint32_t *)pv);
}

static inline void qemu_get_sbe64s(QEMUFile *f, int64_t *pv)
{
    qemu_get_be64s(f, (uint64_t *)pv);
}

#ifdef CONFIG_ANDROID
void qemu_put_string(QEMUFile *f, const char* str);
char* qemu_get_string(QEMUFile *f);
#endif

typedef enum {
    Q_FIELD_END,          
    Q_FIELD_BYTE,         
    Q_FIELD_INT16,        
    Q_FIELD_INT32,        
    Q_FIELD_INT64,        
    Q_FIELD_BUFFER,       
    Q_FIELD_BUFFER_SIZE,  
} QFieldType;

typedef struct {
    QFieldType  type : 16; 
    uint16_t    offset;    
} QField;

#define  QFIELD_BEGIN(name)  \
    static const QField    name[] = {

#define  _QFIELD_(t, f)    { t, offsetof(QFIELD_STRUCT,f) }
#define  QFIELD_BYTE(f)   _QFIELD_(Q_FIELD_BYTE, f)
#define  QFIELD_INT16(f)  _QFIELD_(Q_FIELD_INT16, f)
#define  QFIELD_INT32(f)  _QFIELD_(Q_FIELD_INT32, f)
#define  QFIELD_INT64(f)  _QFIELD_(Q_FIELD_INT64, f)
#define  QFIELD_TL(f)     _QFIELD_(Q_FIELD_TL, f)

#define  _QFIELD_SIZEOF(f)   sizeof(((QFIELD_STRUCT*)0)->f)

#define  QFIELD_BUFFER(f)  \
    _QFIELD_(Q_FIELD_BUFFER, f), \
    { Q_FIELD_BUFFER_SIZE, (uint16_t)(_QFIELD_SIZEOF(f) >> 16) }, \
    { Q_FIELD_BUFFER_SIZE, (uint16_t) _QFIELD_SIZEOF(f) }

#define  QFIELD_END           \
        { Q_FIELD_END, 0 },   \
    };

extern void  qemu_put_struct(QEMUFile*  f, const QField*  fields, const void*  s);
extern int   qemu_get_struct(QEMUFile*  f, const QField*  fields, void*  s);

#endif 

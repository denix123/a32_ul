/*
 * QEMU VNC display driver
 *
 * Copyright (C) 2006 Anthony Liguori <anthony@codemonkey.ws>
 * Copyright (C) 2006 Fabrice Bellard
 * Copyright (C) 2009 Red Hat, Inc
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

#ifndef __QEMU_VNC_H
#define __QEMU_VNC_H

#include "qemu-common.h"
#include "ui/console.h"
#include "monitor/monitor.h"
#include "audio/audio.h"
#include <zlib.h>

#include "keymaps.h"


#ifdef _VNC_DEBUG
#define VNC_DEBUG(fmt, ...) do { fprintf(stderr, fmt, ## __VA_ARGS__); } while (0)
#else
#define VNC_DEBUG(fmt, ...) do { } while (0)
#endif


typedef struct Buffer
{
    size_t capacity;
    size_t offset;
    uint8_t *buffer;
} Buffer;

typedef struct VncState VncState;

typedef int VncReadEvent(VncState *vs, uint8_t *data, size_t len);

typedef void VncWritePixels(VncState *vs, void *data, int size);

typedef void VncSendHextileTile(VncState *vs,
                                int x, int y, int w, int h,
                                void *last_bg,
                                void *last_fg,
                                int *has_bg, int *has_fg);

#define VNC_MAX_WIDTH 2048
#define VNC_MAX_HEIGHT 2048
#define VNC_DIRTY_WORDS (VNC_MAX_WIDTH / (16 * 32))

#define VNC_AUTH_CHALLENGE_SIZE 16

typedef struct VncDisplay VncDisplay;

#ifdef CONFIG_VNC_TLS
#include "vnc-tls.h"
#include "vnc-auth-vencrypt.h"
#endif
#ifdef CONFIG_VNC_SASL
#include "vnc-auth-sasl.h"
#endif


struct VncDisplay
{
    int lsock;
    DisplayState *ds;
    VncState *clients;
    kbd_layout_t *kbd_layout;

    char *display;
    char *password;
    int auth;
#ifdef CONFIG_VNC_TLS
    int subauth; 
    VncDisplayTLS tls;
#endif
#ifdef CONFIG_VNC_SASL
    VncDisplaySASL sasl;
#endif
};

struct VncSurface
{
    uint32_t dirty[VNC_MAX_HEIGHT][VNC_DIRTY_WORDS];
    DisplaySurface *ds;
};

struct VncState
{
    QEMUTimer *timer;
    int csock;

    DisplayState *ds;
    struct VncSurface guest;   
    struct VncSurface server;  

    VncDisplay *vd;
    int need_update;
    int force_update;
    uint32_t features;
    int absolute;
    int last_x;
    int last_y;

    uint32_t vnc_encoding;
    uint8_t tight_quality;
    uint8_t tight_compression;

    int major;
    int minor;

    char challenge[VNC_AUTH_CHALLENGE_SIZE];
#ifdef CONFIG_VNC_TLS
    VncStateTLS tls;
#endif
#ifdef CONFIG_VNC_SASL
    VncStateSASL sasl;
#endif

    Buffer output;
    Buffer input;
    
    VncWritePixels *write_pixels;
    VncSendHextileTile *send_hextile_tile;
    DisplaySurface clientds;

    CaptureVoiceOut *audio_cap;
    struct audsettings as;

    VncReadEvent *read_handler;
    size_t read_handler_expect;
    
    uint8_t modifiers_state[256];

    Buffer zlib;
    Buffer zlib_tmp;
    z_stream zlib_stream[4];

    VncState *next;
};



enum {
    VNC_AUTH_INVALID = 0,
    VNC_AUTH_NONE = 1,
    VNC_AUTH_VNC = 2,
    VNC_AUTH_RA2 = 5,
    VNC_AUTH_RA2NE = 6,
    VNC_AUTH_TIGHT = 16,
    VNC_AUTH_ULTRA = 17,
    VNC_AUTH_TLS = 18,      
    VNC_AUTH_VENCRYPT = 19, 
    VNC_AUTH_SASL = 20,     
};

enum {
    VNC_AUTH_VENCRYPT_PLAIN = 256,
    VNC_AUTH_VENCRYPT_TLSNONE = 257,
    VNC_AUTH_VENCRYPT_TLSVNC = 258,
    VNC_AUTH_VENCRYPT_TLSPLAIN = 259,
    VNC_AUTH_VENCRYPT_X509NONE = 260,
    VNC_AUTH_VENCRYPT_X509VNC = 261,
    VNC_AUTH_VENCRYPT_X509PLAIN = 262,
    VNC_AUTH_VENCRYPT_X509SASL = 263,
    VNC_AUTH_VENCRYPT_TLSSASL = 264,
};



#define VNC_ENCODING_RAW                  0x00000000
#define VNC_ENCODING_COPYRECT             0x00000001
#define VNC_ENCODING_RRE                  0x00000002
#define VNC_ENCODING_CORRE                0x00000004
#define VNC_ENCODING_HEXTILE              0x00000005
#define VNC_ENCODING_ZLIB                 0x00000006
#define VNC_ENCODING_TIGHT                0x00000007
#define VNC_ENCODING_ZLIBHEX              0x00000008
#define VNC_ENCODING_TRLE                 0x0000000f
#define VNC_ENCODING_ZRLE                 0x00000010
#define VNC_ENCODING_ZYWRLE               0x00000011
#define VNC_ENCODING_COMPRESSLEVEL0       0xFFFFFF00 
#define VNC_ENCODING_QUALITYLEVEL0        0xFFFFFFE0 
#define VNC_ENCODING_XCURSOR              0xFFFFFF10 
#define VNC_ENCODING_RICH_CURSOR          0xFFFFFF11 
#define VNC_ENCODING_POINTER_POS          0xFFFFFF18 
#define VNC_ENCODING_LASTRECT             0xFFFFFF20 
#define VNC_ENCODING_DESKTOPRESIZE        0xFFFFFF21 
#define VNC_ENCODING_POINTER_TYPE_CHANGE  0XFFFFFEFF 
#define VNC_ENCODING_EXT_KEY_EVENT        0XFFFFFEFE 
#define VNC_ENCODING_AUDIO                0XFFFFFEFD 
#define VNC_ENCODING_WMVi                 0x574D5669



#define VNC_TIGHT_CCB_RESET_MASK   (0x0f)
#define VNC_TIGHT_CCB_TYPE_MASK    (0x0f << 4)
#define VNC_TIGHT_CCB_TYPE_FILL    (0x08 << 4)
#define VNC_TIGHT_CCB_TYPE_JPEG    (0x09 << 4)
#define VNC_TIGHT_CCB_BASIC_MAX    (0x07 << 4)
#define VNC_TIGHT_CCB_BASIC_ZLIB   (0x03 << 4)
#define VNC_TIGHT_CCB_BASIC_FILTER (0x04 << 4)


#define VNC_FEATURE_RESIZE                   0
#define VNC_FEATURE_HEXTILE                  1
#define VNC_FEATURE_POINTER_TYPE_CHANGE      2
#define VNC_FEATURE_WMVI                     3
#define VNC_FEATURE_TIGHT                    4
#define VNC_FEATURE_ZLIB                     5
#define VNC_FEATURE_COPYRECT                 6

#define VNC_FEATURE_RESIZE_MASK              (1 << VNC_FEATURE_RESIZE)
#define VNC_FEATURE_HEXTILE_MASK             (1 << VNC_FEATURE_HEXTILE)
#define VNC_FEATURE_POINTER_TYPE_CHANGE_MASK (1 << VNC_FEATURE_POINTER_TYPE_CHANGE)
#define VNC_FEATURE_WMVI_MASK                (1 << VNC_FEATURE_WMVI)
#define VNC_FEATURE_TIGHT_MASK               (1 << VNC_FEATURE_TIGHT)
#define VNC_FEATURE_ZLIB_MASK                (1 << VNC_FEATURE_ZLIB)
#define VNC_FEATURE_COPYRECT_MASK            (1 << VNC_FEATURE_COPYRECT)



void vnc_client_read(void *opaque);
void vnc_client_write(void *opaque);

long vnc_client_read_buf(VncState *vs, uint8_t *data, size_t datalen);
long vnc_client_write_buf(VncState *vs, const uint8_t *data, size_t datalen);

void vnc_write(VncState *vs, const void *data, size_t len);
void vnc_write_u32(VncState *vs, uint32_t value);
void vnc_write_s32(VncState *vs, int32_t value);
void vnc_write_u16(VncState *vs, uint16_t value);
void vnc_write_u8(VncState *vs, uint8_t value);
void vnc_flush(VncState *vs);
void vnc_read_when(VncState *vs, VncReadEvent *func, size_t expecting);


uint8_t read_u8(uint8_t *data, size_t offset);
uint16_t read_u16(uint8_t *data, size_t offset);
int32_t read_s32(uint8_t *data, size_t offset);
uint32_t read_u32(uint8_t *data, size_t offset);

void vnc_client_error(VncState *vs);
int vnc_client_io_error(VncState *vs, int ret, int last_errno);

void start_client_init(VncState *vs);
void start_auth_vnc(VncState *vs);

void buffer_reserve(Buffer *buffer, size_t len);
int buffer_empty(Buffer *buffer);
uint8_t *buffer_end(Buffer *buffer);
void buffer_reset(Buffer *buffer);
void buffer_append(Buffer *buffer, const void *data, size_t len);



char *vnc_socket_local_addr(const char *format, int fd);
char *vnc_socket_remote_addr(const char *format, int fd);

#endif 
/* Copyright (C) 2002 Jean-Marc Valin */
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   
   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   
   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   
   - Neither the name of the Xiph.org Foundation nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef SPEEX_JITTER_H
#define SPEEX_JITTER_H

#include "speex/speex_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct JitterBuffer_;

typedef struct JitterBuffer_ JitterBuffer;

typedef struct _JitterBufferPacket JitterBufferPacket;

struct _JitterBufferPacket {
   char        *data;       
   spx_uint32_t len;        
   spx_uint32_t timestamp;  
   spx_uint32_t span;       
   spx_uint16_t sequence;   
   spx_uint32_t user_data;  
};

#define JITTER_BUFFER_OK 0
#define JITTER_BUFFER_MISSING 1
#define JITTER_BUFFER_INSERTION 2
#define JITTER_BUFFER_INTERNAL_ERROR -1
#define JITTER_BUFFER_BAD_ARGUMENT -2


#define JITTER_BUFFER_SET_MARGIN 0
#define JITTER_BUFFER_GET_MARGIN 1

#define JITTER_BUFFER_GET_AVAILABLE_COUNT 3
#define JITTER_BUFFER_GET_AVALIABLE_COUNT 3

#define JITTER_BUFFER_SET_DESTROY_CALLBACK 4
#define JITTER_BUFFER_GET_DESTROY_CALLBACK 5

#define JITTER_BUFFER_SET_DELAY_STEP 6
#define JITTER_BUFFER_GET_DELAY_STEP 7

#define JITTER_BUFFER_SET_CONCEALMENT_SIZE 8
#define JITTER_BUFFER_GET_CONCEALMENT_SIZE 9

#define JITTER_BUFFER_SET_MAX_LATE_RATE 10
#define JITTER_BUFFER_GET_MAX_LATE_RATE 11

#define JITTER_BUFFER_SET_LATE_COST 12
#define JITTER_BUFFER_GET_LATE_COST 13


JitterBuffer *jitter_buffer_init(int step_size);

void jitter_buffer_reset(JitterBuffer *jitter);

void jitter_buffer_destroy(JitterBuffer *jitter);

void jitter_buffer_put(JitterBuffer *jitter, const JitterBufferPacket *packet);

int jitter_buffer_get(JitterBuffer *jitter, JitterBufferPacket *packet, spx_int32_t desired_span, spx_int32_t *start_offset);

int jitter_buffer_get_another(JitterBuffer *jitter, JitterBufferPacket *packet);

int jitter_buffer_get_pointer_timestamp(JitterBuffer *jitter);

void jitter_buffer_tick(JitterBuffer *jitter);

void jitter_buffer_remaining_span(JitterBuffer *jitter, spx_uint32_t rem);

int jitter_buffer_ctl(JitterBuffer *jitter, int request, void *ptr);

int jitter_buffer_update_delay(JitterBuffer *jitter, JitterBufferPacket *packet, spx_int32_t *start_offset);


#ifdef __cplusplus
}
#endif

#endif

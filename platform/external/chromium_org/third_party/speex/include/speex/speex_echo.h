/* Copyright (C) Jean-Marc Valin */
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SPEEX_ECHO_H
#define SPEEX_ECHO_H
#include "speex/speex_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SPEEX_ECHO_GET_FRAME_SIZE 3

#define SPEEX_ECHO_SET_SAMPLING_RATE 24
#define SPEEX_ECHO_GET_SAMPLING_RATE 25

#define SPEEX_ECHO_GET_IMPULSE_RESPONSE_SIZE 27

#define SPEEX_ECHO_GET_IMPULSE_RESPONSE 29

struct SpeexEchoState_;


typedef struct SpeexEchoState_ SpeexEchoState;

SpeexEchoState *speex_echo_state_init(int frame_size, int filter_length);

SpeexEchoState *speex_echo_state_init_mc(int frame_size, int filter_length, int nb_mic, int nb_speakers);

void speex_echo_state_destroy(SpeexEchoState *st);

void speex_echo_cancellation(SpeexEchoState *st, const spx_int16_t *rec, const spx_int16_t *play, spx_int16_t *out);

void speex_echo_cancel(SpeexEchoState *st, const spx_int16_t *rec, const spx_int16_t *play, spx_int16_t *out, spx_int32_t *Yout);

void speex_echo_capture(SpeexEchoState *st, const spx_int16_t *rec, spx_int16_t *out);

void speex_echo_playback(SpeexEchoState *st, const spx_int16_t *play);

void speex_echo_state_reset(SpeexEchoState *st);

int speex_echo_ctl(SpeexEchoState *st, int request, void *ptr);



struct SpeexDecorrState_;

typedef struct SpeexDecorrState_ SpeexDecorrState;


SpeexDecorrState *speex_decorrelate_new(int rate, int channels, int frame_size);

void speex_decorrelate(SpeexDecorrState *st, const spx_int16_t *in, spx_int16_t *out, int strength);

void speex_decorrelate_destroy(SpeexDecorrState *st);


#ifdef __cplusplus
}
#endif


#endif

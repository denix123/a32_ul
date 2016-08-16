/* Copyright (C) 2003 Epic Games
   Written by Jean-Marc Valin */
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

#ifndef SPEEX_PREPROCESS_H
#define SPEEX_PREPROCESS_H

#include "speex/speex_types.h"

#ifdef __cplusplus
extern "C" {
#endif
   
struct SpeexPreprocessState_;

typedef struct SpeexPreprocessState_ SpeexPreprocessState;


SpeexPreprocessState *speex_preprocess_state_init(int frame_size, int sampling_rate);

void speex_preprocess_state_destroy(SpeexPreprocessState *st);

int speex_preprocess_run(SpeexPreprocessState *st, spx_int16_t *x);

int speex_preprocess(SpeexPreprocessState *st, spx_int16_t *x, spx_int32_t *echo);

void speex_preprocess_estimate_update(SpeexPreprocessState *st, spx_int16_t *x);

int speex_preprocess_ctl(SpeexPreprocessState *st, int request, void *ptr);



#define SPEEX_PREPROCESS_SET_DENOISE 0
#define SPEEX_PREPROCESS_GET_DENOISE 1

#define SPEEX_PREPROCESS_SET_AGC 2
#define SPEEX_PREPROCESS_GET_AGC 3

#define SPEEX_PREPROCESS_SET_VAD 4
#define SPEEX_PREPROCESS_GET_VAD 5

#define SPEEX_PREPROCESS_SET_AGC_LEVEL 6
#define SPEEX_PREPROCESS_GET_AGC_LEVEL 7

#define SPEEX_PREPROCESS_SET_DEREVERB 8
#define SPEEX_PREPROCESS_GET_DEREVERB 9

#define SPEEX_PREPROCESS_SET_DEREVERB_LEVEL 10
#define SPEEX_PREPROCESS_GET_DEREVERB_LEVEL 11

#define SPEEX_PREPROCESS_SET_DEREVERB_DECAY 12
#define SPEEX_PREPROCESS_GET_DEREVERB_DECAY 13

#define SPEEX_PREPROCESS_SET_PROB_START 14
#define SPEEX_PREPROCESS_GET_PROB_START 15

#define SPEEX_PREPROCESS_SET_PROB_CONTINUE 16
#define SPEEX_PREPROCESS_GET_PROB_CONTINUE 17

#define SPEEX_PREPROCESS_SET_NOISE_SUPPRESS 18
#define SPEEX_PREPROCESS_GET_NOISE_SUPPRESS 19

#define SPEEX_PREPROCESS_SET_ECHO_SUPPRESS 20
#define SPEEX_PREPROCESS_GET_ECHO_SUPPRESS 21

#define SPEEX_PREPROCESS_SET_ECHO_SUPPRESS_ACTIVE 22
#define SPEEX_PREPROCESS_GET_ECHO_SUPPRESS_ACTIVE 23

#define SPEEX_PREPROCESS_SET_ECHO_STATE 24
#define SPEEX_PREPROCESS_GET_ECHO_STATE 25

#define SPEEX_PREPROCESS_SET_AGC_INCREMENT 26

#define SPEEX_PREPROCESS_GET_AGC_INCREMENT 27

#define SPEEX_PREPROCESS_SET_AGC_DECREMENT 28

#define SPEEX_PREPROCESS_GET_AGC_DECREMENT 29

#define SPEEX_PREPROCESS_SET_AGC_MAX_GAIN 30

#define SPEEX_PREPROCESS_GET_AGC_MAX_GAIN 31

#define SPEEX_PREPROCESS_GET_AGC_LOUDNESS 33

#define SPEEX_PREPROCESS_GET_AGC_GAIN 35

#define SPEEX_PREPROCESS_GET_PSD_SIZE 37

#define SPEEX_PREPROCESS_GET_PSD 39

#define SPEEX_PREPROCESS_GET_NOISE_PSD_SIZE 41

#define SPEEX_PREPROCESS_GET_NOISE_PSD 43

#define SPEEX_PREPROCESS_GET_PROB 45

#define SPEEX_PREPROCESS_SET_AGC_TARGET 46
#define SPEEX_PREPROCESS_GET_AGC_TARGET 47

#ifdef __cplusplus
}
#endif

#endif

/* Copyright (C) 2002 Jean-Marc Valin*/
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

#ifndef STEREO_H
#define STEREO_H

#include "speex/speex_types.h"
#include "speex/speex_bits.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpeexStereoState {
   float balance;      
   float e_ratio;      
   float smooth_left;  
   float smooth_right; 
   float reserved1;    
   float reserved2;    
} SpeexStereoState;

#define SPEEX_STEREO_STATE_INIT {1,.5,1,1,0,0}

SpeexStereoState *speex_stereo_state_init();

void speex_stereo_state_reset(SpeexStereoState *stereo);

void speex_stereo_state_destroy(SpeexStereoState *stereo);

void speex_encode_stereo(float *data, int frame_size, SpeexBits *bits);

void speex_encode_stereo_int(spx_int16_t *data, int frame_size, SpeexBits *bits);

void speex_decode_stereo(float *data, int frame_size, SpeexStereoState *stereo);

void speex_decode_stereo_int(spx_int16_t *data, int frame_size, SpeexStereoState *stereo);

int speex_std_stereo_request_handler(SpeexBits *bits, void *state, void *data);

#ifdef __cplusplus
}
#endif

#endif

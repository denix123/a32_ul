/* Copyright (C) 2002-2006 Jean-Marc Valin */
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

#ifndef NB_CELP_H
#define NB_CELP_H

#include "modes.h"
#include <speex/speex_bits.h>
#include <speex/speex_callbacks.h>
#include "vbr.h"
#include "filters.h"

#ifdef VORBIS_PSYCHO
#include "vorbis_psy.h"
#endif

typedef struct EncState {
   const SpeexMode *mode;        
   int    first;                 
   int    frameSize;             
   int    subframeSize;          
   int    nbSubframes;           
   int    windowSize;            
   int    lpcSize;               
   int    min_pitch;             
   int    max_pitch;             

   spx_word32_t cumul_gain;      
   int    bounded_pitch;         
   int    ol_pitch;              
   int    ol_voiced;             
   int   *pitch;

#ifdef VORBIS_PSYCHO
   VorbisPsy *psy;
   float *psy_window;
   float *curve;
   float *old_curve;
#endif

   spx_word16_t  gamma1;         
   spx_word16_t  gamma2;         
   spx_word16_t  lpc_floor;      
   char  *stack;                 
   spx_word16_t *winBuf;         
   spx_word16_t *excBuf;         
   spx_word16_t *exc;            
   spx_word16_t *swBuf;          
   spx_word16_t *sw;             
   const spx_word16_t *window;   
   const spx_word16_t *lagWindow;      
   spx_lsp_t *old_lsp;           
   spx_lsp_t *old_qlsp;          
   spx_mem_t *mem_sp;            
   spx_mem_t *mem_sw;            
   spx_mem_t *mem_sw_whole;      
   spx_mem_t *mem_exc;           
   spx_mem_t *mem_exc2;          
   spx_mem_t mem_hp[2];          
   spx_word32_t *pi_gain;        
   spx_word16_t *innov_rms_save; 

#ifndef DISABLE_VBR
   VBRState *vbr;                
   float  vbr_quality;           
   float  relative_quality;      
   spx_int32_t vbr_enabled;      
   spx_int32_t vbr_max;          
   int    vad_enabled;           
   int    dtx_enabled;           
   int    dtx_count;             
   spx_int32_t abr_enabled;      
   float  abr_drift;
   float  abr_drift2;
   float  abr_count;
#endif 
   
   int    complexity;            
   spx_int32_t sampling_rate;
   int    plc_tuning;
   int    encode_submode;
   const SpeexSubmode * const *submodes; 
   int    submodeID;             
   int    submodeSelect;         
   int    isWideband;            
   int    highpass_enabled;        
} EncState;

typedef struct DecState {
   const SpeexMode *mode;       
   int    first;                
   int    count_lost;           
   int    frameSize;            
   int    subframeSize;         
   int    nbSubframes;          
   int    lpcSize;              
   int    min_pitch;            
   int    max_pitch;            
   spx_int32_t sampling_rate;

   spx_word16_t  last_ol_gain;  

   char  *stack;                
   spx_word16_t *excBuf;        
   spx_word16_t *exc;           
   spx_lsp_t *old_qlsp;         
   spx_coef_t *interp_qlpc;     
   spx_mem_t *mem_sp;           
   spx_mem_t mem_hp[2];         
   spx_word32_t *pi_gain;       
   spx_word16_t *innov_save;    
   
   spx_word16_t level;
   spx_word16_t max_level;
   spx_word16_t min_level;
   
   
   int    last_pitch;           
   spx_word16_t  last_pitch_gain; 
   spx_word16_t  pitch_gain_buf[3]; 
   int    pitch_gain_buf_idx;   
   spx_int32_t seed;            
   
   int    encode_submode;
   const SpeexSubmode * const *submodes; 
   int    submodeID;            
   int    lpc_enh_enabled;      
   SpeexCallback speex_callbacks[SPEEX_MAX_CALLBACKS];

   SpeexCallback user_callback;

   
   spx_word16_t  voc_m1;
   spx_word32_t  voc_m2;
   spx_word16_t  voc_mean;
   int    voc_offset;

   int    dtx_enabled;
   int    isWideband;            
   int    highpass_enabled;        
} DecState;

void *nb_encoder_init(const SpeexMode *m);

void nb_encoder_destroy(void *state);

int nb_encode(void *state, void *in, SpeexBits *bits);


void *nb_decoder_init(const SpeexMode *m);

void nb_decoder_destroy(void *state);

int nb_decode(void *state, SpeexBits *bits, void *out);

int nb_encoder_ctl(void *state, int request, void *ptr);

int nb_decoder_ctl(void *state, int request, void *ptr);


#endif

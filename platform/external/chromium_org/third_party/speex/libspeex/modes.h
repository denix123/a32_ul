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

#ifndef MODES_H
#define MODES_H

#include <speex/speex.h>
#include <speex/speex_bits.h>
#include "arch.h"

#define NB_SUBMODES 16
#define NB_SUBMODE_BITS 4

#define SB_SUBMODES 8
#define SB_SUBMODE_BITS 3

#define SPEEX_GET_PI_GAIN 100
#define SPEEX_GET_EXC     101
#define SPEEX_GET_INNOV   102
#define SPEEX_GET_DTX_STATUS   103
#define SPEEX_SET_INNOVATION_SAVE   104
#define SPEEX_SET_WIDEBAND   105

#define SPEEX_GET_STACK   106


typedef void (*lsp_quant_func)(spx_lsp_t *, spx_lsp_t *, int, SpeexBits *);

typedef void (*lsp_unquant_func)(spx_lsp_t *, int, SpeexBits *);


typedef int (*ltp_quant_func)(spx_word16_t *, spx_word16_t *, spx_coef_t *, spx_coef_t *, 
                              spx_coef_t *, spx_sig_t *, const void *, int, int, spx_word16_t, 
                              int, int, SpeexBits*, char *, spx_word16_t *, spx_word16_t *, int, int, int, spx_word32_t *);

typedef void (*ltp_unquant_func)(spx_word16_t *, spx_word32_t *, int, int, spx_word16_t, const void *, int, int *,
                                 spx_word16_t *, SpeexBits*, char*, int, int, spx_word16_t, int);


typedef void (*innovation_quant_func)(spx_word16_t *, spx_coef_t *, spx_coef_t *, spx_coef_t *, const void *, int, int, 
                                      spx_sig_t *, spx_word16_t *, SpeexBits *, char *, int, int);

typedef void (*innovation_unquant_func)(spx_sig_t *, const void *, int, SpeexBits*, char *, spx_int32_t *);

typedef struct SpeexSubmode {
   int     lbr_pitch;          
   int     forced_pitch_gain;  
   int     have_subframe_gain; 
   int     double_codebook;    
   
   lsp_quant_func    lsp_quant; 
   lsp_unquant_func  lsp_unquant; 

   
   ltp_quant_func    ltp_quant; 
   ltp_unquant_func  ltp_unquant; 
   const void       *ltp_params; 

   
   innovation_quant_func innovation_quant; 
   innovation_unquant_func innovation_unquant; 
   const void             *innovation_params; 

   spx_word16_t      comb_gain;  

   int               bits_per_frame; 
} SpeexSubmode;

typedef struct SpeexNBMode {
   int     frameSize;      
   int     subframeSize;   
   int     lpcSize;        
   int     pitchStart;     
   int     pitchEnd;       

   spx_word16_t gamma1;    
   spx_word16_t gamma2;    
   spx_word16_t   lpc_floor;      

   const SpeexSubmode *submodes[NB_SUBMODES]; 
   int     defaultSubmode; 
   int     quality_map[11]; 
} SpeexNBMode;


typedef struct SpeexSBMode {
   const SpeexMode *nb_mode;    
   int     frameSize;     
   int     subframeSize;  
   int     lpcSize;       
   spx_word16_t gamma1;   
   spx_word16_t gamma2;   
   spx_word16_t   lpc_floor;     
   spx_word16_t   folding_gain;

   const SpeexSubmode *submodes[SB_SUBMODES]; 
   int     defaultSubmode; 
   int     low_quality_map[11]; 
   int     quality_map[11]; 
#ifndef DISABLE_VBR
   const float (*vbr_thresh)[11];
#endif
   int     nb_modes;
} SpeexSBMode;

int speex_encode_native(void *state, spx_word16_t *in, SpeexBits *bits);
int speex_decode_native(void *state, SpeexBits *bits, spx_word16_t *out);

int nb_mode_query(const void *mode, int request, void *ptr);
int wb_mode_query(const void *mode, int request, void *ptr);

#endif

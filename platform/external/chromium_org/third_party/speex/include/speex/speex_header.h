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


#ifndef SPEEX_HEADER_H
#define SPEEX_HEADER_H

#include "speex/speex_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct SpeexMode;

#define SPEEX_HEADER_STRING_LENGTH 8

#define SPEEX_HEADER_VERSION_LENGTH 20

typedef struct SpeexHeader {
   char speex_string[SPEEX_HEADER_STRING_LENGTH];   
   char speex_version[SPEEX_HEADER_VERSION_LENGTH];  
   spx_int32_t speex_version_id;       
   spx_int32_t header_size;            
   spx_int32_t rate;                   
   spx_int32_t mode;                   
   spx_int32_t mode_bitstream_version; 
   spx_int32_t nb_channels;            
   spx_int32_t bitrate;                
   spx_int32_t frame_size;             
   spx_int32_t vbr;                    
   spx_int32_t frames_per_packet;      
   spx_int32_t extra_headers;          
   spx_int32_t reserved1;              
   spx_int32_t reserved2;              
} SpeexHeader;

void speex_init_header(SpeexHeader *header, int rate, int nb_channels, const struct SpeexMode *m);

char *speex_header_to_packet(SpeexHeader *header, int *size);

SpeexHeader *speex_packet_to_header(char *packet, int size);

void speex_header_free(void *ptr);

#ifdef __cplusplus
}
#endif

#endif

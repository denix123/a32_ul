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

#ifndef BITS_H
#define BITS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpeexBits {
   char *chars;   
   int   nbBits;  
   int   charPtr; 
   int   bitPtr;  
   int   owner;   
   int   overflow;
   int   buf_size;
   int   reserved1; 
   void *reserved2; 
} SpeexBits;

void speex_bits_init(SpeexBits *bits);

void speex_bits_init_buffer(SpeexBits *bits, void *buff, int buf_size);

void speex_bits_set_bit_buffer(SpeexBits *bits, void *buff, int buf_size);

void speex_bits_destroy(SpeexBits *bits);

void speex_bits_reset(SpeexBits *bits);

void speex_bits_rewind(SpeexBits *bits);

void speex_bits_read_from(SpeexBits *bits, char *bytes, int len);

void speex_bits_read_whole_bytes(SpeexBits *bits, char *bytes, int len);

/** Write the content of a bit-stream to an area of memory
 * 
 * @param bits Bit-stream to operate on
 * @param bytes Memory location where to write the bits
 * @param max_len Maximum number of bytes to write (i.e. size of the "bytes" buffer)
 * @return Number of bytes written to the "bytes" buffer
*/
int speex_bits_write(SpeexBits *bits, char *bytes, int max_len);

/** Like speex_bits_write, but writes only the complete bytes in the stream. Also removes the written bytes from the stream */
int speex_bits_write_whole_bytes(SpeexBits *bits, char *bytes, int max_len);

void speex_bits_pack(SpeexBits *bits, int data, int nbBits);

int speex_bits_unpack_signed(SpeexBits *bits, int nbBits);

unsigned int speex_bits_unpack_unsigned(SpeexBits *bits, int nbBits);

int speex_bits_nbytes(SpeexBits *bits);

unsigned int speex_bits_peek_unsigned(SpeexBits *bits, int nbBits);

int speex_bits_peek(SpeexBits *bits);

void speex_bits_advance(SpeexBits *bits, int n);

int speex_bits_remaining(SpeexBits *bits);

void speex_bits_insert_terminator(SpeexBits *bits);

#ifdef __cplusplus
}
#endif

#endif

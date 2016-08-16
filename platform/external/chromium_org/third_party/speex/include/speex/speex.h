/* Copyright (C) 2002-2006 Jean-Marc Valin*/
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

#ifndef SPEEX_H
#define SPEEX_H

#include "speex/speex_bits.h"
#include "speex/speex_types.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SPEEX_SET_ENH 0
#define SPEEX_GET_ENH 1

#define SPEEX_GET_FRAME_SIZE 3

#define SPEEX_SET_QUALITY 4

#define SPEEX_SET_MODE 6
#define SPEEX_GET_MODE 7

#define SPEEX_SET_LOW_MODE 8
#define SPEEX_GET_LOW_MODE 9

#define SPEEX_SET_HIGH_MODE 10
#define SPEEX_GET_HIGH_MODE 11

#define SPEEX_SET_VBR 12
#define SPEEX_GET_VBR 13

#define SPEEX_SET_VBR_QUALITY 14
#define SPEEX_GET_VBR_QUALITY 15

#define SPEEX_SET_COMPLEXITY 16
#define SPEEX_GET_COMPLEXITY 17

#define SPEEX_SET_BITRATE 18
#define SPEEX_GET_BITRATE 19

#define SPEEX_SET_HANDLER 20

#define SPEEX_SET_USER_HANDLER 22

#define SPEEX_SET_SAMPLING_RATE 24
#define SPEEX_GET_SAMPLING_RATE 25

#define SPEEX_RESET_STATE 26

#define SPEEX_GET_RELATIVE_QUALITY 29

#define SPEEX_SET_VAD 30

#define SPEEX_GET_VAD 31

#define SPEEX_SET_ABR 32
#define SPEEX_GET_ABR 33

#define SPEEX_SET_DTX 34
#define SPEEX_GET_DTX 35

#define SPEEX_SET_SUBMODE_ENCODING 36
#define SPEEX_GET_SUBMODE_ENCODING 37

#define SPEEX_GET_LOOKAHEAD 39

#define SPEEX_SET_PLC_TUNING 40
#define SPEEX_GET_PLC_TUNING 41

#define SPEEX_SET_VBR_MAX_BITRATE 42
#define SPEEX_GET_VBR_MAX_BITRATE 43

#define SPEEX_SET_HIGHPASS 44
#define SPEEX_GET_HIGHPASS 45

#define SPEEX_GET_ACTIVITY 47


#define SPEEX_SET_PF 0
#define SPEEX_GET_PF 1




#define SPEEX_MODE_FRAME_SIZE 0

#define SPEEX_SUBMODE_BITS_PER_FRAME 1



#define SPEEX_LIB_GET_MAJOR_VERSION 1
#define SPEEX_LIB_GET_MINOR_VERSION 3
#define SPEEX_LIB_GET_MICRO_VERSION 5
#define SPEEX_LIB_GET_EXTRA_VERSION 7
#define SPEEX_LIB_GET_VERSION_STRING 9


#define SPEEX_NB_MODES 3

#define SPEEX_MODEID_NB 0

#define SPEEX_MODEID_WB 1

#define SPEEX_MODEID_UWB 2

struct SpeexMode;



typedef void *(*encoder_init_func)(const struct SpeexMode *mode);

typedef void (*encoder_destroy_func)(void *st);

typedef int (*encode_func)(void *state, void *in, SpeexBits *bits);

typedef int (*encoder_ctl_func)(void *state, int request, void *ptr);

typedef void *(*decoder_init_func)(const struct SpeexMode *mode);

typedef void (*decoder_destroy_func)(void *st);

typedef int  (*decode_func)(void *state, SpeexBits *bits, void *out);

typedef int (*decoder_ctl_func)(void *state, int request, void *ptr);


typedef int (*mode_query_func)(const void *mode, int request, void *ptr);

 
typedef struct SpeexMode {
   
   const void *mode;

   
   mode_query_func query;
   
   
   const char *modeName;

   
   int modeID;

   int bitstream_version;

   
   encoder_init_func enc_init;

   
   encoder_destroy_func enc_destroy;

   
   encode_func enc;

   
   decoder_init_func dec_init;

   
   decoder_destroy_func dec_destroy;

   
   decode_func dec;

   
   encoder_ctl_func enc_ctl;

   
   decoder_ctl_func dec_ctl;

} SpeexMode;

void *speex_encoder_init(const SpeexMode *mode);

void speex_encoder_destroy(void *state);

/** Uses an existing encoder state to encode one frame of speech pointed to by
    "in". The encoded bit-stream is saved in "bits".
 @param state Encoder state
 @param in Frame that will be encoded with a +-2^15 range. This data MAY be 
        overwritten by the encoder and should be considered uninitialised 
        after the call.
 @param bits Bit-stream where the data will be written
 @return 0 if frame needs not be transmitted (DTX only), 1 otherwise
 */
int speex_encode(void *state, float *in, SpeexBits *bits);

/** Uses an existing encoder state to encode one frame of speech pointed to by
    "in". The encoded bit-stream is saved in "bits".
 @param state Encoder state
 @param in Frame that will be encoded with a +-2^15 range
 @param bits Bit-stream where the data will be written
 @return 0 if frame needs not be transmitted (DTX only), 1 otherwise
 */
int speex_encode_int(void *state, spx_int16_t *in, SpeexBits *bits);

int speex_encoder_ctl(void *state, int request, void *ptr);


 
void *speex_decoder_init(const SpeexMode *mode);

void speex_decoder_destroy(void *state);

/** Uses an existing decoder state to decode one frame of speech from
 * bit-stream bits. The output speech is saved written to out.
 *
 * @param state Decoder state
 * @param bits Bit-stream from which to decode the frame (NULL if the packet was lost)
 * @param out Where to write the decoded frame
 * @return return status (0 for no error, -1 for end of stream, -2 corrupt stream)
 */
int speex_decode(void *state, SpeexBits *bits, float *out);

/** Uses an existing decoder state to decode one frame of speech from
 * bit-stream bits. The output speech is saved written to out.
 *
 * @param state Decoder state
 * @param bits Bit-stream from which to decode the frame (NULL if the packet was lost)
 * @param out Where to write the decoded frame
 * @return return status (0 for no error, -1 for end of stream, -2 corrupt stream)
 */
int speex_decode_int(void *state, SpeexBits *bits, spx_int16_t *out);

int speex_decoder_ctl(void *state, int request, void *ptr);


int speex_mode_query(const SpeexMode *mode, int request, void *ptr);

int speex_lib_ctl(int request, void *ptr);

extern const SpeexMode speex_nb_mode;

extern const SpeexMode speex_wb_mode;

extern const SpeexMode speex_uwb_mode;

extern const SpeexMode * const speex_mode_list[SPEEX_NB_MODES];

const SpeexMode * speex_lib_get_mode (int mode);

#ifndef WIN32
#define speex_lib_get_mode(mode) ((mode)==SPEEX_MODEID_NB ? &speex_nb_mode : speex_lib_get_mode (mode))
#endif

#ifdef __cplusplus
}
#endif

#endif

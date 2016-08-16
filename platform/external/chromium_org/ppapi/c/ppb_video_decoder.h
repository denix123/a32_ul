/* Copyright (c) 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_VIDEO_DECODER_H_
#define PPAPI_C_PPB_VIDEO_DECODER_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_codecs.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_VIDEODECODER_INTERFACE_0_1 "PPB_VideoDecoder;0.1"
#define PPB_VIDEODECODER_INTERFACE_0_2 "PPB_VideoDecoder;0.2"
#define PPB_VIDEODECODER_INTERFACE PPB_VIDEODECODER_INTERFACE_0_2



struct PPB_VideoDecoder_0_2 {
  PP_Resource (*Create)(PP_Instance instance);
  PP_Bool (*IsVideoDecoder)(PP_Resource resource);
  int32_t (*Initialize)(PP_Resource video_decoder,
                        PP_Resource graphics3d_context,
                        PP_VideoProfile profile,
                        PP_HardwareAcceleration acceleration,
                        struct PP_CompletionCallback callback);
  int32_t (*Decode)(PP_Resource video_decoder,
                    uint32_t decode_id,
                    uint32_t size,
                    const void* buffer,
                    struct PP_CompletionCallback callback);
  int32_t (*GetPicture)(PP_Resource video_decoder,
                        struct PP_VideoPicture* picture,
                        struct PP_CompletionCallback callback);
  void (*RecyclePicture)(PP_Resource video_decoder,
                         const struct PP_VideoPicture* picture);
  int32_t (*Flush)(PP_Resource video_decoder,
                   struct PP_CompletionCallback callback);
  int32_t (*Reset)(PP_Resource video_decoder,
                   struct PP_CompletionCallback callback);
};

typedef struct PPB_VideoDecoder_0_2 PPB_VideoDecoder;

struct PPB_VideoDecoder_0_1 {
  PP_Resource (*Create)(PP_Instance instance);
  PP_Bool (*IsVideoDecoder)(PP_Resource resource);
  int32_t (*Initialize)(PP_Resource video_decoder,
                        PP_Resource graphics3d_context,
                        PP_VideoProfile profile,
                        PP_Bool allow_software_fallback,
                        struct PP_CompletionCallback callback);
  int32_t (*Decode)(PP_Resource video_decoder,
                    uint32_t decode_id,
                    uint32_t size,
                    const void* buffer,
                    struct PP_CompletionCallback callback);
  int32_t (*GetPicture)(PP_Resource video_decoder,
                        struct PP_VideoPicture* picture,
                        struct PP_CompletionCallback callback);
  void (*RecyclePicture)(PP_Resource video_decoder,
                         const struct PP_VideoPicture* picture);
  int32_t (*Flush)(PP_Resource video_decoder,
                   struct PP_CompletionCallback callback);
  int32_t (*Reset)(PP_Resource video_decoder,
                   struct PP_CompletionCallback callback);
};

#endif  


/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_VIDEO_FRAME_H_
#define PPAPI_C_PPB_VIDEO_FRAME_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_time.h"

#define PPB_VIDEOFRAME_INTERFACE_0_1 "PPB_VideoFrame;0.1"
#define PPB_VIDEOFRAME_INTERFACE PPB_VIDEOFRAME_INTERFACE_0_1



typedef enum {
  PP_VIDEOFRAME_FORMAT_UNKNOWN = 0,
  PP_VIDEOFRAME_FORMAT_YV12 = 1,
  PP_VIDEOFRAME_FORMAT_I420 = 2,
  PP_VIDEOFRAME_FORMAT_BGRA = 3,
  PP_VIDEOFRAME_FORMAT_LAST = PP_VIDEOFRAME_FORMAT_BGRA
} PP_VideoFrame_Format;

struct PPB_VideoFrame_0_1 {
  PP_Bool (*IsVideoFrame)(PP_Resource resource);
  PP_TimeDelta (*GetTimestamp)(PP_Resource frame);
  void (*SetTimestamp)(PP_Resource frame, PP_TimeDelta timestamp);
  PP_VideoFrame_Format (*GetFormat)(PP_Resource frame);
  PP_Bool (*GetSize)(PP_Resource frame, struct PP_Size* size);
  void* (*GetDataBuffer)(PP_Resource frame);
  uint32_t (*GetDataBufferSize)(PP_Resource frame);
};

typedef struct PPB_VideoFrame_0_1 PPB_VideoFrame;

#endif  


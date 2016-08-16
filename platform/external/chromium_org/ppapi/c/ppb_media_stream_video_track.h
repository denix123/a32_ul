/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_MEDIA_STREAM_VIDEO_TRACK_H_
#define PPAPI_C_PPB_MEDIA_STREAM_VIDEO_TRACK_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

#define PPB_MEDIASTREAMVIDEOTRACK_INTERFACE_0_1 "PPB_MediaStreamVideoTrack;0.1"
#define PPB_MEDIASTREAMVIDEOTRACK_INTERFACE_1_0 \
    "PPB_MediaStreamVideoTrack;1.0" 
#define PPB_MEDIASTREAMVIDEOTRACK_INTERFACE \
    PPB_MEDIASTREAMVIDEOTRACK_INTERFACE_0_1



typedef enum {
  PP_MEDIASTREAMVIDEOTRACK_ATTRIB_NONE = 0,
  PP_MEDIASTREAMVIDEOTRACK_ATTRIB_BUFFERED_FRAMES = 1,
  PP_MEDIASTREAMVIDEOTRACK_ATTRIB_WIDTH = 2,
  PP_MEDIASTREAMVIDEOTRACK_ATTRIB_HEIGHT = 3,
  PP_MEDIASTREAMVIDEOTRACK_ATTRIB_FORMAT = 4
} PP_MediaStreamVideoTrack_Attrib;

struct PPB_MediaStreamVideoTrack_1_0 { 
  PP_Resource (*Create)(PP_Instance instance);
  PP_Bool (*IsMediaStreamVideoTrack)(PP_Resource resource);
  int32_t (*Configure)(PP_Resource video_track,
                       const int32_t attrib_list[],
                       struct PP_CompletionCallback callback);
  int32_t (*GetAttrib)(PP_Resource video_track,
                       PP_MediaStreamVideoTrack_Attrib attrib,
                       int32_t* value);
  struct PP_Var (*GetId)(PP_Resource video_track);
  PP_Bool (*HasEnded)(PP_Resource video_track);
  int32_t (*GetFrame)(PP_Resource video_track,
                      PP_Resource* frame,
                      struct PP_CompletionCallback callback);
  int32_t (*RecycleFrame)(PP_Resource video_track, PP_Resource frame);
  void (*Close)(PP_Resource video_track);
  int32_t (*GetEmptyFrame)(PP_Resource video_track,
                           PP_Resource* frame,
                           struct PP_CompletionCallback callback);
  int32_t (*PutFrame)(PP_Resource video_track, PP_Resource frame);
};

struct PPB_MediaStreamVideoTrack_0_1 {
  PP_Bool (*IsMediaStreamVideoTrack)(PP_Resource resource);
  int32_t (*Configure)(PP_Resource video_track,
                       const int32_t attrib_list[],
                       struct PP_CompletionCallback callback);
  int32_t (*GetAttrib)(PP_Resource video_track,
                       PP_MediaStreamVideoTrack_Attrib attrib,
                       int32_t* value);
  struct PP_Var (*GetId)(PP_Resource video_track);
  PP_Bool (*HasEnded)(PP_Resource video_track);
  int32_t (*GetFrame)(PP_Resource video_track,
                      PP_Resource* frame,
                      struct PP_CompletionCallback callback);
  int32_t (*RecycleFrame)(PP_Resource video_track, PP_Resource frame);
  void (*Close)(PP_Resource video_track);
};

typedef struct PPB_MediaStreamVideoTrack_0_1 PPB_MediaStreamVideoTrack;

#endif  


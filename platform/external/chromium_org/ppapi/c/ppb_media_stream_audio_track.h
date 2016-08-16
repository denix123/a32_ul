/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_MEDIA_STREAM_AUDIO_TRACK_H_
#define PPAPI_C_PPB_MEDIA_STREAM_AUDIO_TRACK_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

#define PPB_MEDIASTREAMAUDIOTRACK_INTERFACE_0_1 "PPB_MediaStreamAudioTrack;0.1"
#define PPB_MEDIASTREAMAUDIOTRACK_INTERFACE \
    PPB_MEDIASTREAMAUDIOTRACK_INTERFACE_0_1



typedef enum {
  PP_MEDIASTREAMAUDIOTRACK_ATTRIB_NONE = 0,
  PP_MEDIASTREAMAUDIOTRACK_ATTRIB_BUFFERS = 1,
  PP_MEDIASTREAMAUDIOTRACK_ATTRIB_SAMPLE_RATE = 2,
  PP_MEDIASTREAMAUDIOTRACK_ATTRIB_SAMPLE_SIZE = 3,
  PP_MEDIASTREAMAUDIOTRACK_ATTRIB_CHANNELS = 4,
  PP_MEDIASTREAMAUDIOTRACK_ATTRIB_DURATION = 5
} PP_MediaStreamAudioTrack_Attrib;

struct PPB_MediaStreamAudioTrack_0_1 {
  PP_Bool (*IsMediaStreamAudioTrack)(PP_Resource resource);
  int32_t (*Configure)(PP_Resource audio_track,
                       const int32_t attrib_list[],
                       struct PP_CompletionCallback callback);
  int32_t (*GetAttrib)(PP_Resource audio_track,
                       PP_MediaStreamAudioTrack_Attrib attrib,
                       int32_t* value);
  struct PP_Var (*GetId)(PP_Resource audio_track);
  PP_Bool (*HasEnded)(PP_Resource audio_track);
  int32_t (*GetBuffer)(PP_Resource audio_track,
                       PP_Resource* buffer,
                       struct PP_CompletionCallback callback);
  int32_t (*RecycleBuffer)(PP_Resource audio_track, PP_Resource buffer);
  void (*Close)(PP_Resource audio_track);
};

typedef struct PPB_MediaStreamAudioTrack_0_1 PPB_MediaStreamAudioTrack;

#endif  


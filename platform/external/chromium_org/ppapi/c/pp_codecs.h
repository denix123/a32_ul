/* Copyright (c) 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PP_CODECS_H_
#define PPAPI_C_PP_CODECS_H_

#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"



typedef enum {
  PP_VIDEOPROFILE_H264BASELINE = 0,
  PP_VIDEOPROFILE_H264MAIN = 1,
  PP_VIDEOPROFILE_H264EXTENDED = 2,
  PP_VIDEOPROFILE_H264HIGH = 3,
  PP_VIDEOPROFILE_H264HIGH10PROFILE = 4,
  PP_VIDEOPROFILE_H264HIGH422PROFILE = 5,
  PP_VIDEOPROFILE_H264HIGH444PREDICTIVEPROFILE = 6,
  PP_VIDEOPROFILE_H264SCALABLEBASELINE = 7,
  PP_VIDEOPROFILE_H264SCALABLEHIGH = 8,
  PP_VIDEOPROFILE_H264STEREOHIGH = 9,
  PP_VIDEOPROFILE_H264MULTIVIEWHIGH = 10,
  PP_VIDEOPROFILE_VP8_ANY = 11,
  PP_VIDEOPROFILE_VP9_ANY = 12,
  PP_VIDEOPROFILE_MAX = PP_VIDEOPROFILE_VP9_ANY
} PP_VideoProfile;

typedef enum {
  
  PP_HARDWAREACCELERATION_ONLY = 0,
  PP_HARDWAREACCELERATION_WITHFALLBACK = 1,
  
  PP_HARDWAREACCELERATION_NONE = 2,
  PP_HARDWAREACCELERATION_LAST = PP_HARDWAREACCELERATION_NONE
} PP_HardwareAcceleration;

struct PP_VideoPicture {
  uint32_t decode_id;
  uint32_t texture_id;
  uint32_t texture_target;
  struct PP_Size texture_size;
};

#endif  


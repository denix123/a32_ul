/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPP_PEXE_STREAM_HANDLER_H_
#define PPAPI_C_PRIVATE_PPP_PEXE_STREAM_HANDLER_H_

#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_stdint.h"

#define PPP_PEXESTREAMHANDLER_INTERFACE_1_0 "PPP_PexeStreamHandler;1.0"
#define PPP_PEXESTREAMHANDLER_INTERFACE PPP_PEXESTREAMHANDLER_INTERFACE_1_0



#include "ppapi/c/private/pp_file_handle.h"

struct PPP_PexeStreamHandler_1_0 {
  void (*DidCacheHit)(void* user_data, PP_FileHandle nexe_file_handle);
  void (*DidCacheMiss)(void* user_data,
                       int64_t expected_total_length,
                       PP_FileHandle temp_nexe_file);
  void (*DidStreamData)(void* user_data, const void* data, int32_t length);
  void (*DidFinishStream)(void* user_data, int32_t pp_error);
};

typedef struct PPP_PexeStreamHandler_1_0 PPP_PexeStreamHandler;

#endif  


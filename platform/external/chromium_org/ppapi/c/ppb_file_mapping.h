/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_FILE_MAPPING_H_
#define PPAPI_C_PPB_FILE_MAPPING_H_

#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_FILEMAPPING_INTERFACE_0_1 "PPB_FileMapping;0.1" 


typedef enum {
  
  PP_FILEMAPPROTECTION_READ = 1u << 0,
  
  PP_FILEMAPPROTECTION_WRITE = 1u << 1
} PP_FileMapProtection;
PP_COMPILE_ASSERT_SIZE_IN_BYTES(PP_FileMapProtection, 4);

typedef enum {
  /**
   * Requests a shared mapping. If this flag is set, changes written to the
   * memory region will be reflected in the underlying file and will thus
   * eventually be visible to other processes which have opened the file. The
   * file may not actually be updated until Unmap() is called. This is only
   * valid if the PPB_FileIO resource was opened with write permission.
   */
  PP_FILEMAPFLAG_SHARED = 1u << 0,
  /**
   * Requests a copy-on-write mapping. If this flag is set, changes are not
   * written to the underlying file, but only in the memory of the process
   * (copy-on-write).
   */
  PP_FILEMAPFLAG_PRIVATE = 1u << 1,
  PP_FILEMAPFLAG_FIXED = 1u << 2
} PP_FileMapFlags;
PP_COMPILE_ASSERT_SIZE_IN_BYTES(PP_FileMapFlags, 4);

struct PPB_FileMapping_0_1 { 
  int32_t (*Map)(PP_Instance instance,
                 PP_Resource file_io,
                 int64_t length,
                 uint32_t map_protection,
                 uint32_t map_flags,
                 int64_t offset,
                 void** address,
                 struct PP_CompletionCallback callback);
  int32_t (*Unmap)(PP_Instance instance,
                   const void* address,
                   int64_t length,
                   struct PP_CompletionCallback callback);
  int64_t (*GetMapPageSize)(PP_Instance instance);
};

#endif  


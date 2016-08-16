// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MOJO_PUBLIC_C_SYSTEM_BUFFER_H_
#define MOJO_PUBLIC_C_SYSTEM_BUFFER_H_

#include "mojo/public/c/system/macros.h"
#include "mojo/public/c/system/system_export.h"
#include "mojo/public/c/system/types.h"


typedef uint32_t MojoCreateSharedBufferOptionsFlags;

#ifdef __cplusplus
const MojoCreateSharedBufferOptionsFlags
    MOJO_CREATE_SHARED_BUFFER_OPTIONS_FLAG_NONE = 0;
#else
#define MOJO_CREATE_SHARED_BUFFER_OPTIONS_FLAG_NONE \
  ((MojoCreateSharedBufferOptionsFlags)0)
#endif

MOJO_COMPILE_ASSERT(MOJO_ALIGNOF(int64_t) == 8, int64_t_has_weird_alignment);
struct MOJO_ALIGNAS(8) MojoCreateSharedBufferOptions {
  uint32_t struct_size;
  MojoCreateSharedBufferOptionsFlags flags;
};
MOJO_COMPILE_ASSERT(sizeof(MojoCreateSharedBufferOptions) == 8,
                    MojoCreateSharedBufferOptions_has_wrong_size);


typedef uint32_t MojoDuplicateBufferHandleOptionsFlags;

#ifdef __cplusplus
const MojoDuplicateBufferHandleOptionsFlags
    MOJO_DUPLICATE_BUFFER_HANDLE_OPTIONS_FLAG_NONE = 0;
#else
#define MOJO_DUPLICATE_BUFFER_HANDLE_OPTIONS_FLAG_NONE \
  ((MojoDuplicateBufferHandleOptionsFlags)0)
#endif

struct MojoDuplicateBufferHandleOptions {
  uint32_t struct_size;
  MojoDuplicateBufferHandleOptionsFlags flags;
};
MOJO_COMPILE_ASSERT(sizeof(MojoDuplicateBufferHandleOptions) == 8,
                    MojoDuplicateBufferHandleOptions_has_wrong_size);


typedef uint32_t MojoMapBufferFlags;

#ifdef __cplusplus
const MojoMapBufferFlags MOJO_MAP_BUFFER_FLAG_NONE = 0;
#else
#define MOJO_MAP_BUFFER_FLAG_NONE ((MojoMapBufferFlags)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif


MOJO_SYSTEM_EXPORT MojoResult MojoCreateSharedBuffer(
    const struct MojoCreateSharedBufferOptions* options,  
    uint64_t num_bytes,                                   
    MojoHandle* shared_buffer_handle);                    

MOJO_SYSTEM_EXPORT MojoResult MojoDuplicateBufferHandle(
    MojoHandle buffer_handle,
    const struct MojoDuplicateBufferHandleOptions* options,  
    MojoHandle* new_buffer_handle);                          

MOJO_SYSTEM_EXPORT MojoResult MojoMapBuffer(MojoHandle buffer_handle,
                                            uint64_t offset,
                                            uint64_t num_bytes,
                                            void** buffer,  
                                            MojoMapBufferFlags flags);

MOJO_SYSTEM_EXPORT MojoResult MojoUnmapBuffer(void* buffer);  

#ifdef __cplusplus
}  
#endif

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MOJO_PUBLIC_C_SYSTEM_MESSAGE_PIPE_H_
#define MOJO_PUBLIC_C_SYSTEM_MESSAGE_PIPE_H_

#include "mojo/public/c/system/macros.h"
#include "mojo/public/c/system/system_export.h"
#include "mojo/public/c/system/types.h"


typedef uint32_t MojoCreateMessagePipeOptionsFlags;

#ifdef __cplusplus
const MojoCreateMessagePipeOptionsFlags
    MOJO_CREATE_MESSAGE_PIPE_OPTIONS_FLAG_NONE = 0;
#else
#define MOJO_CREATE_MESSAGE_PIPE_OPTIONS_FLAG_NONE \
  ((MojoCreateMessagePipeOptionsFlags)0)
#endif

MOJO_COMPILE_ASSERT(MOJO_ALIGNOF(int64_t) == 8, int64_t_has_weird_alignment);
struct MOJO_ALIGNAS(8) MojoCreateMessagePipeOptions {
  uint32_t struct_size;
  MojoCreateMessagePipeOptionsFlags flags;
};
MOJO_COMPILE_ASSERT(sizeof(MojoCreateMessagePipeOptions) == 8,
                    MojoCreateMessagePipeOptions_has_wrong_size);


typedef uint32_t MojoWriteMessageFlags;

#ifdef __cplusplus
const MojoWriteMessageFlags MOJO_WRITE_MESSAGE_FLAG_NONE = 0;
#else
#define MOJO_WRITE_MESSAGE_FLAG_NONE ((MojoWriteMessageFlags)0)
#endif


typedef uint32_t MojoReadMessageFlags;

#ifdef __cplusplus
const MojoReadMessageFlags MOJO_READ_MESSAGE_FLAG_NONE = 0;
const MojoReadMessageFlags MOJO_READ_MESSAGE_FLAG_MAY_DISCARD = 1 << 0;
#else
#define MOJO_READ_MESSAGE_FLAG_NONE ((MojoReadMessageFlags)0)
#define MOJO_READ_MESSAGE_FLAG_MAY_DISCARD ((MojoReadMessageFlags)1 << 0)
#endif

#ifdef __cplusplus
extern "C" {
#endif


MOJO_SYSTEM_EXPORT MojoResult MojoCreateMessagePipe(
    const struct MojoCreateMessagePipeOptions* options,  
    MojoHandle* message_pipe_handle0,                    
    MojoHandle* message_pipe_handle1);                   

MOJO_SYSTEM_EXPORT MojoResult
    MojoWriteMessage(MojoHandle message_pipe_handle,
                     const void* bytes,  
                     uint32_t num_bytes,
                     const MojoHandle* handles,  
                     uint32_t num_handles,
                     MojoWriteMessageFlags flags);

MOJO_SYSTEM_EXPORT MojoResult
    MojoReadMessage(MojoHandle message_pipe_handle,
                    void* bytes,            
                    uint32_t* num_bytes,    
                    MojoHandle* handles,    
                    uint32_t* num_handles,  
                    MojoReadMessageFlags flags);

#ifdef __cplusplus
}  
#endif

#endif  

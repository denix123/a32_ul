// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MOJO_PUBLIC_PLATFORM_NATIVE_SYSTEM_THUNKS_H_
#define MOJO_PUBLIC_PLATFORM_NATIVE_SYSTEM_THUNKS_H_

#include <stddef.h>

#include "mojo/public/c/system/core.h"


#pragma pack(push, 8)
struct MojoSystemThunks {
  size_t size;  
  MojoTimeTicks (*GetTimeTicksNow)();
  MojoResult (*Close)(MojoHandle handle);
  MojoResult (*Wait)(MojoHandle handle,
                     MojoHandleSignals signals,
                     MojoDeadline deadline);
  MojoResult (*WaitMany)(const MojoHandle* handles,
                         const MojoHandleSignals* signals,
                         uint32_t num_handles,
                         MojoDeadline deadline);
  MojoResult (*CreateMessagePipe)(
      const struct MojoCreateMessagePipeOptions* options,
      MojoHandle* message_pipe_handle0,
      MojoHandle* message_pipe_handle1);
  MojoResult (*WriteMessage)(MojoHandle message_pipe_handle,
                             const void* bytes,
                             uint32_t num_bytes,
                             const MojoHandle* handles,
                             uint32_t num_handles,
                             MojoWriteMessageFlags flags);
  MojoResult (*ReadMessage)(MojoHandle message_pipe_handle,
                            void* bytes,
                            uint32_t* num_bytes,
                            MojoHandle* handles,
                            uint32_t* num_handles,
                            MojoReadMessageFlags flags);
  MojoResult (*CreateDataPipe)(const struct MojoCreateDataPipeOptions* options,
                               MojoHandle* data_pipe_producer_handle,
                               MojoHandle* data_pipe_consumer_handle);
  MojoResult (*WriteData)(MojoHandle data_pipe_producer_handle,
                          const void* elements,
                          uint32_t* num_elements,
                          MojoWriteDataFlags flags);
  MojoResult (*BeginWriteData)(MojoHandle data_pipe_producer_handle,
                               void** buffer,
                               uint32_t* buffer_num_elements,
                               MojoWriteDataFlags flags);
  MojoResult (*EndWriteData)(MojoHandle data_pipe_producer_handle,
                             uint32_t num_elements_written);
  MojoResult (*ReadData)(MojoHandle data_pipe_consumer_handle,
                         void* elements,
                         uint32_t* num_elements,
                         MojoReadDataFlags flags);
  MojoResult (*BeginReadData)(MojoHandle data_pipe_consumer_handle,
                              const void** buffer,
                              uint32_t* buffer_num_elements,
                              MojoReadDataFlags flags);
  MojoResult (*EndReadData)(MojoHandle data_pipe_consumer_handle,
                            uint32_t num_elements_read);
  MojoResult (*CreateSharedBuffer)(
      const struct MojoCreateSharedBufferOptions* options,
      uint64_t num_bytes,
      MojoHandle* shared_buffer_handle);
  MojoResult (*DuplicateBufferHandle)(
      MojoHandle buffer_handle,
      const struct MojoDuplicateBufferHandleOptions* options,
      MojoHandle* new_buffer_handle);
  MojoResult (*MapBuffer)(MojoHandle buffer_handle,
                          uint64_t offset,
                          uint64_t num_bytes,
                          void** buffer,
                          MojoMapBufferFlags flags);
  MojoResult (*UnmapBuffer)(void* buffer);
};
#pragma pack(pop)


#ifdef __cplusplus
inline MojoSystemThunks MojoMakeSystemThunks() {
  MojoSystemThunks system_thunks = {
    sizeof(MojoSystemThunks),
    MojoGetTimeTicksNow,
    MojoClose,
    MojoWait,
    MojoWaitMany,
    MojoCreateMessagePipe,
    MojoWriteMessage,
    MojoReadMessage,
    MojoCreateDataPipe,
    MojoWriteData,
    MojoBeginWriteData,
    MojoEndWriteData,
    MojoReadData,
    MojoBeginReadData,
    MojoEndReadData,
    MojoCreateSharedBuffer,
    MojoDuplicateBufferHandle,
    MojoMapBuffer,
    MojoUnmapBuffer
  };
  return system_thunks;
}
#endif


typedef size_t (*MojoSetSystemThunksFn)(
    const struct MojoSystemThunks* system_thunks);

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MOJO_PUBLIC_C_SYSTEM_DATA_PIPE_H_
#define MOJO_PUBLIC_C_SYSTEM_DATA_PIPE_H_

#include "mojo/public/c/system/macros.h"
#include "mojo/public/c/system/system_export.h"
#include "mojo/public/c/system/types.h"


typedef uint32_t MojoCreateDataPipeOptionsFlags;

#ifdef __cplusplus
const MojoCreateDataPipeOptionsFlags MOJO_CREATE_DATA_PIPE_OPTIONS_FLAG_NONE =
    0;
const MojoCreateDataPipeOptionsFlags
    MOJO_CREATE_DATA_PIPE_OPTIONS_FLAG_MAY_DISCARD = 1 << 0;
#else
#define MOJO_CREATE_DATA_PIPE_OPTIONS_FLAG_NONE \
  ((MojoCreateDataPipeOptionsFlags)0)
#define MOJO_CREATE_DATA_PIPE_OPTIONS_FLAG_MAY_DISCARD \
  ((MojoCreateDataPipeOptionsFlags)1 << 0)
#endif

MOJO_COMPILE_ASSERT(MOJO_ALIGNOF(int64_t) == 8, int64_t_has_weird_alignment);
struct MOJO_ALIGNAS(8) MojoCreateDataPipeOptions {
  uint32_t struct_size;
  MojoCreateDataPipeOptionsFlags flags;
  uint32_t element_num_bytes;
  uint32_t capacity_num_bytes;
};
MOJO_COMPILE_ASSERT(sizeof(MojoCreateDataPipeOptions) == 16,
                    MojoCreateDataPipeOptions_has_wrong_size);


typedef uint32_t MojoWriteDataFlags;

#ifdef __cplusplus
const MojoWriteDataFlags MOJO_WRITE_DATA_FLAG_NONE = 0;
const MojoWriteDataFlags MOJO_WRITE_DATA_FLAG_ALL_OR_NONE = 1 << 0;
#else
#define MOJO_WRITE_DATA_FLAG_NONE ((MojoWriteDataFlags)0)
#define MOJO_WRITE_DATA_FLAG_ALL_OR_NONE ((MojoWriteDataFlags)1 << 0)
#endif


typedef uint32_t MojoReadDataFlags;

#ifdef __cplusplus
const MojoReadDataFlags MOJO_READ_DATA_FLAG_NONE = 0;
const MojoReadDataFlags MOJO_READ_DATA_FLAG_ALL_OR_NONE = 1 << 0;
const MojoReadDataFlags MOJO_READ_DATA_FLAG_DISCARD = 1 << 1;
const MojoReadDataFlags MOJO_READ_DATA_FLAG_QUERY = 1 << 2;
#else
#define MOJO_READ_DATA_FLAG_NONE ((MojoReadDataFlags)0)
#define MOJO_READ_DATA_FLAG_ALL_OR_NONE ((MojoReadDataFlags)1 << 0)
#define MOJO_READ_DATA_FLAG_DISCARD ((MojoReadDataFlags)1 << 1)
#define MOJO_READ_DATA_FLAG_QUERY ((MojoReadDataFlags)1 << 2)
#endif

#ifdef __cplusplus
extern "C" {
#endif


MOJO_SYSTEM_EXPORT MojoResult MojoCreateDataPipe(
    const struct MojoCreateDataPipeOptions* options,  
    MojoHandle* data_pipe_producer_handle,            
    MojoHandle* data_pipe_consumer_handle);           

// will be written or none is.
// written.
// data, starting with the earliest written data that has not been consumed.
//       (specified by |*num_bytes|) could not be written.
//   |MOJO_RESULT_SHOULD_WAIT| if no data can currently be written (and the
// TODO(vtl): Should there be a way of querying how much data can be written?
MOJO_SYSTEM_EXPORT MojoResult
    MojoWriteData(MojoHandle data_pipe_producer_handle,
                  const void* elements,
                  uint32_t* num_bytes,  
                  MojoWriteDataFlags flags);

// |MojoEndWriteData()| to specify the amount written and to complete the
//       (specified by |*buffer_num_bytes|) cannot be written contiguously at
//   |MOJO_RESULT_SHOULD_WAIT| if no data can currently be written (and the
MOJO_SYSTEM_EXPORT MojoResult
    MojoBeginWriteData(MojoHandle data_pipe_producer_handle,
                       void** buffer,               
                       uint32_t* buffer_num_bytes,  
                       MojoWriteDataFlags flags);

// |MojoBeginWriteData()| on the same handle. |num_bytes_written| should
// indicate the amount of data actually written; it must be less than or equal
// |MojoBeginWriteData()| must have been filled with exactly |num_bytes_written|
// writable again, if there's space available) but no data written to |*buffer|
//       |num_bytes_written| is invalid (greater than the maximum value provided
MOJO_SYSTEM_EXPORT MojoResult
    MojoEndWriteData(MojoHandle data_pipe_producer_handle,
                     uint32_t num_bytes_written);

MOJO_SYSTEM_EXPORT MojoResult MojoReadData(MojoHandle data_pipe_consumer_handle,
                                           void* elements,       
                                           uint32_t* num_bytes,  
                                           MojoReadDataFlags flags);

MOJO_SYSTEM_EXPORT MojoResult
    MojoBeginReadData(MojoHandle data_pipe_consumer_handle,
                      const void** buffer,         
                      uint32_t* buffer_num_bytes,  
                      MojoReadDataFlags flags);

//       |num_bytes_written| is greater than the maximum value provided by
MOJO_SYSTEM_EXPORT MojoResult
    MojoEndReadData(MojoHandle data_pipe_consumer_handle,
                    uint32_t num_bytes_read);

#ifdef __cplusplus
}  
#endif

#endif  

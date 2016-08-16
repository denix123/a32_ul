// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_SYSTEM_DATA_PIPE_H_
#define MOJO_PUBLIC_CPP_SYSTEM_DATA_PIPE_H_

#include <assert.h>

#include "mojo/public/c/system/data_pipe.h"
#include "mojo/public/cpp/system/handle.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {


class DataPipeProducerHandle : public Handle {
 public:
  DataPipeProducerHandle() {}
  explicit DataPipeProducerHandle(MojoHandle value) : Handle(value) {}

  
};

MOJO_COMPILE_ASSERT(sizeof(DataPipeProducerHandle) == sizeof(Handle),
                    bad_size_for_cpp_DataPipeProducerHandle);

typedef ScopedHandleBase<DataPipeProducerHandle> ScopedDataPipeProducerHandle;
MOJO_COMPILE_ASSERT(sizeof(ScopedDataPipeProducerHandle) ==
                        sizeof(DataPipeProducerHandle),
                    bad_size_for_cpp_ScopedDataPipeProducerHandle);

class DataPipeConsumerHandle : public Handle {
 public:
  DataPipeConsumerHandle() {}
  explicit DataPipeConsumerHandle(MojoHandle value) : Handle(value) {}

  
};

MOJO_COMPILE_ASSERT(sizeof(DataPipeConsumerHandle) == sizeof(Handle),
                    bad_size_for_cpp_DataPipeConsumerHandle);

typedef ScopedHandleBase<DataPipeConsumerHandle> ScopedDataPipeConsumerHandle;
MOJO_COMPILE_ASSERT(sizeof(ScopedDataPipeConsumerHandle) ==
                        sizeof(DataPipeConsumerHandle),
                    bad_size_for_cpp_ScopedDataPipeConsumerHandle);

inline MojoResult CreateDataPipe(
    const MojoCreateDataPipeOptions* options,
    ScopedDataPipeProducerHandle* data_pipe_producer,
    ScopedDataPipeConsumerHandle* data_pipe_consumer) {
  assert(data_pipe_producer);
  assert(data_pipe_consumer);
  DataPipeProducerHandle producer_handle;
  DataPipeConsumerHandle consumer_handle;
  MojoResult rv = MojoCreateDataPipe(options, producer_handle.mutable_value(),
                                     consumer_handle.mutable_value());
  
  
  data_pipe_producer->reset(producer_handle);
  data_pipe_consumer->reset(consumer_handle);
  return rv;
}

inline MojoResult WriteDataRaw(DataPipeProducerHandle data_pipe_producer,
                               const void* elements,
                               uint32_t* num_bytes,
                               MojoWriteDataFlags flags) {
  return MojoWriteData(data_pipe_producer.value(), elements, num_bytes, flags);
}

inline MojoResult BeginWriteDataRaw(DataPipeProducerHandle data_pipe_producer,
                                    void** buffer,
                                    uint32_t* buffer_num_bytes,
                                    MojoWriteDataFlags flags) {
  return MojoBeginWriteData(data_pipe_producer.value(), buffer,
                            buffer_num_bytes, flags);
}

inline MojoResult EndWriteDataRaw(DataPipeProducerHandle data_pipe_producer,
                                  uint32_t num_bytes_written) {
  return MojoEndWriteData(data_pipe_producer.value(), num_bytes_written);
}

inline MojoResult ReadDataRaw(DataPipeConsumerHandle data_pipe_consumer,
                              void* elements,
                              uint32_t* num_bytes,
                              MojoReadDataFlags flags) {
  return MojoReadData(data_pipe_consumer.value(), elements, num_bytes, flags);
}

inline MojoResult BeginReadDataRaw(DataPipeConsumerHandle data_pipe_consumer,
                                   const void** buffer,
                                   uint32_t* buffer_num_bytes,
                                   MojoReadDataFlags flags) {
  return MojoBeginReadData(data_pipe_consumer.value(), buffer, buffer_num_bytes,
                           flags);
}

inline MojoResult EndReadDataRaw(DataPipeConsumerHandle data_pipe_consumer,
                                 uint32_t num_bytes_read) {
  return MojoEndReadData(data_pipe_consumer.value(), num_bytes_read);
}

class DataPipe {
 public:
  DataPipe();
  explicit DataPipe(const MojoCreateDataPipeOptions& options);
  ~DataPipe();

  ScopedDataPipeProducerHandle producer_handle;
  ScopedDataPipeConsumerHandle consumer_handle;
};

inline DataPipe::DataPipe() {
  MojoResult result MOJO_ALLOW_UNUSED =
      CreateDataPipe(NULL, &producer_handle, &consumer_handle);
  assert(result == MOJO_RESULT_OK);
}

inline DataPipe::DataPipe(const MojoCreateDataPipeOptions& options) {
  MojoResult result MOJO_ALLOW_UNUSED =
      CreateDataPipe(&options, &producer_handle, &consumer_handle);
  assert(result == MOJO_RESULT_OK);
}

inline DataPipe::~DataPipe() {
}

}  

#endif  

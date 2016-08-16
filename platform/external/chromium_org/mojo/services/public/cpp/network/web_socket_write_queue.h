// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_PUBLIC_CPP_NETWORK_WEB_SOCKET_WRITE_QUEUE_H_
#define MOJO_SERVICES_PUBLIC_CPP_NETWORK_WEB_SOCKET_WRITE_QUEUE_H_

#include "base/callback.h"
#include "base/memory/scoped_vector.h"
#include "mojo/common/handle_watcher.h"
#include "mojo/public/cpp/system/data_pipe.h"

namespace mojo {

class WebSocketWriteQueue {
 public:
  WebSocketWriteQueue(DataPipeProducerHandle handle);
  ~WebSocketWriteQueue();

  void Write(const char* data,
             uint32_t num_bytes,
             base::Callback<void(const char*)> callback);

 private:
  struct Operation;

  MojoResult TryToWrite();
  void Wait();
  void OnHandleReady(MojoResult result);

  DataPipeProducerHandle handle_;
  common::HandleWatcher handle_watcher_;
  ScopedVector<Operation> queue_;
  bool is_waiting_;
};

}  

#endif  

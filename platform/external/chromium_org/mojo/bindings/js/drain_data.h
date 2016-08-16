// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_BINDINGS_JS_DRAIN_DATA_H_
#define MOJO_BINDINGS_JS_DRAIN_DATA_H_

#include "base/memory/scoped_vector.h"
#include "gin/runner.h"
#include "mojo/public/c/environment/async_waiter.h"
#include "mojo/public/cpp/system/core.h"
#include "v8/include/v8.h"

namespace mojo {
namespace js {


class DrainData {
 public:
  
  
  DrainData(v8::Isolate* isolate, mojo::Handle handle);

  
  
  v8::Handle<v8::Value> GetPromise();

 private:
  ~DrainData();

  
  void WaitForData();
  static void WaitCompleted(void* self, MojoResult result) {
    static_cast<DrainData*>(self)->DataReady(result);
  }

  
  
  void DataReady(MojoResult result);
  MojoResult ReadData();

  
  
  void DeliverData(MojoResult result);

  typedef std::vector<char> DataBuffer;

  v8::Isolate* isolate_;
  ScopedDataPipeConsumerHandle handle_;
  MojoAsyncWaitID wait_id_;
  base::WeakPtr<gin::Runner> runner_;
  v8::UniquePersistent<v8::Promise::Resolver> resolver_;
  ScopedVector<DataBuffer> data_buffers_;
};

}  
}  

#endif  

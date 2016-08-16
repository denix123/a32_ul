// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_BINDINGS_JS_WAITING_CALLBACK_H_
#define MOJO_BINDINGS_JS_WAITING_CALLBACK_H_

#include "gin/handle.h"
#include "gin/runner.h"
#include "gin/wrappable.h"
#include "mojo/bindings/js/handle.h"
#include "mojo/bindings/js/handle_close_observer.h"
#include "mojo/public/c/environment/async_waiter.h"
#include "mojo/public/cpp/system/core.h"

namespace mojo {
namespace js {

class WaitingCallback : public gin::Wrappable<WaitingCallback>,
                        public gin::HandleCloseObserver {
 public:
  static gin::WrapperInfo kWrapperInfo;

  
  static gin::Handle<WaitingCallback> Create(
      v8::Isolate* isolate,
      v8::Handle<v8::Function> callback,
      gin::Handle<gin::HandleWrapper> handle_wrapper,
      MojoHandleSignals signals);

  
  
  
  void Cancel();

 private:
  WaitingCallback(v8::Isolate* isolate,
                  v8::Handle<v8::Function> callback,
                  gin::Handle<gin::HandleWrapper> handle_wrapper);
  virtual ~WaitingCallback();

  
  static void CallOnHandleReady(void* closure, MojoResult result);

  
  void OnHandleReady(MojoResult result);

  
  
  virtual void OnWillCloseHandle() OVERRIDE;

  base::WeakPtr<gin::Runner> runner_;
  MojoAsyncWaitID wait_id_;

  gin::HandleWrapper* handle_wrapper_;

  DISALLOW_COPY_AND_ASSIGN(WaitingCallback);
};

}  
}  

#endif  

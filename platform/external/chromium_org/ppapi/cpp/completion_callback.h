// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_COMPLETION_CALLBACK_H_
#define PPAPI_CPP_COMPLETION_CALLBACK_H_

#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_errors.h"
#include "ppapi/cpp/logging.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/output_traits.h"

namespace pp {

class CompletionCallback {
 public:
  
  
  
  
  
  
  
  CompletionCallback() {
    cc_ = PP_BlockUntilComplete();
  }

  
  
  
  
  
  
  CompletionCallback(PP_CompletionCallback_Func func, void* user_data) {
    cc_ = PP_MakeCompletionCallback(func, user_data);
  }

  
  
  
  
  
  
  
  
  
  
  CompletionCallback(PP_CompletionCallback_Func func, void* user_data,
                     int32_t flags) {
    cc_ = PP_MakeCompletionCallback(func, user_data);
    cc_.flags = flags;
  }

  
  
  
  
  
  
  void set_flags(int32_t flags) { cc_.flags = flags; }

  
  
  
  
  
  
  
  
  
  
  
  void Run(int32_t result) {
    PP_DCHECK(cc_.func);
    PP_RunCompletionCallback(&cc_, result);
  }

  
  
  
  
  
  
  
  
  void RunAndClear(int32_t result) {
    PP_DCHECK(cc_.func);
    PP_RunAndClearCompletionCallback(&cc_, result);
  }

  
  
  
  
  
  
  
  
  
  
  
  
  
  bool IsOptional() const {
    return (cc_.func == NULL ||
            (cc_.flags & PP_COMPLETIONCALLBACK_FLAG_OPTIONAL) != 0);
  }

  
  
  
  
  const PP_CompletionCallback& pp_completion_callback() const { return cc_; }

  
  
  
  
  
  int32_t flags() const { return cc_.flags; }

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t MayForce(int32_t result) const {
    if (result == PP_OK_COMPLETIONPENDING || IsOptional())
      return result;
    
    Module::Get()->core()->CallOnMainThread(0, *this, result);
    return PP_OK_COMPLETIONPENDING;
  }

 protected:
  PP_CompletionCallback cc_;
};

template<typename T>
class CompletionCallbackWithOutput : public CompletionCallback {
 public:
  
  
  
  
  
  
  typedef typename internal::CallbackOutputTraits<T>::StorageType
      OutputStorageType;
  typedef typename internal::CallbackOutputTraits<T>::APIArgType
      APIArgType;

  
  
  
  
  
  
  
  
  
  CompletionCallbackWithOutput(OutputStorageType* output)
      : CompletionCallback(),
        output_(output) {
  }

  
  
  
  
  
  
  
  
  
  CompletionCallbackWithOutput(PP_CompletionCallback_Func func,
                               void* user_data,
                               OutputStorageType* output)
      : CompletionCallback(func, user_data),
        output_(output) {
  }

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  CompletionCallbackWithOutput(PP_CompletionCallback_Func func,
                               void* user_data,
                               int32_t flags,
                               OutputStorageType* output)
      : CompletionCallback(func, user_data, flags),
        output_(output) {
  }

  APIArgType output() const {
    return internal::CallbackOutputTraits<T>::StorageToAPIArg(*output_);
  }

 private:
  OutputStorageType* output_;
};

inline CompletionCallback BlockUntilComplete() {
  
  
  return CompletionCallback();
}

}  

#endif  

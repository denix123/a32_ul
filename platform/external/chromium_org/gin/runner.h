// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_RUNNER_H_
#define GIN_RUNNER_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "gin/gin_export.h"
#include "gin/public/context_holder.h"
#include "v8/include/v8.h"

namespace gin {

class GIN_EXPORT Runner {
 public:
  Runner();
  virtual ~Runner();

  
  
  virtual void Run(const std::string& source,
                   const std::string& resource_name) = 0;
  virtual v8::Handle<v8::Value> Call(v8::Handle<v8::Function> function,
                                     v8::Handle<v8::Value> receiver,
                                     int argc,
                                     v8::Handle<v8::Value> argv[]) = 0;
  virtual ContextHolder* GetContextHolder() = 0;

  v8::Handle<v8::Object> global() {
    return GetContextHolder()->context()->Global();
  }

  
  
  base::WeakPtr<Runner> GetWeakPtr() {
    return weak_factory_.GetWeakPtr();
  }

  class GIN_EXPORT Scope {
   public:
    explicit Scope(Runner* runner);
    ~Scope();

   private:
    v8::Isolate::Scope isolate_scope_;
    v8::HandleScope handle_scope_;
    v8::Context::Scope scope_;

    DISALLOW_COPY_AND_ASSIGN(Scope);
  };

 private:
  friend class Scope;

  base::WeakPtrFactory<Runner> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(Runner);
};

}  

#endif  

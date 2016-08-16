// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_PER_CONTEXT_DATA_H_
#define GIN_PER_CONTEXT_DATA_H_

#include "base/basictypes.h"
#include "base/supports_user_data.h"
#include "gin/gin_export.h"
#include "v8/include/v8.h"

namespace gin {

class ContextHolder;
class Runner;

class GIN_EXPORT PerContextData : public base::SupportsUserData {
 public:
  PerContextData(ContextHolder* context_holder,
                 v8::Handle<v8::Context> context);
  virtual ~PerContextData();

  
  static PerContextData* From(v8::Handle<v8::Context> context);

  
  
  Runner* runner() const { return runner_; }
  void set_runner(Runner* runner) { runner_ = runner; }

  ContextHolder* context_holder() { return context_holder_; }

 private:
  ContextHolder* context_holder_;
  Runner* runner_;

  DISALLOW_COPY_AND_ASSIGN(PerContextData);
};

}  

#endif  

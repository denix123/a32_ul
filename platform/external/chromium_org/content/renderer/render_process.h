// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_PROCESS_H_
#define CONTENT_RENDERER_RENDER_PROCESS_H_

#include "content/child/child_process.h"

namespace content {

class RenderProcess : public ChildProcess {
 public:
  RenderProcess() {}
  virtual ~RenderProcess() {}

  
  
  virtual void AddBindings(int bindings) = 0;

  
  virtual int GetEnabledBindings() const = 0;

  
  
  
  static RenderProcess* current() {
    return static_cast<RenderProcess*>(ChildProcess::current());
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(RenderProcess);
};

}  

#endif  

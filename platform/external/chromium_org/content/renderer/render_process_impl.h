// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_PROCESS_IMPL_H_
#define CONTENT_RENDERER_RENDER_PROCESS_IMPL_H_

#include "content/renderer/render_process.h"

namespace content {

class RenderProcessImpl : public RenderProcess {
 public:
  RenderProcessImpl();
  virtual ~RenderProcessImpl();

  
  virtual void AddBindings(int bindings) OVERRIDE;
  virtual int GetEnabledBindings() const OVERRIDE;

 private:
  
  
  int enabled_bindings_;

  DISALLOW_COPY_AND_ASSIGN(RenderProcessImpl);
};

}  

#endif  

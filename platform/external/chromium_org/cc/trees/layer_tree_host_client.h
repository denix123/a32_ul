// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TREES_LAYER_TREE_HOST_CLIENT_H_
#define CC_TREES_LAYER_TREE_HOST_CLIENT_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"

namespace gfx {
class Vector2d;
}

namespace cc {
class ContextProvider;
class InputHandlerClient;
class OutputSurface;
struct BeginFrameArgs;

class LayerTreeHostClient {
 public:
  virtual void WillBeginMainFrame(int frame_id) = 0;
  
  
  virtual void BeginMainFrame(const BeginFrameArgs& args) = 0;
  virtual void DidBeginMainFrame() = 0;
  virtual void Layout() = 0;
  virtual void ApplyViewportDeltas(const gfx::Vector2d& scroll_delta,
                                   float page_scale,
                                   float top_controls_delta) = 0;
  
  
  
  
  virtual void RequestNewOutputSurface(bool fallback) = 0;
  virtual void DidInitializeOutputSurface() = 0;
  virtual void WillCommit() = 0;
  virtual void DidCommit() = 0;
  virtual void DidCommitAndDrawFrame() = 0;
  virtual void DidCompleteSwapBuffers() = 0;

  
  
  
  
  virtual void RateLimitSharedMainThreadContext() {}

  
  virtual void DidFailToInitializeOutputSurface() {}

 protected:
  virtual ~LayerTreeHostClient() {}
};

}  

#endif  

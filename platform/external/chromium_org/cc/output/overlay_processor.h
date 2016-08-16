// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_OUTPUT_OVERLAY_PROCESSOR_H_
#define CC_OUTPUT_OVERLAY_PROCESSOR_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"
#include "cc/output/overlay_candidate.h"
#include "cc/quads/render_pass.h"

namespace cc {
class OutputSurface;
class ResourceProvider;

class CC_EXPORT OverlayProcessor {
 public:
  class CC_EXPORT Strategy {
   public:
    virtual ~Strategy() {}
    
    
    
    
    virtual bool Attempt(RenderPassList* render_passes_in_draw_order,
                         OverlayCandidateList* candidates) = 0;
  };
  typedef ScopedPtrVector<Strategy> StrategyList;

  OverlayProcessor(OutputSurface* surface, ResourceProvider* resource_provider);
  virtual ~OverlayProcessor();
  
  virtual void Initialize();

  void ProcessForOverlays(RenderPassList* render_passes_in_draw_order,
                          OverlayCandidateList* candidate_list);

 protected:
  StrategyList strategies_;
  OutputSurface* surface_;
  ResourceProvider* resource_provider_;

 private:
  DISALLOW_COPY_AND_ASSIGN(OverlayProcessor);
};

}  

#endif  

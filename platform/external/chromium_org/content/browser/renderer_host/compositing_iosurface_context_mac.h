// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_COMPOSITING_IOSURFACE_CONTEXT_MAC_H_
#define CONTENT_BROWSER_RENDERER_HOST_COMPOSITING_IOSURFACE_CONTEXT_MAC_H_

#import <AppKit/NSOpenGL.h>
#include <OpenGL/OpenGL.h>
#include <map>

#include "base/basictypes.h"
#include "base/lazy_instance.h"
#include "base/mac/scoped_nsobject.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/gpu_data_manager_observer.h"
#include "ui/gl/scoped_cgl.h"

namespace content {

class CompositingIOSurfaceContext
    : public base::RefCounted<CompositingIOSurfaceContext>,
      public content::GpuDataManagerObserver {
 public:
  enum {
    
    
    kOffscreenContextWindowNumber = -2,
    
    kCALayerContextWindowNumber = -3,
  };

  
  
  
  
  static scoped_refptr<CompositingIOSurfaceContext> Get(int window_number);

  
  
  
  
  void PoisonContextAndSharegroup();
  bool HasBeenPoisoned() const { return poisoned_; }

  CGLContextObj cgl_context() const { return cgl_context_; }
  int window_number() const { return window_number_; }

  
  virtual void OnGpuSwitching() OVERRIDE;

 private:
  friend class base::RefCounted<CompositingIOSurfaceContext>;

  CompositingIOSurfaceContext(
      int window_number,
      base::ScopedTypeRef<CGLContextObj> clg_context_strong,
      CGLContextObj clg_context);
  virtual ~CompositingIOSurfaceContext();

  int window_number_;
  base::ScopedTypeRef<CGLContextObj> cgl_context_strong_;
  
  CGLContextObj cgl_context_;

  bool poisoned_;

  
  
  typedef std::map<int, CompositingIOSurfaceContext*> WindowMap;
  static base::LazyInstance<WindowMap> window_map_;
  static WindowMap* window_map();
};

}  

#endif  

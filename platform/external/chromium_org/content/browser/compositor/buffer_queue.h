// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_COMPOSITOR_BUFFERED_OUTPUT_SURFACE_H_
#define CONTENT_BROWSER_COMPOSITOR_BUFFERED_OUTPUT_SURFACE_H_

#include <queue>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"

namespace cc {
class ContextProvider;
}

namespace content {

class CONTENT_EXPORT BufferQueue {
 public:
  BufferQueue(scoped_refptr<cc::ContextProvider> context_provider,
              unsigned int internalformat);
  virtual ~BufferQueue();

  bool Initialize();

  void BindFramebuffer();
  void SwapBuffers(const gfx::Rect& damage);
  void PageFlipComplete();
  void Reshape(const gfx::Size& size, float scale_factor);

  unsigned int current_texture_id() { return current_surface_.texture; }

 private:
  friend class BufferQueueTest;

  struct AllocatedSurface {
    AllocatedSurface() : texture(0), image(0) {}
    AllocatedSurface(unsigned int texture,
                     unsigned int image,
                     const gfx::Rect& rect)
        : texture(texture), image(image), damage(rect) {}
    unsigned int texture;
    unsigned int image;
    gfx::Rect damage;  
  };

  void FreeAllSurfaces();

  void FreeSurface(AllocatedSurface* surface);

  
  
  virtual void CopyBufferDamage(int texture,
                                int source_texture,
                                const gfx::Rect& new_damage,
                                const gfx::Rect& old_damage);

  void UpdateBufferDamage(const gfx::Rect& damage);

  
  AllocatedSurface GetNextSurface();

  gfx::Size size_;
  scoped_refptr<cc::ContextProvider> context_provider_;
  unsigned int fbo_;
  size_t allocated_count_;
  unsigned int internalformat_;
  AllocatedSurface current_surface_;  
  std::vector<AllocatedSurface> available_surfaces_;  
  std::deque<AllocatedSurface> in_flight_surfaces_;

  DISALLOW_COPY_AND_ASSIGN(BufferQueue);
};

}  

#endif  

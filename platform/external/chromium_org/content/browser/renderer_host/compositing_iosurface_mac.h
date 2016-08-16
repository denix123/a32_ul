// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_COMPOSITING_IOSURFACE_MAC_H_
#define CONTENT_BROWSER_RENDERER_HOST_COMPOSITING_IOSURFACE_MAC_H_

#include <deque>
#include <list>
#include <vector>

#import <Cocoa/Cocoa.h>
#include <IOSurface/IOSurfaceAPI.h>
#include <QuartzCore/QuartzCore.h>

#include "base/callback.h"
#include "base/lazy_instance.h"
#include "base/mac/scoped_cftyperef.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "media/base/video_frame.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/rect_conversions.h"
#include "ui/gfx/size.h"

class SkBitmap;

namespace gfx {
class Rect;
}

namespace content {

class CompositingIOSurfaceContext;
class RenderWidgetHostViewFrameSubscriber;
class RenderWidgetHostViewMac;

class CompositingIOSurfaceMac
    : public base::RefCounted<CompositingIOSurfaceMac> {
 public:
  
  static scoped_refptr<CompositingIOSurfaceMac> Create();

  
  bool SetIOSurfaceWithContextCurrent(
      scoped_refptr<CompositingIOSurfaceContext> current_context,
      IOSurfaceID io_surface_handle,
      const gfx::Size& size,
      float scale_factor) WARN_UNUSED_RESULT;

  
  int GetRendererID();

  
  
  
  
  bool DrawIOSurface(
      scoped_refptr<CompositingIOSurfaceContext> drawing_context,
      const gfx::Rect& window_rect,
      float window_scale_factor) WARN_UNUSED_RESULT;

  
  
  
  
  
  
  
  
  void CopyTo(const gfx::Rect& src_pixel_subrect,
              const gfx::Size& dst_pixel_size,
              const base::Callback<void(bool, const SkBitmap&)>& callback);

  
  
  void CopyToVideoFrame(
      const gfx::Rect& src_subrect,
      const scoped_refptr<media::VideoFrame>& target,
      const base::Callback<void(bool)>& callback);

  
  
  void UnrefIOSurface();

  bool HasIOSurface() { return !!io_surface_.get(); }

  const gfx::Size& pixel_io_surface_size() const {
    return pixel_io_surface_size_;
  }
  
  const gfx::Size& dip_io_surface_size() const { return dip_io_surface_size_; }
  float scale_factor() const { return scale_factor_; }

  
  bool IsAsynchronousReadbackSupported();

  
  
  
  void CheckIfAllCopiesAreFinished(bool block_until_finished);

  
  
  bool HasBeenPoisoned() const;

 private:
  friend class base::RefCounted<CompositingIOSurfaceMac>;

  
  struct SurfaceVertex {
    SurfaceVertex() : x_(0.0f), y_(0.0f), tx_(0.0f), ty_(0.0f) { }
    void set(float x, float y, float tx, float ty) {
      x_ = x;
      y_ = y;
      tx_ = tx;
      ty_ = ty;
    }
    void set_position(float x, float y) {
      x_ = x;
      y_ = y;
    }
    void set_texcoord(float tx, float ty) {
      tx_ = tx;
      ty_ = ty;
    }
    float x_;
    float y_;
    float tx_;
    float ty_;
  };

  
  struct SurfaceQuad {
    void set_size(gfx::Size vertex_size, gfx::Size texcoord_size) {
      
      
      float vw = static_cast<float>(vertex_size.width());
      float vh = static_cast<float>(vertex_size.height());
      float tw = static_cast<float>(texcoord_size.width());
      float th = static_cast<float>(texcoord_size.height());
      verts_[0].set(0.0f, 0.0f, 0.0f, th);
      verts_[1].set(0.0f, vh, 0.0f, 0.0f);
      verts_[2].set(vw, vh, tw, 0.0f);
      verts_[3].set(vw, 0.0f, tw, th);
    }
    void set_rect(float x1, float y1, float x2, float y2) {
      verts_[0].set_position(x1, y1);
      verts_[1].set_position(x1, y2);
      verts_[2].set_position(x2, y2);
      verts_[3].set_position(x2, y1);
    }
    void set_texcoord_rect(float tx1, float ty1, float tx2, float ty2) {
      
      
      verts_[0].set_texcoord(tx1, ty2);
      verts_[1].set_texcoord(tx1, ty1);
      verts_[2].set_texcoord(tx2, ty1);
      verts_[3].set_texcoord(tx2, ty2);
    }
    SurfaceVertex verts_[4];
  };

  CompositingIOSurfaceMac(
      const scoped_refptr<CompositingIOSurfaceContext>& context);
  ~CompositingIOSurfaceMac();

  
  bool MapIOSurfaceToTextureWithContextCurrent(
      const scoped_refptr<CompositingIOSurfaceContext>& current_context,
      const gfx::Size pixel_size,
      float scale_factor,
      IOSurfaceID io_surface_handle) WARN_UNUSED_RESULT;

  void UnrefIOSurfaceWithContextCurrent();

  void DrawQuad(const SurfaceQuad& quad);

  
  
  GLenum GetAndSaveGLError();

  
  
  
  scoped_refptr<CompositingIOSurfaceContext> offscreen_context_;

  
  IOSurfaceID io_surface_handle_;
  base::ScopedCFTypeRef<IOSurfaceRef> io_surface_;

  
  gfx::Size pixel_io_surface_size_;  
  gfx::Size dip_io_surface_size_;  
  float scale_factor_;

  
  
  
  
  
  GLuint texture_;

  
  GLint gl_error_;

  
  
  
  
  
  
  enum {
    kMaximumUnevictedSurfaces = 8,
  };
  typedef std::list<CompositingIOSurfaceMac*> EvictionQueue;
  void EvictionMarkUpdated();
  void EvictionMarkEvicted();
  EvictionQueue::iterator eviction_queue_iterator_;
  bool eviction_has_been_drawn_since_updated_;

  static void EvictionScheduleDoEvict();
  static void EvictionDoEvict();
  static base::LazyInstance<EvictionQueue> eviction_queue_;
  static bool eviction_scheduled_;
};

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_RENDERING_HELPER_H_
#define CONTENT_COMMON_GPU_MEDIA_RENDERING_HELPER_H_

#include <map>
#include <queue>
#include <vector>

#include "base/basictypes.h"
#include "base/cancelable_callback.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gl/gl_bindings.h"
#include "ui/gl/gl_context.h"
#include "ui/gl/gl_surface.h"

namespace base {
class MessageLoop;
class WaitableEvent;
}

namespace content {

class VideoFrameTexture : public base::RefCounted<VideoFrameTexture> {
 public:
  uint32 texture_id() const { return texture_id_; }
  uint32 texture_target() const { return texture_target_; }

  VideoFrameTexture(uint32 texture_target,
                    uint32 texture_id,
                    const base::Closure& no_longer_needed_cb);

 private:
  friend class base::RefCounted<VideoFrameTexture>;

  uint32 texture_target_;
  uint32 texture_id_;
  base::Closure no_longer_needed_cb_;

  ~VideoFrameTexture();
};

struct RenderingHelperParams {
  RenderingHelperParams();
  ~RenderingHelperParams();

  
  int rendering_fps;

  
  
  std::vector<gfx::Size> window_sizes;

  
  

  
  
  bool render_as_thumbnails;
  
  gfx::Size thumbnails_page_size;
  
  gfx::Size thumbnail_size;
};

class RenderingHelper {
 public:

  RenderingHelper();
  ~RenderingHelper();

  static bool InitializeOneOff();

  
  void Initialize(const RenderingHelperParams& params,
                  base::WaitableEvent* done);

  
  void UnInitialize(base::WaitableEvent* done);

  
  
  void CreateTexture(uint32 texture_target,
                     uint32* texture_id,
                     const gfx::Size& size,
                     base::WaitableEvent* done);

  
  
  void RenderThumbnail(uint32 texture_target, uint32 texture_id);

  
  void QueueVideoFrame(size_t window_id,
                       scoped_refptr<VideoFrameTexture> video_frame);

  
  
  void Flush(size_t window_id);

  
  void DeleteTexture(uint32 texture_id);

  
  void* GetGLDisplay();

  
  void* GetGLContext();

  
  
  void GetThumbnailsAsRGB(std::vector<unsigned char>* rgb,
                          bool* alpha_solid,
                          base::WaitableEvent* done);

 private:
  struct RenderedVideo {
    
    gfx::Rect render_area;

    
    
    
    
    
    bool last_frame_rendered;

    
    bool is_flushing;

    
    int frames_to_drop;

    
    std::queue<scoped_refptr<VideoFrameTexture> > pending_frames;

    RenderedVideo();
    ~RenderedVideo();
  };

  void Clear();

  void RenderContent();

  void LayoutRenderingAreas(const std::vector<gfx::Size>& window_sizes);

  
  
  void RenderTexture(uint32 texture_target, uint32 texture_id);

  base::MessageLoop* message_loop_;

  scoped_refptr<gfx::GLContext> gl_context_;
  scoped_refptr<gfx::GLSurface> gl_surface_;

  gfx::AcceleratedWidget window_;

  gfx::Size screen_size_;

  std::vector<RenderedVideo> videos_;

  bool render_as_thumbnails_;
  int frame_count_;
  GLuint thumbnails_fbo_id_;
  GLuint thumbnails_texture_id_;
  gfx::Size thumbnails_fbo_size_;
  gfx::Size thumbnail_size_;
  GLuint program_;
  base::TimeDelta frame_duration_;
  base::TimeTicks scheduled_render_time_;
  base::CancelableClosure render_task_;

  DISALLOW_COPY_AND_ASSIGN(RenderingHelper);
};

}  

#endif  

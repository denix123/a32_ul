// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_VIDEO_FRAME_COMPOSITOR_H_
#define MEDIA_BLINK_VIDEO_FRAME_COMPOSITOR_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "cc/layers/video_frame_provider.h"
#include "media/base/media_export.h"
#include "ui/gfx/size.h"

namespace media {
class VideoFrame;

class MEDIA_EXPORT VideoFrameCompositor
    : NON_EXPORTED_BASE(public cc::VideoFrameProvider) {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  VideoFrameCompositor(
      const base::Callback<void(gfx::Size)>& natural_size_changed_cb,
      const base::Callback<void(bool)>& opacity_changed_cb);
  virtual ~VideoFrameCompositor();

  
  virtual void SetVideoFrameProviderClient(
      cc::VideoFrameProvider::Client* client) OVERRIDE;
  virtual scoped_refptr<VideoFrame> GetCurrentFrame() OVERRIDE;
  virtual void PutCurrentFrame(
      const scoped_refptr<VideoFrame>& frame) OVERRIDE;

  
  void UpdateCurrentFrame(const scoped_refptr<VideoFrame>& frame);

 private:
  base::Callback<void(gfx::Size)> natural_size_changed_cb_;
  base::Callback<void(bool)> opacity_changed_cb_;

  cc::VideoFrameProvider::Client* client_;

  scoped_refptr<VideoFrame> current_frame_;

  DISALLOW_COPY_AND_ASSIGN(VideoFrameCompositor);
};

}  

#endif  

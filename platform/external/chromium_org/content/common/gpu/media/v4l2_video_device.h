// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_DEVICE_H_
#define CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_DEVICE_H_

#include "media/base/video_decoder_config.h"
#include "media/base/video_frame.h"
#include "ui/gfx/size.h"
#include "ui/gl/gl_bindings.h"

namespace content {

class V4L2Device {
 public:
  
  static media::VideoFrame::Format V4L2PixFmtToVideoFrameFormat(uint32 format);
  static uint32 VideoFrameFormatToV4L2PixFmt(media::VideoFrame::Format format);
  static uint32 VideoCodecProfileToV4L2PixFmt(media::VideoCodecProfile profile);
  
  static gfx::Size CodedSizeFromV4L2Format(struct v4l2_format format);

  virtual ~V4L2Device();

  enum Type {
    kDecoder,
    kEncoder,
    kImageProcessor,
  };

  
  
  static scoped_ptr<V4L2Device> Create(Type type);

  
  
  virtual int Ioctl(int request, void* arg) = 0;

  
  
  
  
  
  
  
  virtual bool Poll(bool poll_device, bool* event_pending) = 0;

  
  
  
  
  
  
  virtual bool SetDevicePollInterrupt() = 0;
  virtual bool ClearDevicePollInterrupt() = 0;

  
  virtual void* Mmap(void* addr,
                     unsigned int len,
                     int prot,
                     int flags,
                     unsigned int offset) = 0;
  virtual void Munmap(void* addr, unsigned int len) = 0;

  
  
  virtual bool Initialize() = 0;

  
  
  
  
  
  virtual EGLImageKHR CreateEGLImage(EGLDisplay egl_display,
                                     EGLContext egl_context,
                                     GLuint texture_id,
                                     gfx::Size frame_buffer_size,
                                     unsigned int buffer_index,
                                     size_t planes_count) = 0;

  
  virtual EGLBoolean DestroyEGLImage(EGLDisplay egl_display,
                                     EGLImageKHR egl_image) = 0;

  
  virtual GLenum GetTextureTarget() = 0;

  
  virtual uint32 PreferredInputFormat() = 0;

  
  virtual uint32 PreferredOutputFormat() = 0;
};

}  

#endif  

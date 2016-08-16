// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_TYPES_H_
#define MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_TYPES_H_

#include <vector>

#include "media/base/media_export.h"
#include "ui/gfx/size.h"

namespace media {

typedef int VideoCaptureSessionId;

enum VideoPixelFormat {
  PIXEL_FORMAT_UNKNOWN,  
  PIXEL_FORMAT_I420,
  PIXEL_FORMAT_YUY2,
  PIXEL_FORMAT_UYVY,
  PIXEL_FORMAT_RGB24,
  PIXEL_FORMAT_ARGB,
  PIXEL_FORMAT_MJPEG,
  PIXEL_FORMAT_NV21,
  PIXEL_FORMAT_YV12,
  PIXEL_FORMAT_TEXTURE,  
  PIXEL_FORMAT_MAX,
};

enum ResolutionChangePolicy {
  
  
  
  
  RESOLUTION_POLICY_FIXED,

  
  
  
  
  RESOLUTION_POLICY_DYNAMIC_WITHIN_LIMIT,

  RESOLUTION_POLICY_LAST,
};

const int kFrameRatePrecision = 10000;

class MEDIA_EXPORT VideoCaptureFormat {
 public:
  VideoCaptureFormat();
  VideoCaptureFormat(const gfx::Size& frame_size,
                     float frame_rate,
                     VideoPixelFormat pixel_format);

  std::string ToString() const;
  static std::string PixelFormatToString(VideoPixelFormat format);

  
  
  bool IsValid() const;

  gfx::Size frame_size;
  float frame_rate;
  VideoPixelFormat pixel_format;
};

typedef std::vector<VideoCaptureFormat> VideoCaptureFormats;

class MEDIA_EXPORT VideoCaptureParams {
 public:
  VideoCaptureParams();

  
  VideoCaptureFormat requested_format;

  
  ResolutionChangePolicy resolution_change_policy;
};

}  

#endif  

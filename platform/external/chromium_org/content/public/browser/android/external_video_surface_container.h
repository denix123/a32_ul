// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_ANDROID_EXTERNAL_VIDEO_SURFACE_CONTAINER_H_
#define CONTENT_PUBLIC_BROWSER_ANDROID_EXTERNAL_VIDEO_SURFACE_CONTAINER_H_

#include <jni.h>

#include "base/callback.h"
#include "content/common/content_export.h"

namespace gfx {
class RectF;
}

namespace content {
class WebContents;

class CONTENT_EXPORT ExternalVideoSurfaceContainer {
 public:
  typedef base::Callback<void(int, jobject)> SurfaceCreatedCB;
  typedef base::Callback<void(int)> SurfaceDestroyedCB;

  
  
  
  
  virtual void RequestExternalVideoSurface(
      int player_id,
      const SurfaceCreatedCB& surface_created_cb,
      const SurfaceDestroyedCB& surface_destroyed_cb) = 0;

  
  virtual void ReleaseExternalVideoSurface(int player_id) = 0;

  
  
  
  virtual void OnExternalVideoSurfacePositionChanged(
      int player_id, const gfx::RectF& rect) = 0;

  
  virtual void OnFrameInfoUpdated() = 0;

  virtual ~ExternalVideoSurfaceContainer() {}
};

}  

#endif  

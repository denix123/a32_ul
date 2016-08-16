// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_BROWSER_BROWSER_VIEW_RENDERER_CLIENT_H_
#define ANDROID_WEBVIEW_BROWSER_BROWSER_VIEW_RENDERER_CLIENT_H_

#include "base/android/scoped_java_ref.h"
#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/size_f.h"
#include "ui/gfx/geometry/vector2d_f.h"

namespace android_webview {

class BrowserViewRendererClient {
 public:
  
  
  
  
  
  virtual bool RequestDrawGL(jobject canvas, bool wait_for_completion) = 0;

  
  
  virtual void OnNewPicture() = 0;

  
  virtual void PostInvalidate() = 0;

  
  virtual void UpdateParentDrawConstraints() = 0;

  
  virtual void DidSkipCommitFrame() = 0;

  
  virtual gfx::Point GetLocationOnScreen() = 0;

  
  virtual void ScrollContainerViewTo(gfx::Vector2d new_value) = 0;

  
  virtual bool IsFlingActive() const = 0;

  
  
  
  
  
  virtual void UpdateScrollState(gfx::Vector2d max_scroll_offset,
                                 gfx::SizeF contents_size_dip,
                                 float page_scale_factor,
                                 float min_page_scale_factor,
                                 float max_page_scale_factor) = 0;

  
  virtual void DidOverscroll(gfx::Vector2d overscroll_delta) = 0;

 protected:
  virtual ~BrowserViewRendererClient() {}
};

}  

#endif  

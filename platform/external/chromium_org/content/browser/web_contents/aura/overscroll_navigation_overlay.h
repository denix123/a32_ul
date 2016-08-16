// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_WEB_CONTENTS_AURA_OVERSCROLL_NAVIGATION_OVERLAY_H_
#define CONTENT_BROWSER_WEB_CONTENTS_AURA_OVERSCROLL_NAVIGATION_OVERLAY_H_

#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "content/browser/web_contents/aura/window_slider.h"
#include "content/common/content_export.h"
#include "content/public/browser/web_contents_observer.h"

struct ViewHostMsg_UpdateRect_Params;

namespace content {

class ImageLayerDelegate;
class ImageWindowDelegate;
class OverscrollNavigationOverlayTest;

class CONTENT_EXPORT OverscrollNavigationOverlay
    : public WebContentsObserver,
      public WindowSlider::Delegate {
 public:
  explicit OverscrollNavigationOverlay(WebContentsImpl* web_contents);
  virtual ~OverscrollNavigationOverlay();

  bool has_window() const { return !!window_.get(); }

  
  
  
  
  
  
  void StartObserving();

  
  
  
  
  void SetOverlayWindow(scoped_ptr<aura::Window> window,
                        ImageWindowDelegate* delegate);

 private:
  friend class OverscrollNavigationOverlayTest;
  FRIEND_TEST_ALL_PREFIXES(OverscrollNavigationOverlayTest,
                           FirstVisuallyNonEmptyPaint_NoImage);
  FRIEND_TEST_ALL_PREFIXES(OverscrollNavigationOverlayTest,
                           FirstVisuallyNonEmptyPaint_WithImage);
  FRIEND_TEST_ALL_PREFIXES(OverscrollNavigationOverlayTest,
                           LoadUpdateWithoutNonEmptyPaint);
  FRIEND_TEST_ALL_PREFIXES(OverscrollNavigationOverlayTest,
                           MultiNavigation_LoadingUpdate);
  FRIEND_TEST_ALL_PREFIXES(OverscrollNavigationOverlayTest,
                           MultiNavigation_PaintUpdate);

  enum SlideDirection {
    SLIDE_UNKNOWN,
    SLIDE_BACK,
    SLIDE_FRONT
  };

  
  
  
  void StopObservingIfDone();

  
  
  ui::Layer* CreateSlideLayer(int offset);

  
  virtual ui::Layer* CreateBackLayer() OVERRIDE;
  virtual ui::Layer* CreateFrontLayer() OVERRIDE;
  virtual void OnWindowSlideCompleting() OVERRIDE;
  virtual void OnWindowSlideCompleted(scoped_ptr<ui::Layer> layer) OVERRIDE;
  virtual void OnWindowSlideAborted() OVERRIDE;
  virtual void OnWindowSliderDestroyed() OVERRIDE;

  
  virtual void DidFirstVisuallyNonEmptyPaint() OVERRIDE;
  virtual void DidStopLoading(RenderViewHost* host) OVERRIDE;

  
  WebContentsImpl* web_contents_;

  
  scoped_ptr<aura::Window> window_;

  
  
  ImageWindowDelegate* image_delegate_;

  bool loading_complete_;
  bool received_paint_update_;

  
  
  
  GURL pending_entry_url_;

  
  
  scoped_ptr<WindowSlider> window_slider_;

  
  
  scoped_ptr<ui::Layer> overlay_dismiss_layer_;

  
  SlideDirection slide_direction_;

  
  scoped_ptr<ImageLayerDelegate> layer_delegate_;

  DISALLOW_COPY_AND_ASSIGN(OverscrollNavigationOverlay);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_VIEW_OVERSCROLL_ANIMATOR_SLIDER_MAC_H_
#define CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_VIEW_OVERSCROLL_ANIMATOR_SLIDER_MAC_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/web_contents/web_contents_view_overscroll_animator_mac.h"

namespace overscroll_animator {
class WebContentsPaintObserver;
}  

@interface OverscrollAnimatorSliderView
    : NSView<WebContentsOverscrollAnimator> {
  
  
  
  
  
  base::scoped_nsobject<NSView> middleView_;

  
  
  
  
  base::scoped_nsobject<NSImageView> bottomView_;

  
  
  
  
  base::scoped_nsobject<NSImageView> topView_;

  
  
  content::OverscrollAnimatorDirection direction_;

  
  
  BOOL animating_;

  
  BOOL inOverscroll_;

  
  CGFloat progress_;

  
  
  scoped_ptr<overscroll_animator::WebContentsPaintObserver> observer_;
}
@end

#endif  

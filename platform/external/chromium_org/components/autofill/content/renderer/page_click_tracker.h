// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CONTENT_RENDERER_PAGE_CLICK_TRACKER_H_
#define COMPONENTS_AUTOFILL_CONTENT_RENDERER_PAGE_CLICK_TRACKER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "content/public/renderer/render_view_observer.h"
#include "third_party/WebKit/public/web/WebNode.h"

namespace autofill {

class PageClickListener;

class PageClickTracker : public content::RenderViewObserver {
 public:
  
  
  PageClickTracker(content::RenderView* render_view,
                   PageClickListener* listener);
  virtual ~PageClickTracker();

 private:
  
  virtual void DidHandleMouseEvent(const blink::WebMouseEvent& event) OVERRIDE;
  virtual void DidHandleGestureEvent(
      const blink::WebGestureEvent& event) OVERRIDE;
  virtual void FocusedNodeChanged(const blink::WebNode& node) OVERRIDE;

  
  void PotentialActivationAt(int x, int y);

  
  void SetWasFocused();

  
  
  
  bool was_focused_before_now_;

  
  PageClickListener* listener_;

  base::WeakPtrFactory<PageClickTracker> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PageClickTracker);
};

}  

#endif  

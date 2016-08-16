// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_ACCESSIBILITY_RENDERER_ACCESSIBILITY_H_
#define CONTENT_RENDERER_ACCESSIBILITY_RENDERER_ACCESSIBILITY_H_

#include "content/common/accessibility_messages.h"
#include "content/public/renderer/render_frame_observer.h"
#include "third_party/WebKit/public/web/WebAXObject.h"

namespace blink {
class WebDocument;
};

namespace content {
class RenderFrameImpl;

enum RendererAccessibilityType {
  
  
  RendererAccessibilityTypeComplete,

  
  
  
  
  RendererAccessibilityTypeFocusOnly
};

class CONTENT_EXPORT RendererAccessibility : public RenderFrameObserver {
 public:
  explicit RendererAccessibility(RenderFrameImpl* render_frame);
  virtual ~RendererAccessibility();

  
  virtual void HandleWebAccessibilityEvent(
      const blink::WebAXObject& obj, blink::WebAXEvent event) = 0;
  virtual void FocusedNodeChanged(const blink::WebNode& node) = 0;

  
  
  virtual RendererAccessibilityType GetType() = 0;

 protected:
  
  
  blink::WebDocument GetMainDocument();

  
  RenderFrameImpl* render_frame_;

  DISALLOW_COPY_AND_ASSIGN(RendererAccessibility);
};

}  

#endif  

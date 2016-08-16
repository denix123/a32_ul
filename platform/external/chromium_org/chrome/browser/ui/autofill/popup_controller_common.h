// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTOFILL_POPUP_CONTROLLER_COMMON_H_
#define CHROME_BROWSER_UI_AUTOFILL_POPUP_CONTROLLER_COMMON_H_

#include "content/public/browser/render_widget_host.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/rect_f.h"

namespace content {
struct NativeWebKeyboardEvent;
class RenderViewHost;
class WebContents;
}

namespace gfx {
class Display;
}

namespace autofill {

class PopupControllerCommon {
 public:
  PopupControllerCommon(const gfx::RectF& element_bounds,
                        gfx::NativeView container_view,
                        content::WebContents* web_contents);
  virtual ~PopupControllerCommon();

  const gfx::RectF& element_bounds() const { return element_bounds_; }
  gfx::NativeView container_view() { return container_view_; }
  content::WebContents* web_contents() { return web_contents_; }

  
  const gfx::Rect RoundedElementBounds() const;

  
  
  
  gfx::Rect GetPopupBounds(int desired_width, int desired_height) const;

  
  
  
  void SetKeyPressCallback(content::RenderWidgetHost::KeyPressEventCallback);

  
  
  
  void RegisterKeyPressCallback();

  
  
  
  void RemoveKeyPressCallback();

 protected:
  
  
  virtual gfx::Display GetDisplayNearestPoint(const gfx::Point& point) const;

 private:
  
  
  std::pair<int, int> CalculatePopupXAndWidth(
      const gfx::Display& left_display,
      const gfx::Display& right_display,
      int popup_required_width) const;

  
  
  std::pair<int, int> CalculatePopupYAndHeight(
      const gfx::Display& top_display,
      const gfx::Display& bottom_display,
      int popup_required_height) const;

  
  
  gfx::RectF element_bounds_;

  
  gfx::NativeView container_view_;

  
  
  
  content::WebContents* web_contents_;

  
  
  content::RenderViewHost* key_press_event_target_;

  content::RenderWidgetHost::KeyPressEventCallback key_press_event_callback_;

  DISALLOW_COPY_AND_ASSIGN(PopupControllerCommon);
};

}  

#endif  

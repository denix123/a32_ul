// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_LINK_DISAMBIGUATION_LINK_DISAMBIGUATION_POPUP_H_
#define CHROME_BROWSER_UI_VIEWS_LINK_DISAMBIGUATION_LINK_DISAMBIGUATION_POPUP_H_

#include "content/public/browser/web_contents_view_delegate.h"
#include "ui/gfx/geometry/rect.h"

namespace aura {
class Window;
}

namespace ui {
class MouseEvent;
}

class LinkDisambiguationPopup {
 public:
  LinkDisambiguationPopup();
  ~LinkDisambiguationPopup();

  
  
  
  
  
  
  void Show(const SkBitmap& zoomed_bitmap,
            const gfx::Rect& target_rect,
            const gfx::NativeView content,
            const base::Callback<void(ui::GestureEvent*)>& gesture_cb,
            const base::Callback<void(ui::MouseEvent*)>& mouse_cb);
  void Close();

 private:
  class ZoomBubbleView;

  
  
  
  void InvalidateBubbleView();

  
  
  const aura::Window* content_;
  ZoomBubbleView* view_;

  DISALLOW_COPY_AND_ASSIGN(LinkDisambiguationPopup);
};

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_EV_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_EV_BUBBLE_VIEW_H_

#include "chrome/browser/ui/views/location_bar/icon_label_bubble_view.h"
#include "chrome/browser/ui/views/location_bar/page_info_helper.h"

class LocationBarView;

class EVBubbleView : public IconLabelBubbleView {
 public:
  EVBubbleView(const gfx::FontList& font_list,
               SkColor text_color,
               SkColor parent_background_color,
               LocationBarView* parent);
  virtual ~EVBubbleView();

  
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  
  gfx::Size GetMinimumSizeForLabelText(const base::string16& text) const;

 private:
  
  gfx::Size GetMinimumSizeForPreferredSize(gfx::Size size) const;

  PageInfoHelper page_info_helper_;

  DISALLOW_COPY_AND_ASSIGN(EVBubbleView);
};

#endif  
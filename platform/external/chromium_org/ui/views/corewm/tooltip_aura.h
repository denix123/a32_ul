// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_COREWM_TOOLTIP_AURA_H_
#define UI_VIEWS_COREWM_TOOLTIP_AURA_H_

#include "ui/gfx/screen_type_delegate.h"
#include "ui/views/controls/label.h"
#include "ui/views/corewm/tooltip.h"
#include "ui/views/widget/widget_observer.h"

namespace gfx {
class FontList;
}  

namespace views {

class Widget;

namespace corewm {

class VIEWS_EXPORT TooltipAura : public Tooltip, public WidgetObserver {
 public:
  explicit TooltipAura(gfx::ScreenType screen_type);
  virtual ~TooltipAura();

  
  
  
  
  static void TrimTooltipToFit(const gfx::FontList& font_list,
                               int max_width,
                               base::string16* text,
                               int* width,
                               int* line_count);

 private:
  
  int GetMaxWidth(const gfx::Point& location) const;

  
  
  void SetTooltipBounds(const gfx::Point& mouse_pos,
                        const gfx::Size& tooltip_size);

  
  void DestroyWidget();

  
  virtual void SetText(aura::Window* window,
                       const base::string16& tooltip_text,
                       const gfx::Point& location) OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual bool IsVisible() OVERRIDE;

  
  virtual void OnWidgetDestroying(Widget* widget) OVERRIDE;

  const gfx::ScreenType screen_type_;

  
  Label label_;

  
  Widget* widget_;

  
  
  aura::Window* tooltip_window_;

  DISALLOW_COPY_AND_ASSIGN(TooltipAura);
};

}  
}  

#endif  

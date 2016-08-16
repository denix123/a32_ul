// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_ORIGIN_CHIP_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_ORIGIN_CHIP_VIEW_H_

#include "chrome/browser/safe_browsing/ui_manager.h"
#include "chrome/browser/ui/toolbar/toolbar_model.h"
#include "chrome/browser/ui/views/location_bar/location_icon_view.h"
#include "ui/gfx/animation/slide_animation.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/button/label_button.h"

class LocationBarView;
class OriginChipExtensionIcon;
class Profile;

namespace content {
class WebContents;
}

namespace gfx {
class FontList;
}

namespace views {
class Label;
}

class OriginChipView : public views::LabelButton,
                       public views::ButtonListener,
                       public SafeBrowsingUIManager::Observer {
 public:
  OriginChipView(LocationBarView* location_bar_view,
                 Profile* profile,
                 const gfx::FontList& font_list);
  virtual ~OriginChipView();

  SkColor pressed_text_color() const { return pressed_text_color_; }
  SkColor pressed_background_color() const {
    return background_colors_[Button::STATE_PRESSED];
  }
  const base::string16& host_label_text() const { return host_label_->text(); }

  
  
  void OnChanged();

  
  void FadeIn();
  void CancelFade();

  
  
  
  
  int HostLabelOffset() const;

  
  
  int WidthFromStartOfLabels() const;

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;

 private:
  
  int GetLabelX() const;

  
  void SetBorderImages(const int images[3][9]);

  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;
  virtual void AnimationEnded(const gfx::Animation* animation) OVERRIDE;
  virtual void OnPaintBorder(gfx::Canvas* canvas) OVERRIDE;
  virtual void StateChanged() OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void OnSafeBrowsingHit(
      const SafeBrowsingUIManager::UnsafeResource& resource) OVERRIDE;
  virtual void OnSafeBrowsingMatch(
      const SafeBrowsingUIManager::UnsafeResource& resource) OVERRIDE;

  LocationBarView* location_bar_view_;
  Profile* profile_;
  SkColor pressed_text_color_;
  SkColor background_colors_[3];
  views::Label* ev_label_;
  views::Label* host_label_;
  LocationIconView* location_icon_view_;
  bool showing_16x16_icon_;
  scoped_ptr<OriginChipExtensionIcon> extension_icon_;
  gfx::SlideAnimation fade_in_animation_;
  GURL url_displayed_;
  ToolbarModel::SecurityLevel security_level_;
  bool url_malware_;

  DISALLOW_COPY_AND_ASSIGN(OriginChipView);
};

#endif  

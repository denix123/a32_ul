// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_EXTENSIONS_BOOKMARK_APP_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_EXTENSIONS_BOOKMARK_APP_BUBBLE_VIEW_H_

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "chrome/browser/extensions/app_icon_loader.h"
#include "chrome/common/web_application_info.h"
#include "ui/views/bubble/bubble_delegate.h"
#include "ui/views/controls/button/button.h"

class Profile;

namespace extensions {
class AppIconLoader;
}

namespace gfx {
class ImageSkia;
}

namespace views {
class Checkbox;
class ImageView;
class LabelButton;
class Textfield;
}

class BookmarkAppBubbleView : public views::BubbleDelegateView,
                              public views::ButtonListener,
                              public extensions::AppIconLoader::Delegate {
 public:
  virtual ~BookmarkAppBubbleView();

  static void ShowBubble(views::View* anchor_view,
                         Profile* profile,
                         const WebApplicationInfo& web_app_info,
                         const std::string& extension_id);

 private:
  
  BookmarkAppBubbleView(views::View* anchor_view,
                        Profile* profile,
                        const WebApplicationInfo& web_app_info,
                        const std::string& extension_id);

  
  virtual void Init() OVERRIDE;
  virtual views::View* GetInitiallyFocusedView() OVERRIDE;

  
  virtual void WindowClosing() OVERRIDE;

  
  virtual bool AcceleratorPressed(const ui::Accelerator& accelerator) OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;

  
  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void SetAppImage(const std::string& id,
                           const gfx::ImageSkia& image) OVERRIDE;

  
  void HandleButtonPressed(views::Button* sender);

  
  void ApplyEdits();

  
  static BookmarkAppBubbleView* bookmark_app_bubble_;

  
  Profile* profile_;

  
  const WebApplicationInfo web_app_info_;

  
  const std::string extension_id_;

  
  views::LabelButton* add_button_;

  
  views::LabelButton* cancel_button_;

  
  views::Checkbox* open_as_tab_checkbox_;

  
  views::Textfield* title_tf_;

  
  views::ImageView* icon_image_view_;

  
  bool remove_app_;

  
  scoped_ptr<extensions::AppIconLoader> app_icon_loader_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkAppBubbleView);
};

#endif  

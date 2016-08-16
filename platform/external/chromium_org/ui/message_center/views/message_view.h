// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_VIEWS_MESSAGE_VIEW_H_
#define UI_MESSAGE_CENTER_VIEWS_MESSAGE_VIEW_H_

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/gfx/insets.h"
#include "ui/message_center/message_center_export.h"
#include "ui/message_center/notification.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/slide_out_view.h"

namespace ui {
class MenuModel;
}

namespace views {
class ImageButton;
class ImageView;
class Painter;
class ScrollView;
}

namespace message_center {

class MessageViewController {
 public:
  virtual void ClickOnNotification(const std::string& notification_id) = 0;
  virtual void RemoveNotification(const std::string& notification_id,
                                  bool by_user) = 0;
};

const int kPaddingBetweenItems = 10;
const int kPaddingHorizontal = 18;
const int kWebNotificationButtonWidth = 32;
const int kWebNotificationIconSize = 40;

class MESSAGE_CENTER_EXPORT MessageView : public views::SlideOutView,
                                          public views::ButtonListener {
 public:
  MessageView(MessageViewController* controller,
              const std::string& notification_id,
              const NotifierId& notifier_id,
              const gfx::ImageSkia& small_image,
              const base::string16& display_source);
  virtual ~MessageView();

  
  virtual void UpdateWithNotification(const Notification& notification);

  
  static gfx::Insets GetShadowInsets();

  
  void CreateShadowBorder();

  bool IsCloseButtonFocused();
  void RequestFocusOnCloseButton();

  void set_accessible_name(const base::string16& accessible_name) {
    accessible_name_ = accessible_name;
  }

  
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;
  virtual bool OnKeyReleased(const ui::KeyEvent& event) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;
  virtual void Layout() OVERRIDE;

  
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  void set_scroller(views::ScrollView* scroller) { scroller_ = scroller; }
  std::string notification_id() { return notification_id_; }
  NotifierId notifier_id() { return notifier_id_; }
  const base::string16& display_source() const { return display_source_; }

 protected:
  
  virtual void OnSlideOut() OVERRIDE;

  views::ImageView* small_image() { return small_image_view_.get(); }
  views::ImageButton* close_button() { return close_button_.get(); }
  views::ScrollView* scroller() { return scroller_; }

 private:
  MessageViewController* controller_;
  std::string notification_id_;
  NotifierId notifier_id_;
  views::View* background_view_;  
  scoped_ptr<views::ImageButton> close_button_;
  scoped_ptr<views::ImageView> small_image_view_;
  views::ScrollView* scroller_;

  base::string16 accessible_name_;

  base::string16 display_source_;

  scoped_ptr<views::Painter> focus_painter_;

  DISALLOW_COPY_AND_ASSIGN(MessageView);
};

}  

#endif 

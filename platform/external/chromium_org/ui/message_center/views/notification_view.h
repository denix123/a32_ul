// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_VIEWS_NOTIFICATION_VIEW_H_
#define UI_MESSAGE_CENTER_VIEWS_NOTIFICATION_VIEW_H_

#include <vector>

#include "ui/message_center/message_center_export.h"
#include "ui/message_center/views/message_view.h"
#include "ui/views/view_targeter_delegate.h"

namespace views {
class ProgressBar;
}

namespace message_center {

class BoundedLabel;
class MessageCenter;
class MessageCenterController;
class NotificationButton;
class NotificationView;
class PaddedButton;

class MESSAGE_CENTER_EXPORT NotificationView
    : public MessageView,
      public views::ViewTargeterDelegate,
      public MessageViewController {
 public:
  
  
  
  
  
  
  
  static NotificationView* Create(MessageCenterController* controller,
                                  const Notification& notification,
                                  bool top_level);
  virtual ~NotificationView();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual int GetHeightForWidth(int width) const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void ScrollRectToVisible(const gfx::Rect& rect) OVERRIDE;
  virtual gfx::NativeCursor GetCursor(const ui::MouseEvent& event) OVERRIDE;

  
  virtual void UpdateWithNotification(
      const Notification& notification) OVERRIDE;
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void ClickOnNotification(const std::string& notification_id) OVERRIDE;
  virtual void RemoveNotification(const std::string& notification_id,
                                  bool by_user) OVERRIDE;

  void set_controller(MessageCenterController* controller) {
    controller_ = controller;
  }

 protected:
  NotificationView(MessageCenterController* controller,
                   const Notification& notification);

 private:
  FRIEND_TEST_ALL_PREFIXES(NotificationViewTest, CreateOrUpdateTest);
  FRIEND_TEST_ALL_PREFIXES(NotificationViewTest, TestLineLimits);
  FRIEND_TEST_ALL_PREFIXES(NotificationViewTest, UpdateButtonsStateTest);
  FRIEND_TEST_ALL_PREFIXES(NotificationViewTest, UpdateButtonCountTest);

  friend class NotificationViewTest;

  
  virtual views::View* TargetForRect(views::View* root,
                                     const gfx::Rect& rect) OVERRIDE;

  void CreateOrUpdateViews(const Notification& notification);
  void SetAccessibleName(const Notification& notification);

  void CreateOrUpdateTitleView(const Notification& notification);
  void CreateOrUpdateMessageView(const Notification& notification);
  void CreateOrUpdateContextMessageView(const Notification& notification);
  void CreateOrUpdateProgressBarView(const Notification& notification);
  void CreateOrUpdateListItemViews(const Notification& notification);
  void CreateOrUpdateIconView(const Notification& notification);
  void CreateOrUpdateImageView(const Notification& notification);
  void CreateOrUpdateActionButtonViews(const Notification& notification);

  int GetMessageLineLimit(int title_lines, int width) const;
  int GetMessageHeight(int width, int limit) const;

  MessageCenterController* controller_;  

  
  bool clickable_;

  
  views::View* top_view_;
  BoundedLabel* title_view_;
  BoundedLabel* message_view_;
  BoundedLabel* context_message_view_;
  std::vector<views::View*> item_views_;
  views::View* icon_view_;
  views::View* bottom_view_;
  views::View* image_view_;
  views::ProgressBar* progress_bar_view_;
  std::vector<NotificationButton*> action_buttons_;
  std::vector<views::View*> separators_;

  DISALLOW_COPY_AND_ASSIGN(NotificationView);
};

}  

#endif 

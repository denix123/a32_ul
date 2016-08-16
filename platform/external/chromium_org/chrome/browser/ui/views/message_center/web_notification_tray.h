// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_MESSAGE_CENTER_WEB_NOTIFICATION_TRAY_H_
#define CHROME_BROWSER_UI_VIEWS_MESSAGE_CENTER_WEB_NOTIFICATION_TRAY_H_

#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_member.h"
#include "chrome/browser/status_icons/status_icon_menu_model.h"
#include "chrome/browser/status_icons/status_icon_observer.h"
#include "chrome/browser/ui/views/message_center/message_center_widget_delegate.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "ui/base/models/simple_menu_model.h"
#include "ui/gfx/rect.h"
#include "ui/message_center/message_center_tray.h"
#include "ui/message_center/message_center_tray_delegate.h"
#include "ui/views/widget/widget_observer.h"

#if defined(OS_WIN)
#include "base/threading/thread.h"
#endif

class PrefService;
class StatusIcon;

namespace message_center {
class MessageCenter;
class MessagePopupCollection;
}

namespace views {
class Widget;
}

namespace message_center {

struct PositionInfo;

class DesktopPopupAlignmentDelegate;
class MessageCenterWidgetDelegate;

class WebNotificationTray : public message_center::MessageCenterTrayDelegate,
                            public StatusIconObserver,
                            public base::SupportsWeakPtr<WebNotificationTray>,
                            public StatusIconMenuModel::Delegate {
 public:
  explicit WebNotificationTray(PrefService* local_state);
  virtual ~WebNotificationTray();

  message_center::MessageCenter* message_center();

  
  virtual bool ShowPopups() OVERRIDE;
  virtual void HidePopups() OVERRIDE;
  virtual bool ShowMessageCenter() OVERRIDE;
  virtual void HideMessageCenter() OVERRIDE;
  virtual void OnMessageCenterTrayChanged() OVERRIDE;
  virtual bool ShowNotifierSettings() OVERRIDE;
  virtual bool IsContextMenuEnabled() const OVERRIDE;

  
  virtual void OnStatusIconClicked() OVERRIDE;
#if defined(OS_WIN)
  virtual void OnBalloonClicked() OVERRIDE;

  
  
  void DisplayFirstRunBalloon();

  void EnforceStatusIconVisible();
#endif

  
  virtual void ExecuteCommand(int command_id, int event_flags) OVERRIDE;

  
  void UpdateStatusIcon();
  void SendHideMessageCenter();
  void MarkMessageCenterHidden();

  
  gfx::Point mouse_click_point() { return mouse_click_point_; }
  virtual MessageCenterTray* GetMessageCenterTray() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(WebNotificationTrayTest, WebNotifications);
  FRIEND_TEST_ALL_PREFIXES(WebNotificationTrayTest, WebNotificationPopupBubble);
  FRIEND_TEST_ALL_PREFIXES(WebNotificationTrayTest,
                           ManyMessageCenterNotifications);
  FRIEND_TEST_ALL_PREFIXES(WebNotificationTrayTest, ManyPopupNotifications);
  FRIEND_TEST_ALL_PREFIXES(WebNotificationTrayTest, ManuallyCloseMessageCenter);
  FRIEND_TEST_ALL_PREFIXES(WebNotificationTrayTest, StatusIconBehavior);

  PositionInfo GetPositionInfo();

  void CreateStatusIcon(const gfx::ImageSkia& image,
                        const base::string16& tool_tip);
  void DestroyStatusIcon();
  void AddQuietModeMenu(StatusIcon* status_icon);
  MessageCenterWidgetDelegate* GetMessageCenterWidgetDelegateForTest();

#if defined(OS_WIN)
  
  
  
  scoped_ptr<BooleanPrefMember> did_force_tray_visible_;
#endif

  MessageCenterWidgetDelegate* message_center_delegate_;
  scoped_ptr<message_center::MessagePopupCollection> popup_collection_;
  scoped_ptr<message_center::DesktopPopupAlignmentDelegate> alignment_delegate_;

  StatusIcon* status_icon_;
  StatusIconMenuModel* status_icon_menu_;
  scoped_ptr<MessageCenterTray> message_center_tray_;
  gfx::Point mouse_click_point_;

  bool should_update_tray_content_;
  bool last_quiet_mode_state_;
  base::string16 title_;

  DISALLOW_COPY_AND_ASSIGN(WebNotificationTray);
};

}  

#endif  

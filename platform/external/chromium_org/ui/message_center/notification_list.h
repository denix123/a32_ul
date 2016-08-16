// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_NOTIFICATION_LIST_H_
#define UI_MESSAGE_CENTER_NOTIFICATION_LIST_H_

#include <list>
#include <set>
#include <string>

#include "base/gtest_prod_util.h"
#include "ui/message_center/message_center_export.h"
#include "ui/message_center/notification_blocker.h"
#include "ui/message_center/notification_types.h"

namespace base {
class DictionaryValue;
class TimeDelta;
}

namespace gfx {
class Image;
}

namespace message_center {

namespace test {
class NotificationListTest;
}

class Notification;
class NotificationDelegate;
struct NotifierId;

struct MESSAGE_CENTER_EXPORT ComparePriorityTimestampSerial {
  bool operator()(Notification* n1, Notification* n2);
};

struct CompareTimestampSerial {
  bool operator()(Notification* n1, Notification* n2);
};

class MESSAGE_CENTER_EXPORT NotificationList {
 public:
  
  
  typedef std::set<Notification*, ComparePriorityTimestampSerial> Notifications;

  
  
  typedef std::set<Notification*, CompareTimestampSerial> PopupNotifications;

  explicit NotificationList();
  virtual ~NotificationList();

  
  
  
  void SetMessageCenterVisible(bool visible,
                               std::set<std::string>* updated_ids);

  void AddNotification(scoped_ptr<Notification> notification);

  void UpdateNotificationMessage(const std::string& old_id,
                                 scoped_ptr<Notification> new_notification);

  void RemoveNotification(const std::string& id);

  Notifications GetNotificationsByNotifierId(const NotifierId& notifier_id);

  
  bool SetNotificationIcon(const std::string& notification_id,
                           const gfx::Image& image);

  
  bool SetNotificationImage(const std::string& notification_id,
                            const gfx::Image& image);

  
  bool SetNotificationButtonIcon(const std::string& notification_id,
                                 int button_index,
                                 const gfx::Image& image);

  
  
  bool HasNotificationOfType(const std::string& id,
                             const NotificationType type);

  
  
  bool HasPopupNotifications(const NotificationBlockers& blockers);

  
  
  
  
  
  
  PopupNotifications GetPopupNotifications(
      const NotificationBlockers& blockers,
      std::list<std::string>* blocked_ids);

  
  
  void MarkSinglePopupAsShown(const std::string& id,
                              bool mark_notification_as_read);

  
  void MarkSinglePopupAsDisplayed(const std::string& id);

  NotificationDelegate* GetNotificationDelegate(const std::string& id);

  bool quiet_mode() const { return quiet_mode_; }

  
  void SetQuietMode(bool quiet_mode);

  
  
  void EnterQuietModeWithExpire(const base::TimeDelta& expires_in);

  
  
  Notification* GetNotificationById(const std::string& id);

  
  
  Notifications GetVisibleNotifications(
      const NotificationBlockers& blockers) const;
  size_t NotificationCount(const NotificationBlockers& blockers) const;
  size_t UnreadCount(const NotificationBlockers& blockers) const;

  bool is_message_center_visible() const { return message_center_visible_; }

 private:
  friend class NotificationListTest;
  FRIEND_TEST_ALL_PREFIXES(NotificationListTest,
                           TestPushingShownNotification);

  
  Notifications::iterator GetNotification(const std::string& id);

  void EraseNotification(Notifications::iterator iter);

  void PushNotification(scoped_ptr<Notification> notification);

  Notifications notifications_;
  bool message_center_visible_;
  bool quiet_mode_;

  DISALLOW_COPY_AND_ASSIGN(NotificationList);
};

}  

#endif 

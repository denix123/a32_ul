// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_NOTIFICATION_H_
#define UI_MESSAGE_CENTER_NOTIFICATION_H_

#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "base/time/time.h"
#include "base/values.h"
#include "ui/gfx/image/image.h"
#include "ui/message_center/message_center_export.h"
#include "ui/message_center/notification_delegate.h"
#include "ui/message_center/notification_types.h"
#include "ui/message_center/notifier_settings.h"

namespace message_center {

struct MESSAGE_CENTER_EXPORT NotificationItem {
  base::string16 title;
  base::string16 message;

  NotificationItem(const base::string16& title, const base::string16& message);
};

struct MESSAGE_CENTER_EXPORT ButtonInfo {
  base::string16 title;
  gfx::Image icon;

  ButtonInfo(const base::string16& title);
};

class MESSAGE_CENTER_EXPORT RichNotificationData {
 public:
  RichNotificationData();
  RichNotificationData(const RichNotificationData& other);
  ~RichNotificationData();

  int priority;
  bool never_timeout;
  base::Time timestamp;
  base::string16 context_message;
  gfx::Image image;
  gfx::Image small_image;
  std::vector<NotificationItem> items;
  int progress;
  std::vector<ButtonInfo> buttons;
  bool should_make_spoken_feedback_for_popup_updates;
  bool clickable;
};

class MESSAGE_CENTER_EXPORT Notification {
 public:
  Notification(NotificationType type,
               const std::string& id,
               const base::string16& title,
               const base::string16& message,
               const gfx::Image& icon,
               const base::string16& display_source,
               const NotifierId& notifier_id,
               const RichNotificationData& optional_fields,
               NotificationDelegate* delegate);

  Notification(const Notification& other);

  virtual ~Notification();

  
  
  void CopyState(Notification* base);

  NotificationType type() const { return type_; }
  void set_type(NotificationType type) { type_ = type; }

  
  
  
  
  
  const std::string& id() const { return id_; }

  const base::string16& title() const { return title_; }
  void set_title(const base::string16& title) { title_ = title; }

  const base::string16& message() const { return message_; }
  void set_message(const base::string16& message) { message_ = message; }

  
  const base::string16& display_source() const { return display_source_; }

  const NotifierId& notifier_id() const { return notifier_id_; }

  void set_profile_id(const std::string& profile_id) {
    notifier_id_.profile_id = profile_id;
  }

  
  int priority() const { return optional_fields_.priority; }
  void set_priority(int priority) { optional_fields_.priority = priority; }

  base::Time timestamp() const { return optional_fields_.timestamp; }
  void set_timestamp(const base::Time& timestamp) {
    optional_fields_.timestamp = timestamp;
  }

  const base::string16& context_message() const {
    return optional_fields_.context_message;
  }
  void set_context_message(const base::string16& context_message) {
    optional_fields_.context_message = context_message;
  }

  const std::vector<NotificationItem>& items() const {
    return optional_fields_.items;
  }
  void set_items(const std::vector<NotificationItem>& items) {
    optional_fields_.items = items;
  }

  int progress() const { return optional_fields_.progress; }
  void set_progress(int progress) { optional_fields_.progress = progress; }
  

  
  const gfx::Image& icon() const { return icon_; }
  void set_icon(const gfx::Image& icon) { icon_ = icon; }

  const gfx::Image& image() const { return optional_fields_.image; }
  void set_image(const gfx::Image& image) { optional_fields_.image = image; }

  const gfx::Image& small_image() const { return optional_fields_.small_image; }
  void set_small_image(const gfx::Image& image) {
    optional_fields_.small_image = image;
  }

  
  const std::vector<ButtonInfo>& buttons() const {
    return optional_fields_.buttons;
  }
  void set_buttons(const std::vector<ButtonInfo>& buttons) {
    optional_fields_.buttons = buttons;
  }
  void SetButtonIcon(size_t index, const gfx::Image& icon);

  bool shown_as_popup() const { return shown_as_popup_; }
  void set_shown_as_popup(bool shown_as_popup) {
    shown_as_popup_ = shown_as_popup;
  }

  
  bool IsRead() const;
  void set_is_read(bool read) { is_read_ = read; }

  
  
  unsigned serial_number() { return serial_number_; }

  
  
  void set_never_timeout(bool never_timeout) {
    optional_fields_.never_timeout = never_timeout;
  }

  bool never_timeout() const { return optional_fields_.never_timeout; }

  bool clickable() const { return optional_fields_.clickable; }
  void set_clickable(bool clickable) {
    optional_fields_.clickable = clickable;
  }

  NotificationDelegate* delegate() const { return delegate_.get(); }

  const RichNotificationData& rich_notification_data() const {
    return optional_fields_;
  }

  
  
  void SetSystemPriority();

  
  void Display() const { delegate()->Display(); }
  void Error() const { delegate()->Error(); }
  bool HasClickedListener() const { return delegate()->HasClickedListener(); }
  void Click() const { delegate()->Click(); }
  void ButtonClick(int index) const { delegate()->ButtonClick(index); }
  void Close(bool by_user) const { delegate()->Close(by_user); }

  
  
  static scoped_ptr<Notification> CreateSystemNotification(
      const std::string& notification_id,
      const base::string16& title,
      const base::string16& message,
      const gfx::Image& icon,
      const std::string& system_component_id,
      const base::Closure& click_callback);

 protected:
  Notification& operator=(const Notification& other);

  
  NotificationType type_;

  std::string id_;
  base::string16 title_;
  base::string16 message_;

  
  gfx::Image icon_;

  
  
  base::string16 display_source_;

 private:
  NotifierId notifier_id_;
  unsigned serial_number_;
  RichNotificationData optional_fields_;
  bool shown_as_popup_;  
  bool is_read_;  

  
  
  scoped_refptr<NotificationDelegate> delegate_;
};

}  

#endif  
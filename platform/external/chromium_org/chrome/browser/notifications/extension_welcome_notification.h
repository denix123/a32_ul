// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NOTIFICATIONS_EXTENSION_WELCOME_NOTIFICATION_H_
#define CHROME_BROWSER_NOTIFICATIONS_EXTENSION_WELCOME_NOTIFICATION_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_member.h"
#include "base/timer/timer.h"
#include "chrome/browser/prefs/pref_service_syncable_observer.h"
#include "components/keyed_service/core/keyed_service.h"
#include "ui/message_center/notifier_settings.h"

namespace base {
typedef Callback<void(void)> Closure;
}

namespace message_center {
class MessageCenter;
}

namespace tracked_objects {
class Location;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class Notification;
class Profile;

class ExtensionWelcomeNotification : public KeyedService,
                                     public PrefServiceSyncableObserver {
 public:
  
  class Delegate {
   public:
    Delegate() {}
    virtual ~Delegate() {}
    virtual message_center::MessageCenter* GetMessageCenter() = 0;
    virtual base::Time GetCurrentTime() = 0;
    virtual void PostTask(
        const tracked_objects::Location& from_here,
        const base::Closure& task) = 0;
   private:
    DISALLOW_COPY_AND_ASSIGN(Delegate);
  };

  
  static const int kRequestedShowTimeDays;

  
  static const char kChromeNowExtensionID[];

  virtual ~ExtensionWelcomeNotification();

  
  
  
  static ExtensionWelcomeNotification* Create(Profile* const profile);

  
  static ExtensionWelcomeNotification* Create(Profile* const profile,
                                              Delegate* const delegate);

  
  virtual void OnIsSyncingChanged() OVERRIDE;

  
  
  void ShowWelcomeNotificationIfNecessary(const Notification& notification);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* prefs);

 private:
  enum PopUpRequest { POP_UP_HIDDEN = 0, POP_UP_SHOWN = 1, };

  ExtensionWelcomeNotification(
      Profile* const profile,
      ExtensionWelcomeNotification::Delegate* const delegate);

  
  message_center::MessageCenter* GetMessageCenter() const;

  
  void ShowWelcomeNotification(const base::string16& display_source,
                               const PopUpRequest pop_up_request);

  
  void HideWelcomeNotification();

  
  bool UserHasDismissedWelcomeNotification() const;

  
  void OnWelcomeNotificationDismissedChanged();

  
  void StartExpirationTimer();

  
  void StopExpirationTimer();

  
  void ExpireWelcomeNotification();

  
  base::Time GetExpirationTimestamp() const;

  
  void SetExpirationTimestampFromNow();

  
  bool IsWelcomeNotificationExpired() const;

  
  BooleanPrefMember welcome_notification_dismissed_pref_;

  
  
  BooleanPrefMember welcome_notification_dismissed_local_pref_;

  
  message_center::NotifierId notifier_id_;

  
  Profile* profile_;

  
  std::string welcome_notification_id_;

  
  
  
  
  
  scoped_ptr<Notification> delayed_notification_;

  
  
  scoped_ptr<base::OneShotTimer<ExtensionWelcomeNotification> >
      expiration_timer_;

  
  
  scoped_ptr<Delegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionWelcomeNotification);
};

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NOTIFICATIONS_DESKTOP_NOTIFICATION_PROFILE_UTIL_H_
#define CHROME_BROWSER_NOTIFICATIONS_DESKTOP_NOTIFICATION_PROFILE_UTIL_H_

#include "base/macros.h"
#include "components/content_settings/core/common/content_settings.h"

class Profile;

class DesktopNotificationProfileUtil {
 public:
  
  static void ResetToDefaultContentSetting(Profile* profile);

  
  static void ClearSetting(
      Profile* profile, const ContentSettingsPattern& pattern);

  
  static void GrantPermission(Profile* profile, const GURL& origin);
  static void DenyPermission(Profile* profile, const GURL& origin);
  static void GetNotificationsSettings(
      Profile* profile, ContentSettingsForOneType* settings);
  static ContentSetting GetContentSetting(Profile* profile, const GURL& origin);
  static void UsePermission(Profile* profile, const GURL& origin);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(DesktopNotificationProfileUtil);
};

#endif  

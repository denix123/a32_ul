// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_NOTIFICATION_PROVIDER_NOTIFICATION_PROVIDER_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_NOTIFICATION_PROVIDER_NOTIFICATION_PROVIDER_API_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/extensions/api/notification_provider.h"
#include "extensions/browser/extension_function.h"
#include "ui/message_center/notification_types.h"

namespace extensions {

class NotificationProviderEventRouter {
 public:
  explicit NotificationProviderEventRouter(Profile* profile);
  virtual ~NotificationProviderEventRouter();

  void CreateNotification(
      const std::string& notification_provider_id,
      const std::string& sender_id,
      const std::string& notification_id,
      const api::notifications::NotificationOptions& options);
  void UpdateNotification(
      const std::string& notification_provider_id,
      const std::string& sender_id,
      const std::string& notificaiton_id,
      const api::notifications::NotificationOptions& options);
  void ClearNotification(const std::string& notification_provider_id,
                         const std::string& sender_id,
                         const std::string& notification_id);

 private:
  void Create(const std::string& notification_provider_id,
              const std::string& sender_id,
              const std::string& notification_id,
              const api::notifications::NotificationOptions& options);
  void Update(const std::string& notification_provider_id,
              const std::string& sender_id,
              const std::string& notification_id,
              const api::notifications::NotificationOptions& options);
  void Clear(const std::string& notification_provider_id,
             const std::string& sender_id,
             const std::string& notification_id);

  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(NotificationProviderEventRouter);
};

class NotificationProviderNotifyOnClearedFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  NotificationProviderNotifyOnClearedFunction();

 protected:
  virtual ~NotificationProviderNotifyOnClearedFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("notificationProvider.notifyOnCleared",
                             NOTIFICATIONPROVIDER_NOTIFYONCLEARED);

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class NotificationProviderNotifyOnClickedFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  NotificationProviderNotifyOnClickedFunction();

 protected:
  virtual ~NotificationProviderNotifyOnClickedFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("notificationProvider.notifyOnClicked",
                             NOTIFICATIONPROVIDER_NOTIFYONCLICKED);

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class NotificationProviderNotifyOnButtonClickedFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  NotificationProviderNotifyOnButtonClickedFunction();

 protected:
  virtual ~NotificationProviderNotifyOnButtonClickedFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("notificationProvider.notifyOnButtonClicked",
                             NOTIFICATIONPROVIDER_NOTIFYONBUTTONCLICKED);

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class NotificationProviderNotifyOnPermissionLevelChangedFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  NotificationProviderNotifyOnPermissionLevelChangedFunction();

 protected:
  virtual ~NotificationProviderNotifyOnPermissionLevelChangedFunction();

 private:
  DECLARE_EXTENSION_FUNCTION(
      "notificationProvider.notifyOnPermissionLevelChanged",
      NOTIFICATIONPROVIDER_NOTIFYONPERMISSIONLEVELCHANGED);

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class NotificationProviderNotifyOnShowSettingsFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  NotificationProviderNotifyOnShowSettingsFunction();

 protected:
  virtual ~NotificationProviderNotifyOnShowSettingsFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("notificationProvider.notifyOnShowSettings",
                             NOTIFICATIONPROVIDER_NOTIFYONSHOWSETTINGS);

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class NotificationProviderGetNotifierFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  NotificationProviderGetNotifierFunction();

 protected:
  virtual ~NotificationProviderGetNotifierFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("notificationProvider.getNotifier",
                             NOTIFICATIONPROVIDER_GETNOTIFIER);

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

class NotificationProviderGetAllNotifiersFunction
    : public ChromeUIThreadExtensionFunction {
 public:
  NotificationProviderGetAllNotifiersFunction();

 protected:
  virtual ~NotificationProviderGetAllNotifiersFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("notificationProvider.getAllNotifiers",
                             NOTIFICATIONPROVIDER_GETALLNOTIFIERS);

  
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

}  

#endif  

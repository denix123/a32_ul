// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_NOTIFICATION_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_NOTIFICATION_MANAGER_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/file_system_provider/notification_manager_interface.h"
#include "chrome/browser/chromeos/file_system_provider/provided_file_system_info.h"
#include "chrome/browser/extensions/app_icon_loader.h"

class Profile;

namespace gfx {
class Image;
class ImageSkia;
}  

namespace message_center {
class Notification;
}  

namespace chromeos {
namespace file_system_provider {

class NotificationManager : public NotificationManagerInterface,
                            public extensions::AppIconLoader::Delegate {
 public:
  NotificationManager(Profile* profile,
                      const ProvidedFileSystemInfo& file_system_info);
  virtual ~NotificationManager();

  
  virtual void ShowUnresponsiveNotification(
      int id,
      const NotificationCallback& callback) OVERRIDE;
  virtual void HideUnresponsiveNotification(int id) OVERRIDE;

  
  void OnButtonClick(int button_index);

  
  void OnError();

  
  void OnClose();

  
  virtual void SetAppImage(const std::string& id,
                           const gfx::ImageSkia& image) OVERRIDE;

 private:
  typedef std::map<int, NotificationCallback> CallbackMap;

  
  scoped_ptr<message_center::Notification> CreateNotification();

  
  
  void OnNotificationResult(NotificationResult result);

  Profile* profile_;  
  ProvidedFileSystemInfo file_system_info_;
  CallbackMap callbacks_;
  scoped_ptr<extensions::AppIconLoader> icon_loader_;
  scoped_ptr<gfx::Image> extension_icon_;

  DISALLOW_COPY_AND_ASSIGN(NotificationManager);
};

}  
}  

#endif  

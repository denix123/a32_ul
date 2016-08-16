// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_APPS_QUIT_WITH_APPS_CONTROLLER_MAC_H_
#define CHROME_BROWSER_UI_COCOA_APPS_QUIT_WITH_APPS_CONTROLLER_MAC_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/notifications/notification.h"

class PrefRegistrySimple;

class QuitWithAppsController : public NotificationDelegate {
 public:
  static const char kQuitWithAppsNotificationID[];

  QuitWithAppsController();

  
  virtual void Display() OVERRIDE;
  virtual void Error() OVERRIDE;
  virtual void Close(bool by_user) OVERRIDE;
  virtual void Click() OVERRIDE;
  virtual void ButtonClick(int button_index) OVERRIDE;
  virtual content::WebContents* GetWebContents() const OVERRIDE;
  virtual std::string id() const OVERRIDE;

  
  
  bool ShouldQuit();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  virtual ~QuitWithAppsController();

  scoped_ptr<Notification> notification_;

  
  bool suppress_for_session_;

  DISALLOW_COPY_AND_ASSIGN(QuitWithAppsController);
};

#endif  

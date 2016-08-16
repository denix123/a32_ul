// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_KIOSK_APP_MENU_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_KIOSK_APP_MENU_HANDLER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/app_mode/kiosk_app_manager.h"
#include "chrome/browser/chromeos/app_mode/kiosk_app_manager_observer.h"
#include "chrome/browser/ui/webui/chromeos/login/network_state_informer.h"
#include "content/public/browser/web_ui_message_handler.h"

namespace chromeos {

class KioskAppMenuHandler
    : public content::WebUIMessageHandler,
      public KioskAppManagerObserver,
      public NetworkStateInformer::NetworkStateInformerObserver {
 public:
  explicit KioskAppMenuHandler(
      const scoped_refptr<NetworkStateInformer>& network_state_informer);
  virtual ~KioskAppMenuHandler();

  void GetLocalizedStrings(base::DictionaryValue* localized_strings);

  
  virtual void RegisterMessages() OVERRIDE;

  
  static bool EnableNewKioskUI();

 private:
  
  void SendKioskApps();

  
  void HandleInitializeKioskApps(const base::ListValue* args);
  void HandleKioskAppsLoaded(const base::ListValue* args);
  void HandleCheckKioskAppLaunchError(const base::ListValue* args);

  
  virtual void OnKioskAppsSettingsChanged() OVERRIDE;
  virtual void OnKioskAppDataChanged(const std::string& app_id) OVERRIDE;

  
  virtual void UpdateState(ErrorScreenActor::ErrorReason reason) OVERRIDE;

  
  bool is_webui_initialized_;

  scoped_refptr<NetworkStateInformer> network_state_informer_;

  base::WeakPtrFactory<KioskAppMenuHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(KioskAppMenuHandler);
};

}  

#endif  

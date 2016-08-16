// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_SIGNIN_LOGIN_UI_SERVICE_H_
#define CHROME_BROWSER_UI_WEBUI_SIGNIN_LOGIN_UI_SERVICE_H_

#include "base/basictypes.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "components/keyed_service/core/keyed_service.h"

class Browser;
class Profile;

class LoginUIService : public KeyedService {
 public:
  
  
  class LoginUI {
   public:
    
    virtual void FocusUI() = 0;

    
    
    virtual void CloseUI() = 0;
   protected:
    virtual ~LoginUI() {}
  };

  
  class Observer {
   public:
    
    
    virtual void OnLoginUIShown(LoginUI* ui) {}

    
    
    virtual void OnLoginUIClosed(LoginUI* ui) {}

    
    
    
    virtual void OnSyncConfirmationUIClosed(bool configure_sync_first) {}

    
    virtual void OnUntrustedLoginUIShown() {}

   protected:
    virtual ~Observer() {}
  };

  explicit LoginUIService(Profile* profile);
  virtual ~LoginUIService();

  
  LoginUI* current_login_ui() const {
    return ui_;
  }

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  void SetLoginUI(LoginUI* ui);

  
  
  void LoginUIClosed(LoginUI* ui);

  
  void SyncConfirmationUIClosed(bool configure_sync_first);

  
  void UntrustedLoginUIShown();

  
  
  
  void ShowLoginPopup();

  
  void DisplayLoginResult(Browser* browser, const base::string16& message);

  
  const base::string16& GetLastLoginResult();

 private:
  
  LoginUI* ui_;
  Profile* profile_;

  
  ObserverList<Observer> observer_list_;

  base::string16 last_login_result_;

  DISALLOW_COPY_AND_ASSIGN(LoginUIService);
};

#endif  

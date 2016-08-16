// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_SUPERVISED_USER_IMPORT_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_SUPERVISED_USER_IMPORT_HANDLER_H_

#include "base/callback_list.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/supervised_user/supervised_user_sync_service_observer.h"
#include "chrome/browser/ui/webui/options/options_ui.h"
#include "components/signin/core/browser/signin_error_controller.h"

namespace base {
class DictionaryValue;
class ListValue;
}

namespace options {

class SupervisedUserImportHandler : public OptionsPageUIHandler,
                                    public SupervisedUserSyncServiceObserver,
                                    public SigninErrorController::Observer {
 public:
  typedef base::CallbackList<void(const std::string&, const std::string&)>
      CallbackList;

  SupervisedUserImportHandler();
  virtual ~SupervisedUserImportHandler();

  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;
  virtual void InitializeHandler() OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void OnSupervisedUserAcknowledged(
      const std::string& supervised_user_id) OVERRIDE {}
  virtual void OnSupervisedUsersSyncingStopped() OVERRIDE {}
  virtual void OnSupervisedUsersChanged() OVERRIDE;

  
  virtual void OnErrorChanged() OVERRIDE;

 private:
  
  
  void FetchSupervisedUsers();

  
  
  
  
  void RequestSupervisedUserImportUpdate(const base::ListValue* args);

  
  
  
  
  
  
  
  
  
  
  void SendExistingSupervisedUsers(const base::DictionaryValue* dict);

  
  
  void ClearSupervisedUsersAndShowError();

  bool IsAccountConnected() const;
  bool HasAuthError() const;

  
  
  void OnSharedSettingChanged(const std::string& supervised_user_id,
                              const std::string& key);

  scoped_ptr<CallbackList::Subscription> subscription_;

  ScopedObserver<SigninErrorController, SupervisedUserImportHandler> observer_;

  base::WeakPtrFactory<SupervisedUserImportHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserImportHandler);
};

}  

#endif  

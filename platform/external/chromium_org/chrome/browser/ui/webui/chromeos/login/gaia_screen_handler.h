// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_GAIA_SCREEN_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_GAIA_SCREEN_HANDLER_H_

#include <string>

#include "base/basictypes.h"
#include "base/command_line.h"
#include "base/memory/ref_counted.h"
#include "chrome/browser/chromeos/login/screens/core_oobe_actor.h"
#include "chrome/browser/ui/webui/chromeos/login/network_state_informer.h"
#include "net/base/net_errors.h"

namespace policy {
class ConsumerManagementService;
}

namespace chromeos {

class SigninScreenHandler;

struct GaiaContext {
  GaiaContext();

  
  bool force_reload;

  
  bool is_local;

  
  bool password_changed;

  
  bool show_users;

  
  bool use_offline;

  
  bool has_users;

  
  std::string email;

  
  bool is_enrolling_consumer_management;
};

class GaiaScreenHandler : public BaseScreenHandler {
 public:
  enum FrameState {
    FRAME_STATE_UNKNOWN = 0,
    FRAME_STATE_LOADING,
    FRAME_STATE_LOADED,
    FRAME_STATE_ERROR
  };

  GaiaScreenHandler(
      CoreOobeActor* core_oobe_actor,
      const scoped_refptr<NetworkStateInformer>& network_state_informer,
      policy::ConsumerManagementService* consumer_management);
  virtual ~GaiaScreenHandler();

  void LoadGaia(const GaiaContext& context);
  void UpdateGaia(const GaiaContext& context);

  
  
  
  void ReloadGaia(bool force_reload);

  FrameState frame_state() const { return frame_state_; }
  net::Error frame_error() const { return frame_error_; }

 private:
  
  friend class SigninScreenHandler;

  
  virtual void DeclareLocalizedValues(LocalizedValuesBuilder* builder) OVERRIDE;
  virtual void Initialize() OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

  
  void HandleFrameLoadingCompleted(int status);
  void HandleCompleteAuthentication(const std::string& email,
                                    const std::string& password,
                                    const std::string& auth_code);
  void HandleCompleteLogin(const std::string& typed_email,
                           const std::string& password,
                           bool using_saml);

  void HandleUsingSAMLAPI();
  void HandleScrapedPasswordCount(int password_count);
  void HandleScrapedPasswordVerificationFailed();

  void HandleGaiaUIReady();

  
  void OnSetOwnerDone(const std::string& typed_email,
                      const std::string& password,
                      bool using_saml,
                      bool success);

  
  void DoCompleteLogin(const std::string& typed_email,
                       const std::string& password,
                       bool using_saml);

  
  void PopulateEmail(const std::string& user_id);

  
  void PasswordChangedFor(const std::string& user_id);

  
  void StartClearingCookies(const base::Closure& on_clear_callback);
  void OnCookiesCleared(const base::Closure& on_clear_callback);

  
  void StartClearingDnsCache();
  void OnDnsCleared();

  
  virtual void ShowSigninScreenForCreds(const std::string& username,
                                        const std::string& password);
  
  void SubmitLoginFormForTest();

  
  
  void SetSAMLPrincipalsAPIUsed(bool api_used);

  void ShowGaia(bool is_enrolling_consumer_management);

  
  void ShowGaiaScreenIfReady();

  
  
  void MaybePreloadAuthExtension();

  
  
  
  
  
  void LoadAuthExtension(bool force, bool silent_load, bool offline);

  
  
  void UpdateState(ErrorScreenActor::ErrorReason reason);

  
  void SetSigninScreenHandler(SigninScreenHandler* handler);

  SigninScreenHandlerDelegate* Delegate();

  
  FrameState frame_state_;

  
  net::Error frame_error_;

  
  scoped_refptr<NetworkStateInformer> network_state_informer_;

  
  policy::ConsumerManagementService* consumer_management_;

  CoreOobeActor* core_oobe_actor_;

  
  std::string populated_email_;

  
  std::set<std::string> password_changed_for_;

  
  bool dns_cleared_;

  
  bool dns_clear_task_running_;

  
  bool cookies_cleared_;

  
  bool focus_stolen_;

  
  bool gaia_silent_load_;

  
  std::string gaia_silent_load_network_;

  
  
  bool using_saml_api_;

  
  bool is_enrolling_consumer_management_;

  
  std::string test_user_;
  std::string test_pass_;
  bool test_expects_complete_login_;

  
  
  
  
  SigninScreenHandler* signin_screen_handler_;

  base::WeakPtrFactory<GaiaScreenHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(GaiaScreenHandler);
};

}  

#endif  

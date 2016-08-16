// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_ENROLLMENT_SCREEN_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_ENROLLMENT_SCREEN_HANDLER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "chrome/browser/browsing_data/browsing_data_remover.h"
#include "chrome/browser/chromeos/login/enrollment/enrollment_screen_actor.h"
#include "chrome/browser/chromeos/login/ui/webui_login_view.h"
#include "chrome/browser/ui/webui/chromeos/login/base_screen_handler.h"
#include "chrome/browser/ui/webui/chromeos/login/network_state_informer.h"

namespace policy {
class PolicyOAuth2TokenFetcher;
}

namespace chromeos {

class AuthenticatedUserEmailRetriever;

class EnrollmentScreenHandler
    : public BaseScreenHandler,
      public EnrollmentScreenActor,
      public BrowsingDataRemover::Observer,
      public NetworkStateInformer::NetworkStateInformerObserver,
      public WebUILoginView::FrameObserver {
 public:
  EnrollmentScreenHandler(
      const scoped_refptr<NetworkStateInformer>& network_state_informer,
      ErrorScreenActor* error_screen_actor);
  virtual ~EnrollmentScreenHandler();

  
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void SetParameters(Controller* controller,
                             EnrollmentMode enrollment_mode,
                             const std::string& management_domain) OVERRIDE;
  virtual void PrepareToShow() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual void FetchOAuthToken() OVERRIDE;
  virtual void ResetAuth(const base::Closure& callback) OVERRIDE;
  virtual void ShowSigninScreen() OVERRIDE;
  virtual void ShowEnrollmentSpinnerScreen() OVERRIDE;
  virtual void ShowLoginSpinnerScreen() OVERRIDE;
  virtual void ShowAuthError(const GoogleServiceAuthError& error) OVERRIDE;
  virtual void ShowEnrollmentStatus(policy::EnrollmentStatus status) OVERRIDE;
  virtual void ShowUIError(UIError error_code) OVERRIDE;

  
  virtual void Initialize() OVERRIDE;
  virtual void DeclareLocalizedValues(LocalizedValuesBuilder* builder) OVERRIDE;

  
  virtual void OnBrowsingDataRemoverDone() OVERRIDE;

  
  virtual void UpdateState(ErrorScreenActor::ErrorReason reason) OVERRIDE;

  
  virtual void OnFrameError(const std::string& frame_unique_name) OVERRIDE;

 private:
  
  void HandleRetrieveAuthenticatedUserEmail(double attempt_token);
  void HandleClose(const std::string& reason);
  void HandleCompleteLogin(const std::string& user);
  void HandleRetry();
  void HandleFrameLoadingCompleted(int status);

  void SetupAndShowOfflineMessage(NetworkStateInformer::State state,
                                  ErrorScreenActor::ErrorReason reason);
  void HideOfflineMessage(NetworkStateInformer::State state,
                          ErrorScreenActor::ErrorReason reason);

  net::Error frame_error() const { return frame_error_; }
  
  void ShowStep(const char* step);

  
  void ShowError(int message_id, bool retry);

  
  void ShowErrorMessage(const std::string& message, bool retry);

  
  void ShowWorking(int message_id);

  
  void OnTokenFetched(const std::string& token,
                      const GoogleServiceAuthError& error);

  
  void DoShow();

  
  OobeUI::Screen GetCurrentScreen() const;

  
  bool IsOnEnrollmentScreen() const;

  
  
  bool IsEnrollmentScreenHiddenByError() const;

  
  Controller* controller_;

  bool show_on_init_;

  
  EnrollmentMode enrollment_mode_;

  
  std::string management_domain_;

  
  bool enrollment_failed_once_;

  
  
  scoped_ptr<policy::PolicyOAuth2TokenFetcher> oauth_fetcher_;

  
  BrowsingDataRemover* browsing_data_remover_;

  
  std::vector<base::Closure> auth_reset_callbacks_;

  
  scoped_ptr<AuthenticatedUserEmailRetriever> email_retriever_;

  
  net::Error frame_error_;

  
  scoped_refptr<NetworkStateInformer> network_state_informer_;

  ErrorScreenActor* error_screen_actor_;

  base::WeakPtrFactory<EnrollmentScreenHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EnrollmentScreenHandler);
};

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_FORM_MANAGER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_FORM_MANAGER_H_

#include <string>
#include <vector>

#include "build/build_config.h"

#include "base/stl_util.h"
#include "components/autofill/core/browser/field_types.h"
#include "components/autofill/core/common/password_form.h"
#include "components/password_manager/core/browser/password_manager_driver.h"
#include "components/password_manager/core/browser/password_store.h"
#include "components/password_manager/core/browser/password_store_consumer.h"

namespace content {
class WebContents;
}  

namespace password_manager {

class PasswordManager;
class PasswordManagerClient;

class PasswordFormManager : public PasswordStoreConsumer {
 public:
  
  
  
  
  PasswordFormManager(PasswordManager* password_manager,
                      PasswordManagerClient* client,
                      PasswordManagerDriver* driver,
                      const autofill::PasswordForm& observed_form,
                      bool ssl_valid);
  virtual ~PasswordFormManager();

  
  
  
  
  enum MatchResultFlags {
    RESULT_NO_MATCH = 0,
    RESULT_MANDATORY_ATTRIBUTES_MATCH = 1 << 0,  
    RESULT_ACTION_MATCH = 1 << 1,                
    RESULT_COMPLETE_MATCH =
        RESULT_MANDATORY_ATTRIBUTES_MATCH | RESULT_ACTION_MATCH
  };
  
  
  
  typedef int MatchResultMask;

  enum OtherPossibleUsernamesAction {
    ALLOW_OTHER_POSSIBLE_USERNAMES,
    IGNORE_OTHER_POSSIBLE_USERNAMES
  };

  
  
  MatchResultMask DoesManage(const autofill::PasswordForm& form) const;

  
  
  
  
  void FetchMatchingLoginsFromPasswordStore(
      PasswordStore::AuthorizationPromptPolicy prompt_policy);

  
  
  
  
  
  
  
  
  
  
  
  
  bool HasCompletedMatching();

  
  bool IsBlacklisted();

  
  
  
  bool IsNewLogin();

  
  
  
  bool IsPendingCredentialsPublicSuffixMatch();

  
  
  bool HasValidPasswordForm();

  
  
  bool HasGeneratedPassword();
  void SetHasGeneratedPassword();

  
  
  void OnRequestDone(const std::vector<autofill::PasswordForm*>& result);

  virtual void OnGetPasswordStoreResults(
      const std::vector<autofill::PasswordForm*>& results) OVERRIDE;

  
  
  
  void PermanentlyBlacklist();

  
  
  void SetUseAdditionalPasswordAuthentication(
      bool use_additional_authentication);

  
  
  
  
  
  
  
  void ProvisionallySave(const autofill::PasswordForm& credentials,
                         OtherPossibleUsernamesAction action);

  
  
  
  
  void Save();

  
  
  void SubmitPassed();
  void SubmitFailed();

  
  const base::string16& associated_username() const {
    return pending_credentials_.username_value;
  }

  
  const autofill::PasswordForm& pending_credentials() const {
    return pending_credentials_;
  }

  
  const autofill::PasswordFormMap& best_matches() const {
    return best_matches_;
  }

  const autofill::PasswordForm* preferred_match() const {
    return preferred_match_;
  }

  
  const std::string& realm() const {
    return pending_credentials_.signon_realm;
  }

 private:
  friend class PasswordFormManagerTest;

  
  
  
  
  
  
  enum ManagerAction {
    kManagerActionNone = 0,
    kManagerActionAutofilled,
    kManagerActionBlacklisted,
    kManagerActionMax
  };

  
  
  
  
  
  
  
  
  
  enum UserAction {
    kUserActionNone = 0,
    kUserActionChoose,
    kUserActionChoosePslMatch,
    kUserActionOverridePassword,
    kUserActionOverrideUsernameAndPassword,
    kUserActionMax
  };

  
  enum SubmitResult {
    kSubmitResultNotSubmitted = 0,
    kSubmitResultFailed,
    kSubmitResultPassed,
    kSubmitResultMax
  };

  
  
  static const int kMaxNumActionsTaken = kManagerActionMax * kUserActionMax *
                                         kSubmitResultMax;

  
  
  bool ShouldIgnoreResult(const autofill::PasswordForm& form) const;

  
  
  
  
  void SaveAsNewLogin(bool reset_preferred_login);

  
  
  int ScoreResult(const autofill::PasswordForm& form) const;

  
  
  
  
  
  void UpdateLogin();

  
  
  
  void CheckForAccountCreationForm(const autofill::PasswordForm& pending,
                                   const autofill::PasswordForm& observed);

  
  
  
  void UpdatePreferredLoginState(PasswordStore* password_store);

  
  
  
  bool UpdatePendingCredentialsIfOtherPossibleUsername(
      const base::string16& username);

  
  
  int GetActionsTaken();

  
  
  void SanitizePossibleUsernames(autofill::PasswordForm* form);

  
  virtual void UploadPasswordForm(
      const autofill::FormData& form_data,
      const autofill::ServerFieldType& password_type);

  
  
  
  autofill::PasswordFormMap best_matches_;

  
  STLValueDeleter<autofill::PasswordFormMap> best_matches_deleter_;

  
  const autofill::PasswordForm observed_form_;

  
  
  std::vector<std::string> form_path_tokens_;

  
  
  autofill::PasswordForm pending_credentials_;

  
  
  bool is_new_login_;

  
  bool has_generated_password_;

  
  
  base::string16 selected_username_;

  
  const PasswordManager* const password_manager_;

  
  
  
  
  const autofill::PasswordForm* preferred_match_;

  typedef enum {
    PRE_MATCHING_PHASE,      
                             
    MATCHING_PHASE,          
                             
    POST_MATCHING_PHASE      
                             
  } PasswordFormManagerState;

  
  
  
  PasswordFormManagerState state_;

  
  PasswordManagerClient* client_;

  
  PasswordManagerDriver* driver_;

  
  
  
  ManagerAction manager_action_;
  UserAction user_action_;
  SubmitResult submit_result_;

  DISALLOW_COPY_AND_ASSIGN(PasswordFormManager);
};

}  

#endif  

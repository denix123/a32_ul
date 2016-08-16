// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_CHECKER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_CHECKER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "extensions/browser/blacklist_state.h"
#include "extensions/common/extension.h"

class Profile;

namespace extensions {

class RequirementsChecker;

class ExtensionInstallChecker {
 public:
  
  
  typedef base::Callback<void(int)> Callback;

  enum CheckType {
    
    CHECK_BLACKLIST = 1 << 0,
    
    CHECK_REQUIREMENTS = 1 << 1,
    
    
    CHECK_MANAGEMENT_POLICY = 1 << 2,
    
    CHECK_ALL = (1 << 3) - 1
  };

  explicit ExtensionInstallChecker(Profile* profile);
  virtual ~ExtensionInstallChecker();

  
  
  
  
  
  
  
  
  void Start(int enabled_checks, bool fail_fast, const Callback& callback);

  Profile* profile() const { return profile_; }

  const scoped_refptr<const Extension>& extension() { return extension_; }
  void set_extension(const scoped_refptr<const Extension>& extension) {
    extension_ = extension;
  }

  
  bool is_running() const { return running_checks_ != 0; }

  
  
  const std::vector<std::string>& requirement_errors() const {
    return requirement_errors_;
  }

  
  
  BlacklistState blacklist_state() const { return blacklist_state_; }

  
  bool policy_allows_load() const { return policy_allows_load_; }
  const std::string& policy_error() const { return policy_error_; }

 protected:
  virtual void CheckManagementPolicy();
  void OnManagementPolicyCheckDone(bool allows_load, const std::string& error);

  virtual void CheckRequirements();
  void OnRequirementsCheckDone(int sequence_number,
                               std::vector<std::string> errors);

  virtual void CheckBlacklistState();
  void OnBlacklistStateCheckDone(int sequence_number, BlacklistState state);

  virtual void ResetResults();
  int current_sequence_number() const { return current_sequence_number_; }

 private:
  void MaybeInvokeCallback();

  scoped_ptr<RequirementsChecker> requirements_checker_;

  
  Profile* profile_;

  
  scoped_refptr<const Extension> extension_;

  
  std::vector<std::string> requirement_errors_;

  
  BlacklistState blacklist_state_;

  
  bool policy_allows_load_;
  std::string policy_error_;

  
  int current_sequence_number_;

  
  int running_checks_;

  
  bool fail_fast_;

  
  Callback callback_;

  base::WeakPtrFactory<ExtensionInstallChecker> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionInstallChecker);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_GENERATION_MANAGER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_GENERATION_MANAGER_H_

#include <vector>

#include "base/basictypes.h"

namespace autofill {
class FormStructure;
}

namespace password_manager {

class PasswordManagerClient;
class PasswordManagerDriver;

class PasswordGenerationManager {
 public:
  explicit PasswordGenerationManager(PasswordManagerClient* client);
  virtual ~PasswordGenerationManager();

  
  
  
  void DetectAccountCreationForms(
      const std::vector<autofill::FormStructure*>& forms);

 private:
  friend class PasswordGenerationManagerTest;

  
  bool IsGenerationEnabled() const;

  
  
  PasswordManagerClient* client_;

  
  
  PasswordManagerDriver* driver_;

  DISALLOW_COPY_AND_ASSIGN(PasswordGenerationManager);
};

}  

#endif  

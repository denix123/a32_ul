// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_DRIVER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_DRIVER_H_

#include <vector>

#include "base/macros.h"
#include "base/strings/string16.h"

namespace autofill {
class AutofillManager;
struct FormData;
struct PasswordForm;
struct PasswordFormFillData;
}  

namespace password_manager {

class PasswordAutofillManager;
class PasswordGenerationManager;
class PasswordManager;

class PasswordManagerDriver {
 public:
  PasswordManagerDriver() {}
  virtual ~PasswordManagerDriver() {}

  
  virtual void FillPasswordForm(
      const autofill::PasswordFormFillData& form_data) = 0;

  
  
  virtual bool DidLastPageLoadEncounterSSLErrors() = 0;

  
  virtual bool IsOffTheRecord() = 0;

  
  virtual void AllowPasswordGenerationForForm(
      const autofill::PasswordForm& form) = 0;

  
  virtual void AccountCreationFormsFound(
      const std::vector<autofill::FormData>& forms) = 0;

  
  virtual void FillSuggestion(const base::string16& username,
                              const base::string16& password) = 0;

  
  
  virtual void PreviewSuggestion(const base::string16& username,
                                 const base::string16& password) = 0;

  
  virtual void ClearPreviewedForm() = 0;

  
  virtual PasswordGenerationManager* GetPasswordGenerationManager() = 0;

  
  virtual PasswordManager* GetPasswordManager() = 0;

  
  virtual PasswordAutofillManager* GetPasswordAutofillManager() = 0;

  
  virtual autofill::AutofillManager* GetAutofillManager() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(PasswordManagerDriver);
};

}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_AUTOFILL_MANAGER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_AUTOFILL_MANAGER_H_

#include <map>

#include "base/gtest_prod_util.h"
#include "components/autofill/core/browser/autofill_client.h"
#include "components/autofill/core/browser/autofill_popup_delegate.h"
#include "components/autofill/core/common/password_form_fill_data.h"

namespace gfx {
class RectF;
}

namespace password_manager {

class PasswordManagerClient;

class PasswordAutofillManager : public autofill::AutofillPopupDelegate {
 public:
  PasswordAutofillManager(PasswordManagerClient* password_manager_client,
                          autofill::AutofillClient* autofill_client);
  virtual ~PasswordAutofillManager();

  
  virtual void OnPopupShown() OVERRIDE;
  virtual void OnPopupHidden() OVERRIDE;
  virtual void DidSelectSuggestion(const base::string16& value,
                                   int identifier) OVERRIDE;
  virtual void DidAcceptSuggestion(const base::string16& value,
                                   int identifier) OVERRIDE;
  virtual void RemoveSuggestion(const base::string16& value,
                                int identifier) OVERRIDE;
  virtual void ClearPreviewedForm() OVERRIDE;

  
  void OnAddPasswordFormMapping(
      const autofill::FormFieldData& field,
      const autofill::PasswordFormFillData& fill_data);

  
  
  void OnShowPasswordSuggestions(
      const autofill::FormFieldData& field,
      const gfx::RectF& bounds,
      const std::vector<base::string16>& suggestions,
      const std::vector<base::string16>& realms);

  
  void Reset();

  
  bool FillSuggestionForTest(const autofill::FormFieldData& field,
                             const base::string16& username);

  
  bool PreviewSuggestionForTest(const autofill::FormFieldData& field,
                                const base::string16& username);

 private:
  typedef std::map<autofill::FormFieldData, autofill::PasswordFormFillData>
      LoginToPasswordInfoMap;

  
  
  bool FillSuggestion(const autofill::FormFieldData& field,
                      const base::string16& username);

  
  
  bool PreviewSuggestion(const autofill::FormFieldData& field,
                         const base::string16& username);

  
  
  
  bool GetPasswordForUsername(
      const base::string16& current_username,
      const autofill::PasswordFormFillData& fill_data,
      base::string16* out_password);

  
  bool FindLoginInfo(const autofill::FormFieldData& field,
                     autofill::PasswordFormFillData* found_password);

  
  LoginToPasswordInfoMap login_to_password_info_;

  
  PasswordManagerClient* const password_manager_client_;  

  autofill::AutofillClient* const autofill_client_;  

  
  autofill::FormFieldData form_field_;

  base::WeakPtrFactory<PasswordAutofillManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PasswordAutofillManager);
};

}  

#endif  

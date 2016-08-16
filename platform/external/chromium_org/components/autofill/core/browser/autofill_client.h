// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_AUTOFILL_CLIENT_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_AUTOFILL_CLIENT_H_

#include <vector>

#include "base/callback_forward.h"
#include "base/i18n/rtl.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"

namespace gfx {
class Rect;
class RectF;
}

class GURL;
class InfoBarService;
class PrefService;

namespace autofill {

class AutofillMetrics;
class AutofillPopupDelegate;
class AutofillWebDataService;
class CreditCard;
class FormStructure;
class PasswordGenerator;
class PersonalDataManager;
struct FormData;
struct PasswordForm;

class AutofillClient {
 public:
  
  enum RequestAutocompleteResult {
    AutocompleteResultSuccess,
    AutocompleteResultErrorDisabled,
    AutocompleteResultErrorCancel,
    AutocompleteResultErrorInvalid,
  };

  typedef base::Callback<void(RequestAutocompleteResult,
                              const base::string16&,
                              const FormStructure*)> ResultCallback;

  virtual ~AutofillClient() {}

  
  virtual PersonalDataManager* GetPersonalDataManager() = 0;

  
  virtual scoped_refptr<AutofillWebDataService> GetDatabase() = 0;

  
  virtual PrefService* GetPrefs() = 0;

  
  virtual void HideRequestAutocompleteDialog() = 0;

  
  virtual void ShowAutofillSettings() = 0;

  
  
  virtual void ConfirmSaveCreditCard(
      const AutofillMetrics& metric_logger,
      const base::Closure& save_card_callback) = 0;

  
  virtual void ShowRequestAutocompleteDialog(
      const FormData& form,
      const GURL& source_url,
      const ResultCallback& callback) = 0;

  
  
  
  virtual void ShowAutofillPopup(
      const gfx::RectF& element_bounds,
      base::i18n::TextDirection text_direction,
      const std::vector<base::string16>& values,
      const std::vector<base::string16>& labels,
      const std::vector<base::string16>& icons,
      const std::vector<int>& identifiers,
      base::WeakPtr<AutofillPopupDelegate> delegate) = 0;

  
  virtual void UpdateAutofillPopupDataListValues(
      const std::vector<base::string16>& values,
      const std::vector<base::string16>& labels) = 0;

  
  virtual void HideAutofillPopup() = 0;

  
  virtual bool IsAutocompleteEnabled() = 0;

  
  
  virtual void DetectAccountCreationForms(
      const std::vector<autofill::FormStructure*>& forms) = 0;

  
  virtual void DidFillOrPreviewField(
      const base::string16& autofilled_value,
      const base::string16& profile_full_name) = 0;
};

}  

#endif  

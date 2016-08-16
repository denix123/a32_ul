// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_AUTOFILL_OPTIONS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_AUTOFILL_OPTIONS_HANDLER_H_

#include <string>

#include "base/compiler_specific.h"
#include "chrome/browser/ui/webui/options/options_ui.h"
#include "components/autofill/core/browser/personal_data_manager_observer.h"

namespace autofill {
class AutofillProfile;
class PersonalDataManager;
}  

namespace base {
class DictionaryValue;
class ListValue;
}

namespace options {

class AutofillOptionsHandler : public OptionsPageUIHandler,
                               public autofill::PersonalDataManagerObserver {
 public:
  AutofillOptionsHandler();
  virtual ~AutofillOptionsHandler();

  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;
  virtual void InitializeHandler() OVERRIDE;
  virtual void InitializePage() OVERRIDE;
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void OnPersonalDataChanged() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(AutofillOptionsHandlerTest, AddressToDictionary);

  
  void SetAddressOverlayStrings(base::DictionaryValue* localized_strings);
  void SetCreditCardOverlayStrings(base::DictionaryValue* localized_strings);

  
  void LoadAutofillData();

#if defined(OS_MACOSX) && !defined(OS_IOS)
  
  
  
  void AccessAddressBook(const base::ListValue* args);
#endif  

  
  
  void RemoveData(const base::ListValue* args);

  
  
  
  void LoadAddressEditor(const base::ListValue* args);

  
  
  
  void LoadAddressEditorComponents(const base::ListValue* args);

  
  
  
  void LoadCreditCardEditor(const base::ListValue* args);

  
  
  
  
  
  void SetAddress(const base::ListValue* args);

  
  
  
  
  
  void SetCreditCard(const base::ListValue* args);

  
  
  
  
  void ValidatePhoneNumbers(const base::ListValue* args);

  
  bool IsPersonalDataLoaded() const;

  
  static void AutofillProfileToDictionary(
      const autofill::AutofillProfile& profile,
      base::DictionaryValue* address);

  
  
  autofill::PersonalDataManager* personal_data_;

  DISALLOW_COPY_AND_ASSIGN(AutofillOptionsHandler);
};

}  

#endif  

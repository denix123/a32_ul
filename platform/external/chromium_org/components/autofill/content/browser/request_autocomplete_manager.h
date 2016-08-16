// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CONTENT_BROWSER_REQUEST_AUTOCOMPLETE_MANAGER_H_
#define COMPONENTS_AUTOFILL_CONTENT_BROWSER_REQUEST_AUTOCOMPLETE_MANAGER_H_

#include "base/callback_forward.h"
#include "base/memory/weak_ptr.h"
#include "components/autofill/core/browser/autofill_client.h"

class GURL;

namespace autofill {

class ContentAutofillDriver;
struct FormData;
class FormStructure;

class RequestAutocompleteManager {
 public:
  explicit RequestAutocompleteManager(ContentAutofillDriver* autofill_driver);
  ~RequestAutocompleteManager();

  
  
  void OnRequestAutocomplete(const FormData& form, const GURL& frame_url);

  
  void OnCancelRequestAutocomplete();

 private:
  
  
  
  
  void ReturnAutocompleteResult(
      AutofillClient::RequestAutocompleteResult result,
      const base::string16& debug_message,
      const FormStructure* form_structure);

  
  
  void ShowRequestAutocompleteDialog(
      const FormData& form,
      const GURL& source_url,
      const AutofillClient::ResultCallback& callback);

  
  ContentAutofillDriver* const autofill_driver_;  

  base::WeakPtrFactory<RequestAutocompleteManager> weak_ptr_factory_;
};

}  

#endif  

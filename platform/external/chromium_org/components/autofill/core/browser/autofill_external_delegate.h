// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_AUTOFILL_EXTERNAL_DELEGATE_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_AUTOFILL_EXTERNAL_DELEGATE_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "components/autofill/core/browser/autofill_popup_delegate.h"
#include "components/autofill/core/common/form_data.h"
#include "components/autofill/core/common/form_field_data.h"
#include "ui/gfx/rect.h"

namespace autofill {

class AutofillDriver;
class AutofillManager;


class AutofillExternalDelegate
    : public AutofillPopupDelegate {
 public:
  
  
  AutofillExternalDelegate(AutofillManager* manager,
                           AutofillDriver* driver);
  virtual ~AutofillExternalDelegate();

  
  virtual void OnPopupShown() OVERRIDE;
  virtual void OnPopupHidden() OVERRIDE;
  virtual void DidSelectSuggestion(const base::string16& value,
                                   int identifier) OVERRIDE;
  virtual void DidAcceptSuggestion(const base::string16& value,
                                   int identifier) OVERRIDE;
  virtual void RemoveSuggestion(const base::string16& value,
                                int identifier) OVERRIDE;
  virtual void ClearPreviewedForm() OVERRIDE;

  
  
  
  
  
  
  
  virtual void OnQuery(int query_id,
                       const FormData& form,
                       const FormFieldData& field,
                       const gfx::RectF& element_bounds,
                       bool display_warning_if_disabled);

  
  
  virtual void OnSuggestionsReturned(
      int query_id,
      const std::vector<base::string16>& values,
      const std::vector<base::string16>& labels,
      const std::vector<base::string16>& icons,
      const std::vector<int>& unique_ids);

  
  void SetCurrentDataListValues(
      const std::vector<base::string16>& data_list_values,
      const std::vector<base::string16>& data_list_labels);

  
  
  void DidEndTextFieldEditing();

  
  
  void Reset();

  
  void OnPingAck();

 protected:
  base::WeakPtr<AutofillExternalDelegate> GetWeakPtr();

 private:
  
  
  
  
  void FillAutofillFormData(int unique_id, bool is_preview);

  
  void ApplyAutofillWarnings(std::vector<base::string16>* values,
                             std::vector<base::string16>* labels,
                             std::vector<base::string16>* icons,
                             std::vector<int>* unique_ids);

  
  
  
  void ApplyAutofillOptions(std::vector<base::string16>* values,
                            std::vector<base::string16>* labels,
                            std::vector<base::string16>* icons,
                            std::vector<int>* unique_ids);

  
  
  void InsertDataListValues(std::vector<base::string16>* values,
                            std::vector<base::string16>* labels,
                            std::vector<base::string16>* icons,
                            std::vector<int>* unique_ids);

#if defined(OS_MACOSX) && !defined(OS_IOS)
  
  void PingRenderer();
#endif  

  AutofillManager* manager_;  

  
  
  AutofillDriver* driver_;  

  
  
  int query_id_;

  
  FormData query_form_;
  FormFieldData query_field_;

  
  gfx::RectF element_bounds_;

  
  bool display_warning_if_disabled_;

  
  bool has_suggestion_;

  
  
  bool has_shown_popup_for_current_edit_;

  
  std::vector<base::string16> data_list_values_;
  std::vector<base::string16> data_list_labels_;

  base::WeakPtrFactory<AutofillExternalDelegate> weak_ptr_factory_;

  
  
  bool has_shown_address_book_prompt;

  DISALLOW_COPY_AND_ASSIGN(AutofillExternalDelegate);
};

}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CONTENT_RENDERER_AUTOFILL_AGENT_H_
#define COMPONENTS_AUTOFILL_CONTENT_RENDERER_AUTOFILL_AGENT_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "components/autofill/content/renderer/form_cache.h"
#include "components/autofill/content/renderer/page_click_listener.h"
#include "content/public/renderer/render_view_observer.h"
#include "third_party/WebKit/public/web/WebAutofillClient.h"
#include "third_party/WebKit/public/web/WebFormControlElement.h"
#include "third_party/WebKit/public/web/WebFormElement.h"
#include "third_party/WebKit/public/web/WebInputElement.h"

namespace blink {
class WebNode;
class WebView;
struct WebAutocompleteParams;
}

namespace autofill {

struct FormData;
struct FormFieldData;
struct WebElementDescriptor;
class PasswordAutofillAgent;
class PasswordGenerationAgent;


class AutofillAgent : public content::RenderViewObserver,
                      public PageClickListener,
                      public blink::WebAutofillClient {
 public:
  
  
  
  AutofillAgent(content::RenderView* render_view,
                PasswordAutofillAgent* password_autofill_manager,
                PasswordGenerationAgent* password_generation_agent);
  virtual ~AutofillAgent();

 private:
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidFinishDocumentLoad(blink::WebLocalFrame* frame) OVERRIDE;
  virtual void DidCommitProvisionalLoad(blink::WebLocalFrame* frame,
                                        bool is_new_navigation) OVERRIDE;
  virtual void FrameDetached(blink::WebFrame* frame) OVERRIDE;
  virtual void FrameWillClose(blink::WebFrame* frame) OVERRIDE;
  virtual void WillSubmitForm(blink::WebLocalFrame* frame,
                              const blink::WebFormElement& form) OVERRIDE;
  virtual void DidChangeScrollOffset(blink::WebLocalFrame* frame) OVERRIDE;
  virtual void FocusedNodeChanged(const blink::WebNode& node) OVERRIDE;
  virtual void OrientationChangeEvent() OVERRIDE;
  virtual void Resized() OVERRIDE;

  
  virtual void FormControlElementClicked(
      const blink::WebFormControlElement& element,
      bool was_focused) OVERRIDE;

  
  virtual void textFieldDidEndEditing(
      const blink::WebInputElement& element);
  virtual void textFieldDidChange(
      const blink::WebFormControlElement& element);
  virtual void textFieldDidReceiveKeyDown(
      const blink::WebInputElement& element,
      const blink::WebKeyboardEvent& event);
  virtual void didRequestAutocomplete(
      const blink::WebFormElement& form);
  virtual void setIgnoreTextChanges(bool ignore);
  virtual void didAssociateFormControls(
      const blink::WebVector<blink::WebNode>& nodes);
  virtual void openTextDataListChooser(const blink::WebInputElement& element);
  virtual void firstUserGestureObserved();

  void OnFieldTypePredictionsAvailable(
      const std::vector<FormDataPredictions>& forms);
  void OnFillForm(int query_id, const FormData& form);
  void OnPing();
  void OnPreviewForm(int query_id, const FormData& form);

  
  void OnClearForm();
  void OnClearPreviewedForm();
  void OnFillFieldWithValue(const base::string16& value);
  void OnPreviewFieldWithValue(const base::string16& value);
  void OnAcceptDataListSuggestion(const base::string16& value);
  void OnFillPasswordSuggestion(const base::string16& username,
                                const base::string16& password);
  void OnPreviewPasswordSuggestion(const base::string16& username,
                                   const base::string16& password);

  
  
  void OnRequestAutocompleteResult(
      blink::WebFormElement::AutocompleteResult result,
      const base::string16& message,
      const FormData& form_data);

  
  void FinishAutocompleteRequest(
      blink::WebFormElement::AutocompleteResult result);

  
  
  void TextFieldDidChangeImpl(const blink::WebFormControlElement& element);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void ShowSuggestions(const blink::WebFormControlElement& element,
                       bool autofill_on_empty_values,
                       bool requires_caret_at_end,
                       bool display_warning_if_disabled,
                       bool datalist_only,
                       bool show_full_suggestion_list,
                       bool show_password_suggestions_only);

  
  
  void QueryAutofillSuggestions(const blink::WebFormControlElement& element,
                                bool display_warning_if_disabled,
                                bool datalist_only);

  
  void AcceptDataListSuggestion(const base::string16& suggested_value);

  
  
  bool FindFormAndFieldForNode(
      const blink::WebNode& node,
      FormData* form,
      FormFieldData* field) WARN_UNUSED_RESULT;

  
  void FillFieldWithValue(const base::string16& value,
                          blink::WebInputElement* node);

  
  
  
  void PreviewFieldWithValue(const base::string16& value,
                             blink::WebInputElement* node);

  
  void ProcessForms(const blink::WebLocalFrame& frame);

  
  void HidePopup();

  FormCache form_cache_;

  PasswordAutofillAgent* password_autofill_agent_;  
  PasswordGenerationAgent* password_generation_agent_;  

  
  
  int autofill_query_id_;

  
  blink::WebFormControlElement element_;

  
  blink::WebFormElement in_flight_request_form_;

  
  blink::WebView* web_view_;

  
  bool display_warning_if_disabled_;

  
  bool was_query_node_autofilled_;

  
  
  bool has_shown_autofill_popup_for_current_edit_;

  
  bool did_set_node_text_;

  
  
  
  bool ignore_text_changes_;

  
  
  
  bool is_popup_possibly_visible_;

  
  
  
  bool main_frame_processed_;

  base::WeakPtrFactory<AutofillAgent> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(AutofillAgent);
};

}  

#endif  

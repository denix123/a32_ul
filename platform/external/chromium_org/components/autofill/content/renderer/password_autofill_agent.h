// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CONTENT_RENDERER_PASSWORD_AUTOFILL_AGENT_H_
#define COMPONENTS_AUTOFILL_CONTENT_RENDERER_PASSWORD_AUTOFILL_AGENT_H_

#include <map>
#include <vector>

#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/autofill/core/common/password_form_fill_data.h"
#include "content/public/renderer/render_view_observer.h"
#include "third_party/WebKit/public/web/WebInputElement.h"

namespace blink {
class WebInputElement;
class WebKeyboardEvent;
class WebSecurityOrigin;
class WebView;
}

namespace autofill {

class PasswordAutofillAgent : public content::RenderViewObserver {
 public:
  explicit PasswordAutofillAgent(content::RenderView* render_view);
  virtual ~PasswordAutofillAgent();

  
  
  
  bool TextFieldDidEndEditing(const blink::WebInputElement& element);
  bool TextDidChangeInTextField(const blink::WebInputElement& element);
  bool TextFieldHandlingKeyDown(const blink::WebInputElement& element,
                                const blink::WebKeyboardEvent& event);

  
  
  bool FillSuggestion(const blink::WebNode& node,
                      const blink::WebString& username,
                      const blink::WebString& password);

  
  
  bool PreviewSuggestion(const blink::WebNode& node,
                         const blink::WebString& username,
                         const blink::WebString& password);

  
  
  
  bool DidClearAutofillSelection(const blink::WebNode& node);
  
  
  
  
  bool ShowSuggestions(const blink::WebInputElement& element, bool show_all);

  
  void OnDynamicFormsSeen(blink::WebFrame* frame);

  
  
  
  void FirstUserGestureObserved();

 protected:
  virtual bool OriginCanAccessPasswordManager(
      const blink::WebSecurityOrigin& origin);

 private:
  enum OtherPossibleUsernamesUsage {
    NOTHING_TO_AUTOFILL,
    OTHER_POSSIBLE_USERNAMES_ABSENT,
    OTHER_POSSIBLE_USERNAMES_PRESENT,
    OTHER_POSSIBLE_USERNAME_SHOWN,
    OTHER_POSSIBLE_USERNAME_SELECTED,
    OTHER_POSSIBLE_USERNAMES_MAX
  };

  
  enum ProvisionallySaveRestriction {
    RESTRICTION_NONE,
    RESTRICTION_NON_EMPTY_PASSWORD
  };

  struct PasswordInfo {
    blink::WebInputElement password_field;
    PasswordFormFillData fill_data;
    bool backspace_pressed_last;
    
    
    bool password_was_edited_last;
    PasswordInfo();
  };
  typedef std::map<blink::WebElement, PasswordInfo> LoginToPasswordInfoMap;
  typedef std::map<blink::WebElement, blink::WebElement> PasswordToLoginMap;
  typedef std::map<blink::WebFrame*,
                   linked_ptr<PasswordForm> > FrameToPasswordFormMap;

  
  
  
  class PasswordValueGatekeeper {
   public:
    PasswordValueGatekeeper();
    ~PasswordValueGatekeeper();

    
    
    void RegisterElement(blink::WebInputElement* element);

    
    
    void OnUserGesture();

    
    void Reset();

   private:
    
    void ShowValue(blink::WebInputElement* element);

    bool was_user_gesture_seen_;
    std::vector<blink::WebInputElement> elements_;

    DISALLOW_COPY_AND_ASSIGN(PasswordValueGatekeeper);
  };

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidStartProvisionalLoad(blink::WebLocalFrame* frame) OVERRIDE;
  virtual void DidStartLoading() OVERRIDE;
  virtual void DidFinishDocumentLoad(blink::WebLocalFrame* frame) OVERRIDE;
  virtual void DidFinishLoad(blink::WebLocalFrame* frame) OVERRIDE;
  virtual void DidStopLoading() OVERRIDE;
  virtual void FrameDetached(blink::WebFrame* frame) OVERRIDE;
  virtual void FrameWillClose(blink::WebFrame* frame) OVERRIDE;
  virtual void WillSendSubmitEvent(blink::WebLocalFrame* frame,
                                   const blink::WebFormElement& form) OVERRIDE;
  virtual void WillSubmitForm(blink::WebLocalFrame* frame,
                              const blink::WebFormElement& form) OVERRIDE;

  
  void OnFillPasswordForm(const PasswordFormFillData& form_data);
  void OnSetLoggingState(bool active);

  
  
  void SendPasswordForms(blink::WebFrame* frame, bool only_visible);

  void GetSuggestions(const PasswordFormFillData& fill_data,
                      const base::string16& input,
                      std::vector<base::string16>* suggestions,
                      std::vector<base::string16>* realms,
                      bool show_all);

  bool ShowSuggestionPopup(const PasswordFormFillData& fill_data,
                           const blink::WebInputElement& user_input,
                           bool show_all);

  
  
  
  
  
  void FillFormOnPasswordRecieved(const PasswordFormFillData& fill_data,
                                  blink::WebInputElement username_element,
                                  blink::WebInputElement password_element);

  bool FillUserNameAndPassword(blink::WebInputElement* username_element,
                               blink::WebInputElement* password_element,
                               const PasswordFormFillData& fill_data,
                               bool exact_username_match,
                               bool set_selection);

  
  
  void PerformInlineAutocomplete(
      const blink::WebInputElement& username,
      const blink::WebInputElement& password,
      const PasswordFormFillData& fill_data);

  
  
  void FrameClosing(const blink::WebFrame* frame);

  
  bool FindLoginInfo(const blink::WebNode& node,
                     blink::WebInputElement* found_input,
                     PasswordInfo** found_password);

  
  
  void ClearPreview(blink::WebInputElement* username,
                    blink::WebInputElement* password);

  
  
  blink::WebFrame* CurrentOrChildFrameWithSavedForms(
      const blink::WebFrame* current_frame);

  
  
  void ProvisionallySavePassword(blink::WebLocalFrame* frame,
                                 const blink::WebFormElement& form,
                                 ProvisionallySaveRestriction restriction);

  
  LoginToPasswordInfoMap login_to_password_info_;
  
  PasswordToLoginMap password_to_username_;

  
  OtherPossibleUsernamesUsage usernames_usage_;

  
  blink::WebView* web_view_;

  
  
  FrameToPasswordFormMap provisionally_saved_forms_;

  PasswordValueGatekeeper gatekeeper_;

  
  bool logging_state_active_;

  
  bool was_username_autofilled_;
  
  bool was_password_autofilled_;

  
  
  int username_selection_start_;

  
  bool did_stop_loading_;

  base::WeakPtrFactory<PasswordAutofillAgent> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PasswordAutofillAgent);
};

}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CONTENT_RENDERER_PASSWORD_GENERATION_AGENT_H_
#define COMPONENTS_AUTOFILL_CONTENT_RENDERER_PASSWORD_GENERATION_AGENT_H_

#include <map>
#include <utility>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "content/public/renderer/render_view_observer.h"
#include "third_party/WebKit/public/web/WebInputElement.h"
#include "url/gurl.h"

namespace blink {
class WebCString;
class WebDocument;
}

namespace autofill {

struct FormData;
struct PasswordForm;

class PasswordGenerationAgent : public content::RenderViewObserver {
 public:
  explicit PasswordGenerationAgent(content::RenderView* render_view);
  virtual ~PasswordGenerationAgent();

  
  
  bool TextDidChangeInTextField(const blink::WebInputElement& element);

  
  bool FocusedNodeHasChanged(const blink::WebNode& node);

  
  static const size_t kMaximumOfferSize = 5;

 protected:
  
  
  virtual bool ShouldAnalyzeDocument(const blink::WebDocument& document) const;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  void set_enabled(bool enabled) { enabled_ = enabled; }

 private:
  
  virtual void DidFinishDocumentLoad(blink::WebLocalFrame* frame) OVERRIDE;
  virtual void DidFinishLoad(blink::WebLocalFrame* frame) OVERRIDE;

  
  void OnFormNotBlacklisted(const PasswordForm& form);
  void OnPasswordAccepted(const base::string16& password);
  void OnAccountCreationFormsDetected(
      const std::vector<autofill::FormData>& forms);

  
  
  
  void DetermineGenerationElement();

  
  void ShowGenerationPopup();

  
  void ShowEditingPopup();

  
  void HidePopup();

  content::RenderView* render_view_;

  
  scoped_ptr<PasswordForm> possible_account_creation_form_;

  
  
  
  std::vector<GURL> not_blacklisted_password_form_origins_;

  
  
  
  std::vector<autofill::FormData> generation_enabled_forms_;

  
  std::vector<blink::WebInputElement> password_elements_;

  
  blink::WebInputElement generation_element_;

  
  
  bool password_is_generated_;

  
  
  bool password_edited_;

  
  bool enabled_;

  DISALLOW_COPY_AND_ASSIGN(PasswordGenerationAgent);
};

}  

#endif  

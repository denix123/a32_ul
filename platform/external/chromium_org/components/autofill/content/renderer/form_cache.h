// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CONTENT_RENDERER_FORM_CACHE_H_
#define COMPONENTS_AUTOFILL_CONTENT_RENDERER_FORM_CACHE_H_

#include <map>
#include <set>
#include <vector>

#include "base/strings/string16.h"

namespace blink {
class WebDocument;
class WebFormControlElement;
class WebFormElement;
class WebFrame;
class WebInputElement;
class WebSelectElement;
}

namespace autofill {

struct FormData;
struct FormDataPredictions;

class FormCache {
 public:
  FormCache();
  ~FormCache();

  
  
  void ExtractNewForms(const blink::WebFrame& frame,
                       std::vector<FormData>* forms);

  
  void ResetFrame(const blink::WebFrame& frame);

  
  
  bool ClearFormWithElement(const blink::WebFormControlElement& element);

  
  
  
  
  bool ShowPredictions(const FormDataPredictions& form);

 private:
  
  std::set<blink::WebDocument> web_documents_;

  
  std::map<const blink::WebFrame*, std::set<FormData> > parsed_forms_;

  
  std::map<const blink::WebSelectElement, base::string16>
      initial_select_values_;

  
  std::map<const blink::WebInputElement, bool> initial_checked_state_;

  DISALLOW_COPY_AND_ASSIGN(FormCache);
};

}  

#endif  

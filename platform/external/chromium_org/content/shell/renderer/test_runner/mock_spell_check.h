// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_TEST_RUNNER_MOCK_SPELL_CHECK_H_
#define CONTENT_SHELL_RENDERER_TEST_RUNNER_MOCK_SPELL_CHECK_H_

#include <vector>

#include "base/basictypes.h"
#include "third_party/WebKit/public/platform/WebString.h"
#include "third_party/WebKit/public/platform/WebVector.h"
#include "third_party/WebKit/public/web/WebTextCheckingResult.h"

namespace content {

class MockSpellCheck {
 public:
  static void FillSuggestionList(
      const blink::WebString& word,
      blink::WebVector<blink::WebString>* suggestions);

  MockSpellCheck();
  ~MockSpellCheck();

  
  
  
  
  
  
  
  
  bool SpellCheckWord(const blink::WebString& text,
                      int* misspelled_offset,
                      int* misspelled_length);

  
  
  bool HasInCache(const blink::WebString& text);

  
  
  bool IsMultiWordMisspelling(
      const blink::WebString& text,
      std::vector<blink::WebTextCheckingResult>* results);

 private:
  
  
  
  
  
  
  
  bool InitializeIfNeeded();

  
  std::vector<base::string16> misspelled_words_;

  
  bool initialized_;

  DISALLOW_COPY_AND_ASSIGN(MockSpellCheck);
};

}  

#endif  

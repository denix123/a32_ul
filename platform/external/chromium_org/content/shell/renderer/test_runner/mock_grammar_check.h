// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_TEST_RUNNER_MOCK_GRAMMAR_CHECK_H_
#define CONTENT_SHELL_RENDERER_TEST_RUNNER_MOCK_GRAMMAR_CHECK_H_

#include <vector>

namespace blink {
class WebString;
struct WebTextCheckingResult;
}

namespace content {

class MockGrammarCheck {
 public:
  static bool CheckGrammarOfString(const blink::WebString&,
                                   std::vector<blink::WebTextCheckingResult>*);
};

}  

#endif  

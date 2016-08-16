// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_TEST_RUNNER_MOCK_WEB_THEME_ENGINE_MAC_H_
#define CONTENT_SHELL_RENDERER_TEST_RUNNER_MOCK_WEB_THEME_ENGINE_MAC_H_

#include "base/macros.h"
#include "third_party/WebKit/public/platform/WebThemeEngine.h"

namespace content {

class MockWebThemeEngineMac : public blink::WebThemeEngine {
 public:
  MockWebThemeEngineMac() {}
  virtual ~MockWebThemeEngineMac() {}

  virtual void paintScrollbarThumb(blink::WebCanvas*,
                                   blink::WebThemeEngine::State,
                                   blink::WebThemeEngine::Size,
                                   const blink::WebRect&,
                                   const blink::WebThemeEngine::ScrollbarInfo&);

 private:
  virtual void paintHIThemeScrollbarThumb(
      blink::WebCanvas*,
      blink::WebThemeEngine::State,
      blink::WebThemeEngine::Size,
      const blink::WebRect&,
      const blink::WebThemeEngine::ScrollbarInfo&);
  virtual void paintNSScrollerScrollbarThumb(
      blink::WebCanvas*,
      blink::WebThemeEngine::State,
      blink::WebThemeEngine::Size,
      const blink::WebRect&,
      const blink::WebThemeEngine::ScrollbarInfo&);

  DISALLOW_COPY_AND_ASSIGN(MockWebThemeEngineMac);
};

}  

#endif  

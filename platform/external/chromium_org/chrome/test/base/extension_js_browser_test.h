// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_EXTENSION_JS_BROWSER_TEST_H_
#define CHROME_TEST_BASE_EXTENSION_JS_BROWSER_TEST_H_

#include "base/callback_forward.h"
#include "chrome/test/base/extension_load_waiter_one_shot.h"
#include "chrome/test/base/javascript_browser_test.h"

class ExtensionJSBrowserTest : public JavaScriptBrowserTest {
 public:
  ExtensionJSBrowserTest();

  virtual ~ExtensionJSBrowserTest();

 protected:
  
  void WaitForExtension(const char* extension_id, const base::Closure& load_cb);

  
  
  bool RunJavascriptTestF(bool is_async,
                          const std::string& test_fixture,
                          const std::string& test_name);

 private:
  scoped_ptr<ExtensionLoadWaiterOneShot> load_waiter_;
  bool libs_loaded_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionJSBrowserTest);
};

#endif  

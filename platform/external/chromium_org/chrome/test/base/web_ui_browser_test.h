// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_WEB_UI_BROWSER_TEST_H_
#define CHROME_TEST_BASE_WEB_UI_BROWSER_TEST_H_

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/javascript_browser_test.h"

namespace base {
class Value;
}

namespace content {
class RenderViewHost;
class WebUI;
class WebUIMessageHandler;
}

class TestChromeWebUIControllerFactory;
class WebUITestHandler;

#define WEB_UI_UNITTEST_F(x, y) \
  IN_PROC_BROWSER_TEST_F(x, y) { ASSERT_TRUE(RunJavascriptTest(#y)); }

class WebUIBrowserTest : public JavaScriptBrowserTest {
 public:
  virtual ~WebUIBrowserTest();

  
  
  
  bool RunJavascriptFunction(const std::string& function_name);
  bool RunJavascriptFunction(const std::string& function_name,
                             base::Value* arg);
  bool RunJavascriptFunction(const std::string& function_name,
                             base::Value* arg1,
                             base::Value* arg2);
  bool RunJavascriptFunction(const std::string& function_name,
                             const ConstValueVector& function_arguments);

  
  bool RunJavascriptTestF(bool is_async,
                          const std::string& test_fixture,
                          const std::string& test_name);

  
  
  bool RunJavascriptTest(const std::string& test_name);
  bool RunJavascriptTest(const std::string& test_name, base::Value* arg);
  bool RunJavascriptTest(const std::string& test_name,
                         base::Value* arg1,
                         base::Value* arg2);
  bool RunJavascriptTest(const std::string& test_name,
                         const ConstValueVector& test_arguments);

  
  
  bool RunJavascriptAsyncTest(const std::string& test_name);
  bool RunJavascriptAsyncTest(const std::string& test_name, base::Value* arg);
  bool RunJavascriptAsyncTest(const std::string& test_name,
                              base::Value* arg1,
                              base::Value* arg2);
  bool RunJavascriptAsyncTest(const std::string& test_name,
                              base::Value* arg1,
                              base::Value* arg2,
                              base::Value* arg3);
  bool RunJavascriptAsyncTest(const std::string& test_name,
                              const ConstValueVector& test_arguments);

  
  
  
  void PreLoadJavascriptLibraries(const std::string& preload_test_fixture,
                                  const std::string& preload_test_name,
                                  content::RenderViewHost* preload_host);

  
  
  
  
  void BrowsePreload(const GURL& browse_to);

  
  
  
  
  void BrowsePrintPreload(const GURL& browse_to);

 protected:
  
  static const char kDummyURL[];

  WebUIBrowserTest();

  
  void set_preload_test_fixture(const std::string& preload_test_fixture);
  void set_preload_test_name(const std::string& preload_test_name);

  
  virtual void SetUpOnMainThread() OVERRIDE;
  virtual void TearDownOnMainThread() OVERRIDE;

  
  void SetWebUIInstance(content::WebUI* web_ui);

  
  virtual content::WebUIMessageHandler* GetMockMessageHandler();

  
  
  static GURL WebUITestDataPathToURL(const base::FilePath::StringType& path);

 private:
  
  
  
  
  
  
  
  bool RunJavascriptUsingHandler(const std::string& function_name,
                                 const ConstValueVector& function_arguments,
                                 bool is_test,
                                 bool is_async,
                                 content::RenderViewHost* preload_host);

  
  void SetupHandlers();

  
  scoped_ptr<WebUITestHandler> test_handler_;

  
  
  bool libraries_preloaded_;

  
  
  std::string preload_test_fixture_;
  std::string preload_test_name_;

  
  
  content::WebUI* override_selected_web_ui_;

  scoped_ptr<TestChromeWebUIControllerFactory> test_factory_;
};

#endif  
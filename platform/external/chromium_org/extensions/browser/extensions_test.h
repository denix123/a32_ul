// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSIONS_TEST_H_
#define EXTENSIONS_BROWSER_EXTENSIONS_TEST_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace content {
class BrowserContext;
class ContentClient;
class ContentBrowserClient;
}

namespace extensions {
class TestExtensionsBrowserClient;

class ExtensionsTest : public testing::Test {
 public:
  ExtensionsTest();
  virtual ~ExtensionsTest();

  
  
  content::BrowserContext* browser_context() { return browser_context_.get(); }

  
  
  TestExtensionsBrowserClient* extensions_browser_client() {
    return extensions_browser_client_.get();
  }

  
  virtual void SetUp() OVERRIDE;
  virtual void TearDown() OVERRIDE;

 private:
  scoped_ptr<content::ContentClient> content_client_;
  scoped_ptr<content::ContentBrowserClient> content_browser_client_;
  scoped_ptr<content::BrowserContext> browser_context_;
  scoped_ptr<TestExtensionsBrowserClient> extensions_browser_client_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionsTest);
};

}  

#endif  

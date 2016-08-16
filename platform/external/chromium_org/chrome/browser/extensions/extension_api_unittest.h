// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_API_UNITTEST_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_API_UNITTEST_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/test/base/browser_with_test_window_test.h"

namespace base {
class Value;
class DictionaryValue;
class ListValue;
}

namespace content {
class WebContents;
}

class UIThreadExtensionFunction;

namespace extensions {

class ExtensionApiUnittest : public BrowserWithTestWindowTest {
 public:
  ExtensionApiUnittest();
  virtual ~ExtensionApiUnittest();

  content::WebContents* contents() { return contents_; }

  const Extension* extension() const { return extension_.get(); }
  scoped_refptr<Extension> extension_ref() { return extension_; }
  void set_extension(scoped_refptr<Extension> extension) {
    extension_ = extension;
  }

 protected:
  
  virtual void SetUp() OVERRIDE;

  
  
  
  void CreateBackgroundPage();

  
  
  

  
  scoped_ptr<base::Value> RunFunctionAndReturnValue(
      UIThreadExtensionFunction* function, const std::string& args);

  
  
  scoped_ptr<base::DictionaryValue> RunFunctionAndReturnDictionary(
      UIThreadExtensionFunction* function, const std::string& args);

  
  
  scoped_ptr<base::ListValue> RunFunctionAndReturnList(
      UIThreadExtensionFunction* function, const std::string& args);

  
  
  std::string RunFunctionAndReturnError(
      UIThreadExtensionFunction* function, const std::string& args);

  
  void RunFunction(
      UIThreadExtensionFunction* function, const std::string& args);

 private:
  
  
  content::WebContents* contents_;

  
  scoped_refptr<Extension> extension_;
};

}  

#endif  

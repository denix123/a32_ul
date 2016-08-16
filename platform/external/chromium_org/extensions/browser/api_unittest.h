// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_UNITTEST_H_
#define EXTENSIONS_BROWSER_API_UNITTEST_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/testing_pref_service.h"
#include "extensions/browser/extensions_test.h"
#include "extensions/browser/mock_extension_system.h"

namespace base {
class Value;
class DictionaryValue;
class ListValue;
}

namespace content {
class NotificationService;
class TestBrowserThreadBundle;
}

class UIThreadExtensionFunction;

namespace extensions {

class ApiUnitTest : public ExtensionsTest {
 public:
  ApiUnitTest();
  virtual ~ApiUnitTest();

  const Extension* extension() const { return extension_.get(); }
  scoped_refptr<Extension> extension_ref() { return extension_; }
  void set_extension(scoped_refptr<Extension> extension) {
    extension_ = extension;
  }

 protected:
  
  virtual void SetUp() OVERRIDE;

  
  
  

  
  scoped_ptr<base::Value> RunFunctionAndReturnValue(
      UIThreadExtensionFunction* function,
      const std::string& args);

  
  
  scoped_ptr<base::DictionaryValue> RunFunctionAndReturnDictionary(
      UIThreadExtensionFunction* function,
      const std::string& args);

  
  
  scoped_ptr<base::ListValue> RunFunctionAndReturnList(
      UIThreadExtensionFunction* function,
      const std::string& args);

  
  
  std::string RunFunctionAndReturnError(UIThreadExtensionFunction* function,
                                        const std::string& args);

  
  void RunFunction(UIThreadExtensionFunction* function,
                   const std::string& args);

 private:
  scoped_ptr<content::NotificationService> notification_service_;

  scoped_ptr<content::TestBrowserThreadBundle> thread_bundle_;
  TestingPrefServiceSimple testing_pref_service_;

  MockExtensionSystemFactory<MockExtensionSystem> extension_system_factory_;

  
  scoped_refptr<Extension> extension_;
};

}  

#endif  

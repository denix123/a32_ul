// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_TEST_UTILS_H_
#define EXTENSIONS_BROWSER_API_TEST_UTILS_H_

#include <string>

#include "base/memory/scoped_ptr.h"

class UIThreadExtensionFunction;

namespace base {
class ListValue;
class Value;
}

namespace content {
class BrowserContext;
}

namespace extensions {
class ExtensionFunctionDispatcher;

namespace api_test_utils {

enum RunFunctionFlags { NONE = 0, INCLUDE_INCOGNITO = 1 << 0 };

base::Value* RunFunctionWithDelegateAndReturnSingleResult(
    UIThreadExtensionFunction* function,
    const std::string& args,
    content::BrowserContext* context,
    scoped_ptr<ExtensionFunctionDispatcher> dispatcher);
base::Value* RunFunctionWithDelegateAndReturnSingleResult(
    UIThreadExtensionFunction* function,
    const std::string& args,
    content::BrowserContext* context,
    scoped_ptr<ExtensionFunctionDispatcher> dispatcher,
    RunFunctionFlags flags);

base::Value* RunFunctionAndReturnSingleResult(
    UIThreadExtensionFunction* function,
    const std::string& args,
    content::BrowserContext* context);
base::Value* RunFunctionAndReturnSingleResult(
    UIThreadExtensionFunction* function,
    const std::string& args,
    content::BrowserContext* context,
    RunFunctionFlags flags);

std::string RunFunctionAndReturnError(UIThreadExtensionFunction* function,
                                      const std::string& args,
                                      content::BrowserContext* context,
                                      RunFunctionFlags flags);
std::string RunFunctionAndReturnError(UIThreadExtensionFunction* function,
                                      const std::string& args,
                                      content::BrowserContext* context);

bool RunFunction(UIThreadExtensionFunction* function,
                 const std::string& args,
                 content::BrowserContext* context);
bool RunFunction(UIThreadExtensionFunction* function,
                 const std::string& args,
                 content::BrowserContext* context,
                 scoped_ptr<ExtensionFunctionDispatcher> dispatcher,
                 RunFunctionFlags flags);
bool RunFunction(UIThreadExtensionFunction* function,
                 scoped_ptr<base::ListValue> args,
                 content::BrowserContext* context,
                 scoped_ptr<ExtensionFunctionDispatcher> dispatcher,
                 RunFunctionFlags flags);

}  
}  

#endif  

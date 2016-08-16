// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_TEST_UTIL_H_
#define EXTENSIONS_COMMON_TEST_UTIL_H_

#include <string>

#include "base/memory/ref_counted.h"

namespace extensions {
class Extension;
class ExtensionBuilder;

namespace test_util {

ExtensionBuilder& BuildExtension(ExtensionBuilder& builder);

scoped_refptr<Extension> CreateEmptyExtension();

scoped_refptr<Extension> CreateEmptyExtension(const std::string& id);

}  
}  

#endif  

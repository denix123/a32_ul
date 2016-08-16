// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_TESTS_TEST_HARNESS_UTILS_H_
#define PPAPI_TESTS_TEST_HARNESS_UTILS_H_

#include <string>
#include "base/files/file_path.h"
#include "ppapi/shared_impl/ppapi_shared_export.h"


namespace base {
class CommandLine;
}

namespace ppapi {

std::string PPAPI_SHARED_EXPORT StripTestPrefixes(const std::string& test_name);

base::FilePath::StringType PPAPI_SHARED_EXPORT GetTestLibraryName();

} 

#endif  

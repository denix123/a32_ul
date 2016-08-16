// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_COMMON_WEBKIT_TEST_HELPERS_H_
#define CONTENT_SHELL_COMMON_WEBKIT_TEST_HELPERS_H_

#include <string>
#include <vector>

namespace base {
class FilePath;
}

namespace content {

struct TestPreferences;
struct WebPreferences;

void ExportLayoutTestSpecificPreferences(const TestPreferences& from,
                                         WebPreferences* to);

void ApplyLayoutTestDefaultPreferences(WebPreferences* prefs);

base::FilePath GetWebKitRootDirFilePath();

std::vector<std::string> GetSideloadFontFiles();

}  

#endif  

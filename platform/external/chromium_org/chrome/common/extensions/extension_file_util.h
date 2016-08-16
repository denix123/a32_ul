// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_EXTENSION_FILE_UTIL_H_
#define CHROME_COMMON_EXTENSIONS_EXTENSION_FILE_UTIL_H_

#include <set>

namespace base {
class FilePath;
}

namespace extensions {
class Extension;
}

namespace extension_file_util {

std::set<base::FilePath> GetBrowserImagePaths(
    const extensions::Extension* extension);

}  

#endif  

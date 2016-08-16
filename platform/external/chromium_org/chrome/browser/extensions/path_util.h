// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_PATH_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_PATH_UTIL_H_

#include "base/files/file_path.h"

namespace extensions {
namespace path_util {

base::FilePath PrettifyPath(const base::FilePath& source_path);

}  
}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CRX_FILE_ID_UTIL_H_
#define COMPONENTS_CRX_FILE_ID_UTIL_H_

#include <string>

namespace base {
class FilePath;
}

namespace crx_file {
namespace id_util {

extern const size_t kIdSize;

std::string GenerateId(const std::string& input);

std::string GenerateIdForPath(const base::FilePath& path);

base::FilePath MaybeNormalizePath(const base::FilePath& path);

bool IdIsValid(const std::string& id);

}  
}  

#endif  

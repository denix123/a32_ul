// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_MANAGER_FILESYSTEM_API_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_FILE_MANAGER_FILESYSTEM_API_UTIL_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"

class Profile;

namespace base {
class FilePath;
}  

namespace storage {
class FileSystemURL;
}  

namespace file_manager {
namespace util {

bool IsUnderNonNativeLocalPath(Profile* profile, const base::FilePath& path);

void GetNonNativeLocalPathMimeType(
    Profile* profile,
    const base::FilePath& path,
    const base::Callback<void(bool, const std::string&)>& callback);

void IsNonNativeLocalPathDirectory(
    Profile* profile,
    const base::FilePath& path,
    const base::Callback<void(bool)>& callback);

void PrepareNonNativeLocalFileForWritableApp(
    Profile* profile,
    const base::FilePath& path,
    const base::Callback<void(bool)>& callback);

}  
}  

#endif  

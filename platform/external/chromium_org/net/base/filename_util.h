// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_FILENAME_UTIL_H_
#define NET_BASE_FILENAME_UTIL_H_

#include <string>

#include "base/strings/string16.h"
#include "net/base/net_export.h"

class GURL;

namespace base {
class FilePath;
}

namespace  net {

NET_EXPORT GURL FilePathToFileURL(const base::FilePath& path);

NET_EXPORT bool FileURLToFilePath(const GURL& url, base::FilePath* file_path);

NET_EXPORT base::string16 GetSuggestedFilename(
    const GURL& url,
    const std::string& content_disposition,
    const std::string& referrer_charset,
    const std::string& suggested_name,
    const std::string& mime_type,
    const std::string& default_name);

NET_EXPORT base::FilePath GenerateFileName(
    const GURL& url,
    const std::string& content_disposition,
    const std::string& referrer_charset,
    const std::string& suggested_name,
    const std::string& mime_type,
    const std::string& default_name);

NET_EXPORT bool IsSafePortablePathComponent(const base::FilePath& component);

NET_EXPORT bool IsSafePortableRelativePath(const base::FilePath& path);

NET_EXPORT void GenerateSafeFileName(const std::string& mime_type,
                                     bool ignore_extension,
                                     base::FilePath* file_path);

}  

#endif  

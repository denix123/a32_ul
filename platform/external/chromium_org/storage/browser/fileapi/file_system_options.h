// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_OPTIONS_H_
#define STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_OPTIONS_H_

#include <string>
#include <vector>

#include "storage/browser/storage_browser_export.h"

namespace leveldb {
class Env;
}

namespace storage {

class STORAGE_EXPORT FileSystemOptions {
 public:
  enum ProfileMode {
    PROFILE_MODE_NORMAL = 0,
    PROFILE_MODE_INCOGNITO
  };

  
  
  
  
  
  
  FileSystemOptions(
      ProfileMode profile_mode,
      const std::vector<std::string>& additional_allowed_schemes,
      leveldb::Env* env_override);

  ~FileSystemOptions();

  
  bool is_incognito() const { return profile_mode_ == PROFILE_MODE_INCOGNITO; }

  
  
  
  
  const std::vector<std::string>& additional_allowed_schemes() const {
    return additional_allowed_schemes_;
  }

  leveldb::Env* env_override() const { return env_override_; }

 private:
  const ProfileMode profile_mode_;
  const std::vector<std::string> additional_allowed_schemes_;
  leveldb::Env* env_override_;
};

}  

#endif  

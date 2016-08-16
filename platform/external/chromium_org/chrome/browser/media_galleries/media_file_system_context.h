// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_FILE_SYSTEM_CONTEXT_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_FILE_SYSTEM_CONTEXT_H_


#include <string>

namespace base {
class FilePath;
}

class MediaFileSystemRegistry;

class MediaFileSystemContext {
 public:
  virtual ~MediaFileSystemContext() {}

  
  virtual bool RegisterFileSystem(const std::string& device_id,
                                  const std::string& fs_name,
                                  const base::FilePath& path) = 0;

  
  virtual void RevokeFileSystem(const std::string& fs_name) = 0;

  
  
  virtual base::FilePath GetRegisteredPath(
      const std::string& fs_name) const = 0;
};

#endif  

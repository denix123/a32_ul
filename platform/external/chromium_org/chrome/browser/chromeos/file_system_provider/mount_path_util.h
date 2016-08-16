// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_MOUNT_PATH_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_MOUNT_PATH_UTIL_H_

#include <string>

#include "base/files/file_path.h"
#include "storage/browser/fileapi/file_system_url.h"

class Profile;

namespace chromeos {
namespace file_system_provider {

class ProvidedFileSystemInterface;

namespace util {

base::FilePath GetMountPath(Profile* profile,
                            const std::string& extension_id,
                            const std::string& file_system_id);

bool IsFileSystemProviderLocalPath(const base::FilePath& local_path);

class FileSystemURLParser {
 public:
  explicit FileSystemURLParser(const storage::FileSystemURL& url);
  virtual ~FileSystemURLParser();

  
  
  bool Parse();

  ProvidedFileSystemInterface* file_system() const { return file_system_; }
  const base::FilePath& file_path() const { return file_path_; }

 private:
  storage::FileSystemURL url_;
  ProvidedFileSystemInterface* file_system_;
  base::FilePath file_path_;

  DISALLOW_COPY_AND_ASSIGN(FileSystemURLParser);
};

class LocalPathParser {
 public:
  LocalPathParser(Profile* profile, const base::FilePath& local_path);
  virtual ~LocalPathParser();

  
  
  bool Parse();

  ProvidedFileSystemInterface* file_system() const { return file_system_; }
  const base::FilePath& file_path() const { return file_path_; }

 private:
  Profile* profile_;
  base::FilePath local_path_;
  ProvidedFileSystemInterface* file_system_;
  base::FilePath file_path_;

  DISALLOW_COPY_AND_ASSIGN(LocalPathParser);
};
}  
}  
}  

#endif  

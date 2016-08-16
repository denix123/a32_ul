// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TEST_TEST_FILE_UTIL_H_
#define BASE_TEST_TEST_FILE_UTIL_H_


#include <string>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"

#if defined(OS_ANDROID)
#include <jni.h>
#include "base/basictypes.h"
#endif

namespace base {

class FilePath;

bool EvictFileFromSystemCacheWithRetry(const FilePath& file);

bool DieFileDie(const FilePath& file, bool recurse);

bool EvictFileFromSystemCache(const FilePath& file);

#if defined(OS_WIN)
bool VolumeSupportsADS(const FilePath& path);

bool HasInternetZoneIdentifier(const FilePath& full_path);
#endif  

bool MakeFileUnreadable(const FilePath& path) WARN_UNUSED_RESULT;
bool MakeFileUnwritable(const FilePath& path) WARN_UNUSED_RESULT;

class FilePermissionRestorer {
 public:
  explicit FilePermissionRestorer(const FilePath& path);
  ~FilePermissionRestorer();

 private:
  const FilePath path_;
  void* info_;  
  size_t length_;  

  DISALLOW_COPY_AND_ASSIGN(FilePermissionRestorer);
};

#if defined(OS_ANDROID)
bool RegisterContentUriTestUtils(JNIEnv* env);

FilePath InsertImageIntoMediaStore(const FilePath& path);
#endif  

}  

#endif  

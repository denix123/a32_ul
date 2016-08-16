// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_PROVIDER_LOGOS_LOGO_CACHE_H_
#define COMPONENTS_SEARCH_PROVIDER_LOGOS_LOGO_CACHE_H_

#include <string>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "components/search_provider_logos/logo_common.h"

namespace search_provider_logos {

class LogoCache {
 public:
  
  
  explicit LogoCache(const base::FilePath& cache_directory);
  virtual ~LogoCache();

  
  virtual void UpdateCachedLogoMetadata(const LogoMetadata& metadata);

  
  virtual const LogoMetadata* GetCachedLogoMetadata();

  
  
  virtual void SetCachedLogo(const EncodedLogo* logo);

  
  
  virtual scoped_ptr<EncodedLogo> GetCachedLogo();

 private:
  FRIEND_TEST_ALL_PREFIXES(LogoCacheSerializationTest, SerializeMetadata);
  FRIEND_TEST_ALL_PREFIXES(LogoCacheSerializationTest,
                           DeserializeCorruptMetadata);
  FRIEND_TEST_ALL_PREFIXES(LogoCacheTest, StoreAndRetrieveMetadata);
  FRIEND_TEST_ALL_PREFIXES(LogoCacheTest, RetrieveCorruptMetadata);
  FRIEND_TEST_ALL_PREFIXES(LogoCacheTest, RetrieveCorruptLogo);

  
  
  static scoped_ptr<LogoMetadata> LogoMetadataFromString(
      const std::string& str, int* logo_num_bytes);

  
  static void LogoMetadataToString(const LogoMetadata& metadata,
                                   int logo_num_bytes,
                                   std::string* str);

  
  base::FilePath GetLogoPath();

  
  base::FilePath GetMetadataPath();

  
  void UpdateMetadata(scoped_ptr<LogoMetadata> metadata);

  
  
  
  void ReadMetadataIfNeeded();

  
  void WriteMetadata();

  
  
  void WriteLogo(scoped_refptr<base::RefCountedMemory> encoded_image);

  
  void DeleteLogoAndMetadata();

  
  
  bool EnsureCacheDirectoryExists();

  
  base::FilePath cache_directory_;

  
  
  
  
  scoped_ptr<LogoMetadata> metadata_;
  bool metadata_is_valid_;

  
  
  
  int logo_num_bytes_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(LogoCache);
};

}  

#endif  

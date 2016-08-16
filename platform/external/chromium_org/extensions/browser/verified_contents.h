// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_VERIFIED_CONTENTS_H_
#define EXTENSIONS_BROWSER_VERIFIED_CONTENTS_H_

#include <map>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/version.h"

namespace extensions {

class VerifiedContents {
 public:
  
  
  
  
  
  
  
  
  
  static bool FixupBase64Encoding(std::string* input);

  
  VerifiedContents(const uint8* public_key, int public_key_size);
  ~VerifiedContents();

  
  
  
  
  
  bool InitFrom(const base::FilePath& path, bool ignore_invalid_signature);

  int block_size() const { return block_size_; }
  const std::string& extension_id() const { return extension_id_; }
  const base::Version& version() const { return version_; }

  bool HasTreeHashRoot(const base::FilePath& relative_path) const;

  bool TreeHashRootEquals(const base::FilePath& relative_path,
                          const std::string& expected) const;

  
  
  bool valid_signature() { return valid_signature_; }

 private:
  
  
  bool GetPayload(const base::FilePath& path,
                  std::string* payload,
                  bool ignore_invalid_signature);

  
  
  
  
  bool VerifySignature(const std::string& protected_value,
                       const std::string& payload,
                       const std::string& signature_bytes);

  
  const uint8* public_key_;
  const int public_key_size_;

  
  bool valid_signature_;

  
  int block_size_;

  
  std::string extension_id_;
  base::Version version_;

  
  
  
  
  
  
  
  
  
  typedef std::multimap<base::FilePath::StringType, std::string> RootHashes;
  RootHashes root_hashes_;

  DISALLOW_COPY_AND_ASSIGN(VerifiedContents);
};

}  

#endif  

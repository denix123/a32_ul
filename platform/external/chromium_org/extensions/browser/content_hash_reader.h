// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_CONTENT_HASH_READER_H_
#define EXTENSIONS_BROWSER_CONTENT_HASH_READER_H_

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/version.h"
#include "extensions/browser/content_verifier_delegate.h"

namespace extensions {

class VerifiedContents;

class ContentHashReader : public base::RefCountedThreadSafe<ContentHashReader> {
 public:
  
  
  ContentHashReader(const std::string& extension_id,
                    const base::Version& extension_version,
                    const base::FilePath& extension_root,
                    const base::FilePath& relative_path,
                    const ContentVerifierKey& key);

  const std::string& extension_id() const { return extension_id_; }
  const base::FilePath& relative_path() const { return relative_path_; }

  
  
  
  
  bool Init();

  
  
  bool content_exists() const { return content_exists_; }

  
  
  
  bool have_verified_contents() const { return have_verified_contents_; }
  bool have_computed_hashes() const { return have_computed_hashes_; }

  
  
  int block_count() const;
  int block_size() const;

  
  
  bool GetHashForBlock(int block_index, const std::string** result) const;

 private:
  friend class base::RefCountedThreadSafe<ContentHashReader>;
  virtual ~ContentHashReader();

  enum InitStatus { NOT_INITIALIZED, SUCCESS, FAILURE };

  std::string extension_id_;
  base::Version extension_version_;
  base::FilePath extension_root_;
  base::FilePath relative_path_;
  ContentVerifierKey key_;

  InitStatus status_;

  bool content_exists_;

  bool have_verified_contents_;
  bool have_computed_hashes_;

  
  int block_size_;

  scoped_ptr<VerifiedContents> verified_contents_;

  std::vector<std::string> hashes_;

  DISALLOW_COPY_AND_ASSIGN(ContentHashReader);
};

}  

#endif  

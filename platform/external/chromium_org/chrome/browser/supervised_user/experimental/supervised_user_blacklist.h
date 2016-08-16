// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_EXPERIMENTAL_SUPERVISED_USER_BLACKLIST_H_
#define CHROME_BROWSER_SUPERVISED_USER_EXPERIMENTAL_SUPERVISED_USER_BLACKLIST_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sha1.h"

namespace base {
class FilePath;
}

class GURL;

class SupervisedUserBlacklist {
 public:
  struct Hash {
    Hash() {}
    explicit Hash(const std::string& host);
    bool operator<(const Hash& rhs) const;

    unsigned char data[base::kSHA1Length];
  };

  SupervisedUserBlacklist();
  ~SupervisedUserBlacklist();

  
  
  
  void ReadFromFile(const base::FilePath& path,
                    const base::Closure& done_callback);

  bool HasURL(const GURL& url) const;

  size_t GetEntryCount() const;

 private:
  void OnReadFromFileCompleted(const base::Closure& done_callback,
                               scoped_ptr<std::vector<Hash> > host_hashes);

  std::vector<Hash> host_hashes_;

  base::WeakPtrFactory<SupervisedUserBlacklist> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserBlacklist);
};

#endif  

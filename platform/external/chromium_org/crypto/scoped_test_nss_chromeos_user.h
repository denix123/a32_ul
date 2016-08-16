// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_SCOPED_TEST_NSS_CHROMEOS_USER_H_
#define CRYPTO_SCOPED_TEST_NSS_CHROMEOS_USER_H_

#include <string>

#include "base/files/scoped_temp_dir.h"
#include "base/macros.h"
#include "crypto/crypto_export.h"

namespace crypto {

class CRYPTO_EXPORT_PRIVATE ScopedTestNSSChromeOSUser {
 public:
  
  
  explicit ScopedTestNSSChromeOSUser(const std::string& username_hash);
  ~ScopedTestNSSChromeOSUser();

  std::string username_hash() const { return username_hash_; }
  bool constructed_successfully() const { return constructed_successfully_; }

  
  
  void FinishInit();

 private:
  const std::string username_hash_;
  base::ScopedTempDir temp_dir_;
  bool constructed_successfully_;

  DISALLOW_COPY_AND_ASSIGN(ScopedTestNSSChromeOSUser);
};

}  

#endif  

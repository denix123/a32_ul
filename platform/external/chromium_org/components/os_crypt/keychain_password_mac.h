// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OS_CRYPT_KEYCHAIN_PASSWORD_MAC_H_
#define COMPONENTS_OS_CRYPT_KEYCHAIN_PASSWORD_MAC_H_

#include <string>

#include "base/macros.h"

namespace crypto {
class AppleKeychain;
}

class KeychainPassword {
 public:
  explicit KeychainPassword(const crypto::AppleKeychain& keychain)
      : keychain_(keychain) {
  }

  
  
  
  
  
  
  std::string GetPassword() const;

 private:
  const crypto::AppleKeychain& keychain_;

  DISALLOW_COPY_AND_ASSIGN(KeychainPassword);
};

#endif  

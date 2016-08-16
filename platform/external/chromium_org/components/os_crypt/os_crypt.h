// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OS_CRYPT_OS_CRYPT_H_
#define COMPONENTS_OS_CRYPT_OS_CRYPT_H_

#include <string>

#include "base/strings/string16.h"

class OSCrypt {
 public:
  
  
  static bool EncryptString16(const base::string16& plaintext,
                              std::string* ciphertext);

  
  
  
  static bool DecryptString16(const std::string& ciphertext,
                              base::string16* plaintext);

  
  static bool EncryptString(const std::string& plaintext,
                            std::string* ciphertext);

  
  
  
  static bool DecryptString(const std::string& ciphertext,
                            std::string* plaintext);

#if defined(OS_MACOSX)
  
  
  static void UseMockKeychain(bool use_mock);
#endif

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(OSCrypt);
};

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_AUTH_KEY_H_
#define CHROMEOS_LOGIN_AUTH_KEY_H_

#include <string>

#include "chromeos/chromeos_export.h"

namespace chromeos {

class CHROMEOS_EXPORT Key {
 public:
  enum KeyType {
    
    KEY_TYPE_PASSWORD_PLAIN = 0,
    
    KEY_TYPE_SALTED_SHA256_TOP_HALF = 1,
    
    KEY_TYPE_SALTED_PBKDF2_AES256_1234 = 2,
    
    KEY_TYPE_SALTED_SHA256 = 3,

    
    KEY_TYPE_COUNT
  };

  Key();
  Key(const Key& other);
  explicit Key(const std::string& plain_text_password);
  Key(KeyType key_type, const std::string& salt, const std::string& secret);
  ~Key();

  bool operator==(const Key& other) const;

  KeyType GetKeyType() const;
  const std::string& GetSecret() const;
  const std::string& GetLabel() const;

  void SetLabel(const std::string& label);

  void ClearSecret();

  void Transform(KeyType target_key_type, const std::string& salt);

 private:
  KeyType key_type_;
  std::string salt_;
  std::string secret_;
  std::string label_;
};

}  

#endif  

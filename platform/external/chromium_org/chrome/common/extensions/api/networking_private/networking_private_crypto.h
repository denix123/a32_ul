// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_CRYPTO_H_
#define CHROME_COMMON_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_CRYPTO_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "base/basictypes.h"

namespace networking_private_crypto {

bool VerifyCredentials(const std::string& certificate,
                       const std::string& signature,
                       const std::string& data,
                       const std::string& connected_mac);

bool EncryptByteString(const std::vector<uint8_t>& public_key,
                       const std::string& data,
                       std::vector<uint8_t>* encrypted_output);

bool DecryptByteString(const std::string& private_key_pem,
                       const std::vector<uint8_t>& encrypted_data,
                       std::string* decrypted_output);

extern const uint8_t kTrustedCAPublicKeyDER[];

extern const size_t kTrustedCAPublicKeyDERLength;

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_OPENSSL_UTIL_OPENSSL_H_
#define CONTENT_CHILD_WEBCRYPTO_OPENSSL_UTIL_OPENSSL_H_

#include <vector>

#include <openssl/ossl_typ.h>

#include "third_party/WebKit/public/platform/WebCryptoAlgorithm.h"
#include "third_party/WebKit/public/platform/WebCryptoKey.h"

namespace content {

namespace webcrypto {

class CryptoData;
class Status;

enum EncryptOrDecrypt { DECRYPT=0, ENCRYPT=1 };

const EVP_MD* GetDigest(blink::WebCryptoAlgorithmId id);

//   * |buffer| where the ciphertext or plaintext is written to.
Status AeadEncryptDecrypt(EncryptOrDecrypt mode,
                          const std::vector<uint8_t>& raw_key,
                          const CryptoData& data,
                          unsigned int tag_length_bytes,
                          const CryptoData& iv,
                          const CryptoData& additional_data,
                          const EVP_AEAD* aead_alg,
                          std::vector<uint8_t>* buffer);

}  

}  

#endif  

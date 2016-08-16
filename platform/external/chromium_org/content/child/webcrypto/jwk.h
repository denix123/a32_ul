// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_JWK_H_
#define CONTENT_CHILD_WEBCRYPTO_JWK_H_

#include <stdint.h>
#include <vector>

#include "base/strings/string_piece.h"
#include "base/values.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebArrayBuffer.h"
#include "third_party/WebKit/public/platform/WebCrypto.h"
#include "third_party/WebKit/public/platform/WebCryptoAlgorithmParams.h"

namespace content {

namespace webcrypto {

class CryptoData;
class Status;

void WriteSecretKeyJwk(const CryptoData& raw_key_data,
                       const std::string& algorithm,
                       bool extractable,
                       blink::WebCryptoKeyUsageMask usage_mask,
                       std::vector<uint8_t>* jwk_key_data);

Status ReadSecretKeyJwk(const CryptoData& key_data,
                        const std::string& expected_algorithm,
                        bool expected_extractable,
                        blink::WebCryptoKeyUsageMask expected_usage_mask,
                        std::vector<uint8_t>* raw_key_data);

std::string MakeJwkAesAlgorithmName(const std::string& suffix,
                                    unsigned int keylen_bytes);

Status ReadAesSecretKeyJwk(const CryptoData& key_data,
                           const std::string& algorithm_name_suffix,
                           bool expected_extractable,
                           blink::WebCryptoKeyUsageMask expected_usage_mask,
                           std::vector<uint8_t>* raw_key_data);

void WriteRsaPublicKeyJwk(const CryptoData& n,
                          const CryptoData& e,
                          const std::string& algorithm,
                          bool extractable,
                          blink::WebCryptoKeyUsageMask usage_mask,
                          std::vector<uint8_t>* jwk_key_data);

void WriteRsaPrivateKeyJwk(const CryptoData& n,
                           const CryptoData& e,
                           const CryptoData& d,
                           const CryptoData& p,
                           const CryptoData& q,
                           const CryptoData& dp,
                           const CryptoData& dq,
                           const CryptoData& qi,
                           const std::string& algorithm,
                           bool extractable,
                           blink::WebCryptoKeyUsageMask usage_mask,
                           std::vector<uint8_t>* jwk_key_data);

struct JwkRsaInfo {
  JwkRsaInfo();
  ~JwkRsaInfo();

  bool is_private_key;
  std::string n;
  std::string e;
  std::string d;
  std::string p;
  std::string q;
  std::string dp;
  std::string dq;
  std::string qi;
};

Status ReadRsaKeyJwk(const CryptoData& key_data,
                     const std::string& expected_algorithm,
                     bool expected_extractable,
                     blink::WebCryptoKeyUsageMask expected_usage_mask,
                     JwkRsaInfo* result);

const char* GetJwkHmacAlgorithmName(blink::WebCryptoAlgorithmId hash);

CONTENT_EXPORT bool Base64DecodeUrlSafe(const std::string& input,
                                        std::string* output);

CONTENT_EXPORT std::string Base64EncodeUrlSafe(const base::StringPiece& input);
CONTENT_EXPORT std::string Base64EncodeUrlSafe(
    const std::vector<uint8_t>& input);

}  

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_OPENSSL_RSA_KEY_OPENSSL_H_
#define CONTENT_CHILD_WEBCRYPTO_OPENSSL_RSA_KEY_OPENSSL_H_

#include "content/child/webcrypto/algorithm_implementation.h"

namespace content {

namespace webcrypto {

class PublicKeyNss;
class PrivateKeyNss;

class RsaHashedAlgorithm : public AlgorithmImplementation {
 public:
  
  
  
  
  
  
  
  
  
  
  RsaHashedAlgorithm(blink::WebCryptoKeyUsageMask all_public_key_usages,
                     blink::WebCryptoKeyUsageMask all_private_key_usages)
      : all_public_key_usages_(all_public_key_usages),
        all_private_key_usages_(all_private_key_usages) {}

  
  virtual const char* GetJwkAlgorithm(
      const blink::WebCryptoAlgorithmId hash) const = 0;

  virtual Status VerifyKeyUsagesBeforeGenerateKeyPair(
      blink::WebCryptoKeyUsageMask combined_usage_mask,
      blink::WebCryptoKeyUsageMask* public_usage_mask,
      blink::WebCryptoKeyUsageMask* private_usage_mask) const OVERRIDE;

  virtual Status GenerateKeyPair(
      const blink::WebCryptoAlgorithm& algorithm,
      bool extractable,
      blink::WebCryptoKeyUsageMask public_usage_mask,
      blink::WebCryptoKeyUsageMask private_usage_mask,
      blink::WebCryptoKey* public_key,
      blink::WebCryptoKey* private_key) const OVERRIDE;

  virtual Status VerifyKeyUsagesBeforeImportKey(
      blink::WebCryptoKeyFormat format,
      blink::WebCryptoKeyUsageMask usage_mask) const OVERRIDE;

  virtual Status ImportKeyPkcs8(const CryptoData& key_data,
                                const blink::WebCryptoAlgorithm& algorithm,
                                bool extractable,
                                blink::WebCryptoKeyUsageMask usage_mask,
                                blink::WebCryptoKey* key) const OVERRIDE;

  virtual Status ImportKeySpki(const CryptoData& key_data,
                               const blink::WebCryptoAlgorithm& algorithm,
                               bool extractable,
                               blink::WebCryptoKeyUsageMask usage_mask,
                               blink::WebCryptoKey* key) const OVERRIDE;

  virtual Status ImportKeyJwk(const CryptoData& key_data,
                              const blink::WebCryptoAlgorithm& algorithm,
                              bool extractable,
                              blink::WebCryptoKeyUsageMask usage_mask,
                              blink::WebCryptoKey* key) const OVERRIDE;

  virtual Status ExportKeyPkcs8(const blink::WebCryptoKey& key,
                                std::vector<uint8_t>* buffer) const OVERRIDE;

  virtual Status ExportKeySpki(const blink::WebCryptoKey& key,
                               std::vector<uint8_t>* buffer) const OVERRIDE;

  virtual Status ExportKeyJwk(const blink::WebCryptoKey& key,
                              std::vector<uint8_t>* buffer) const OVERRIDE;

 private:
  blink::WebCryptoKeyUsageMask all_public_key_usages_;
  blink::WebCryptoKeyUsageMask all_private_key_usages_;
};

}  

}  

#endif  

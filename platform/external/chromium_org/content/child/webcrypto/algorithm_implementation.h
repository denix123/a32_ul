// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_ALGORITHM_IMPLEMENTATION_H_
#define CONTENT_CHILD_WEBCRYPTO_ALGORITHM_IMPLEMENTATION_H_

#include <stdint.h>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "third_party/WebKit/public/platform/WebCrypto.h"

namespace content {

namespace webcrypto {

class CryptoData;
class Status;

class AlgorithmImplementation {
 public:
  virtual ~AlgorithmImplementation();

  
  virtual Status Encrypt(const blink::WebCryptoAlgorithm& algorithm,
                         const blink::WebCryptoKey& key,
                         const CryptoData& data,
                         std::vector<uint8_t>* buffer) const;

  
  virtual Status Decrypt(const blink::WebCryptoAlgorithm& algorithm,
                         const blink::WebCryptoKey& key,
                         const CryptoData& data,
                         std::vector<uint8_t>* buffer) const;

  
  virtual Status Sign(const blink::WebCryptoAlgorithm& algorithm,
                      const blink::WebCryptoKey& key,
                      const CryptoData& data,
                      std::vector<uint8_t>* buffer) const;

  
  virtual Status Verify(const blink::WebCryptoAlgorithm& algorithm,
                        const blink::WebCryptoKey& key,
                        const CryptoData& signature,
                        const CryptoData& data,
                        bool* signature_match) const;

  
  virtual Status Digest(const blink::WebCryptoAlgorithm& algorithm,
                        const CryptoData& data,
                        std::vector<uint8_t>* buffer) const;

  
  
  virtual Status VerifyKeyUsagesBeforeGenerateKey(
      blink::WebCryptoKeyUsageMask usage_mask) const;

  
  virtual Status GenerateSecretKey(const blink::WebCryptoAlgorithm& algorithm,
                                   bool extractable,
                                   blink::WebCryptoKeyUsageMask usage_mask,
                                   blink::WebCryptoKey* key) const;

  
  
  virtual Status VerifyKeyUsagesBeforeGenerateKeyPair(
      blink::WebCryptoKeyUsageMask combined_usage_mask,
      blink::WebCryptoKeyUsageMask* public_usage_mask,
      blink::WebCryptoKeyUsageMask* private_usage_mask) const;

  
  virtual Status GenerateKeyPair(
      const blink::WebCryptoAlgorithm& algorithm,
      bool extractable,
      blink::WebCryptoKeyUsageMask public_usage_mask,
      blink::WebCryptoKeyUsageMask private_usage_mask,
      blink::WebCryptoKey* public_key,
      blink::WebCryptoKey* private_key) const;

  
  
  

  
  
  
  
  
  
  
  
  
  
  
  
  virtual Status VerifyKeyUsagesBeforeImportKey(
      blink::WebCryptoKeyFormat format,
      blink::WebCryptoKeyUsageMask usage_mask) const;

  
  
  virtual Status ImportKeyRaw(const CryptoData& key_data,
                              const blink::WebCryptoAlgorithm& algorithm,
                              bool extractable,
                              blink::WebCryptoKeyUsageMask usage_mask,
                              blink::WebCryptoKey* key) const;

  
  
  virtual Status ImportKeyPkcs8(const CryptoData& key_data,
                                const blink::WebCryptoAlgorithm& algorithm,
                                bool extractable,
                                blink::WebCryptoKeyUsageMask usage_mask,
                                blink::WebCryptoKey* key) const;

  
  
  virtual Status ImportKeySpki(const CryptoData& key_data,
                               const blink::WebCryptoAlgorithm& algorithm,
                               bool extractable,
                               blink::WebCryptoKeyUsageMask usage_mask,
                               blink::WebCryptoKey* key) const;

  
  
  virtual Status ImportKeyJwk(const CryptoData& key_data,
                              const blink::WebCryptoAlgorithm& algorithm,
                              bool extractable,
                              blink::WebCryptoKeyUsageMask usage_mask,
                              blink::WebCryptoKey* key) const;

  
  
  

  virtual Status ExportKeyRaw(const blink::WebCryptoKey& key,
                              std::vector<uint8_t>* buffer) const;

  virtual Status ExportKeyPkcs8(const blink::WebCryptoKey& key,
                                std::vector<uint8_t>* buffer) const;

  virtual Status ExportKeySpki(const blink::WebCryptoKey& key,
                               std::vector<uint8_t>* buffer) const;

  virtual Status ExportKeyJwk(const blink::WebCryptoKey& key,
                              std::vector<uint8_t>* buffer) const;
};

}  

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_NSS_AES_NSS_H_
#define CONTENT_CHILD_WEBCRYPTO_NSS_AES_NSS_H_

#include <pkcs11t.h>

#include "content/child/webcrypto/algorithm_implementation.h"

namespace content {

namespace webcrypto {

class AesAlgorithm : public AlgorithmImplementation {
 public:
  
  
  
  
  
  
  
  AesAlgorithm(CK_MECHANISM_TYPE import_mechanism,
               CK_FLAGS import_flags,
               blink::WebCryptoKeyUsageMask all_key_usages,
               const std::string& jwk_suffix);

  
  
  
  
  AesAlgorithm(CK_MECHANISM_TYPE import_mechanism,
               const std::string& jwk_suffix);

  virtual Status VerifyKeyUsagesBeforeGenerateKey(
      blink::WebCryptoKeyUsageMask usage_mask) const OVERRIDE;

  virtual Status GenerateSecretKey(const blink::WebCryptoAlgorithm& algorithm,
                                   bool extractable,
                                   blink::WebCryptoKeyUsageMask usage_mask,
                                   blink::WebCryptoKey* key) const OVERRIDE;

  virtual Status VerifyKeyUsagesBeforeImportKey(
      blink::WebCryptoKeyFormat format,
      blink::WebCryptoKeyUsageMask usage_mask) const OVERRIDE;

  virtual Status ImportKeyRaw(const CryptoData& key_data,
                              const blink::WebCryptoAlgorithm& algorithm,
                              bool extractable,
                              blink::WebCryptoKeyUsageMask usage_mask,
                              blink::WebCryptoKey* key) const OVERRIDE;

  virtual Status ImportKeyJwk(const CryptoData& key_data,
                              const blink::WebCryptoAlgorithm& algorithm,
                              bool extractable,
                              blink::WebCryptoKeyUsageMask usage_mask,
                              blink::WebCryptoKey* key) const OVERRIDE;

  virtual Status ExportKeyRaw(const blink::WebCryptoKey& key,
                              std::vector<uint8_t>* buffer) const OVERRIDE;

  virtual Status ExportKeyJwk(const blink::WebCryptoKey& key,
                              std::vector<uint8_t>* buffer) const OVERRIDE;

 private:
  const CK_MECHANISM_TYPE import_mechanism_;
  const CK_FLAGS import_flags_;
  const blink::WebCryptoKeyUsageMask all_key_usages_;
  const std::string jwk_suffix_;
};

}  

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_STATUS_H_
#define CONTENT_CHILD_WEBCRYPTO_STATUS_H_

#include <string>
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebCrypto.h"

namespace content {

namespace webcrypto {

class CONTENT_EXPORT Status {
 public:
  Status() : type_(TYPE_ERROR) {}

  
  bool IsError() const;

  
  bool IsSuccess() const;

  
  const std::string& error_details() const { return error_details_; }

  blink::WebCryptoErrorType error_type() const { return error_type_; }

  
  static Status Success();

  
  
  static Status OperationError();

  
  
  static Status DataError();

  
  
  

  
  
  
  static Status ErrorJwkNotDictionary();

  
  static Status ErrorJwkPropertyMissing(const std::string& property);

  
  static Status ErrorJwkPropertyWrongType(const std::string& property,
                                          const std::string& expected_type);

  
  
  static Status ErrorJwkBase64Decode(const std::string& property);

  
  
  static Status ErrorJwkExtInconsistent();

  
  
  static Status ErrorJwkAlgorithmInconsistent();

  
  
  static Status ErrorJwkUnrecognizedUse();

  
  
  static Status ErrorJwkUnrecognizedKeyop();

  
  
  static Status ErrorJwkUseInconsistent();

  
  
  static Status ErrorJwkKeyopsInconsistent();

  
  
  static Status ErrorJwkUseAndKeyopsInconsistent();

  
  
  static Status ErrorJwkUnexpectedKty(const std::string& expected);

  
  
  
  
  static Status ErrorJwkIncorrectKeyLength();

  
  
  static Status ErrorJwkEmptyBigInteger(const std::string& property);

  
  
  static Status ErrorJwkBigIntegerHasLeadingZero(const std::string& property);

  
  
  

  
  
  
  static Status ErrorImportEmptyKeyData();

  
  
  static Status ErrorUnsupportedImportKeyFormat();

  
  
  static Status ErrorUnsupportedExportKeyFormat();

  
  
  static Status ErrorImportAesKeyLength();

  
  static Status ErrorAes192BitUnsupported();

  
  
  
  static Status ErrorUnexpectedKeyType();

  
  
  static Status ErrorIncorrectSizeAesCbcIv();

  
  
  static Status ErrorIncorrectSizeAesCtrCounter();

  
  
  static Status ErrorInvalidAesCtrCounterLength();

  
  
  static Status ErrorAesCtrInputTooLongCounterRepeated();

  
  
  
  static Status ErrorDataTooLarge();

  
  
  
  static Status ErrorDataTooSmall();

  
  
  
  static Status ErrorUnsupported();
  static Status ErrorUnsupported(const std::string& message);

  
  
  
  static Status ErrorUnexpected();

  
  
  static Status ErrorInvalidAesGcmTagLength();

  
  
  static Status ErrorInvalidAesKwDataLength();

  
  
  static Status ErrorGenerateKeyPublicExponent();

  
  static Status ErrorImportRsaEmptyModulus();

  
  static Status ErrorGenerateRsaUnsupportedModulus();

  
  static Status ErrorImportRsaEmptyExponent();

  
  static Status ErrorKeyNotExtractable();

  
  
  static Status ErrorGenerateKeyLength();

  
  
  
  static Status ErrorCreateKeyBadUsages();

 private:
  enum Type { TYPE_ERROR, TYPE_SUCCESS };

  
  Status(blink::WebCryptoErrorType error_type,
         const std::string& error_details_utf8);

  
  explicit Status(Type type);

  Type type_;
  blink::WebCryptoErrorType error_type_;
  std::string error_details_;
};

}  

}  

#endif  

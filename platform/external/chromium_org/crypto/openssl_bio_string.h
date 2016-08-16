// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_OPENSSL_BIO_STRING_H_
#define CRYPTO_OPENSSL_BIO_STRING_H_

#include <string>

#include "crypto/crypto_export.h"

typedef struct bio_st BIO;

namespace crypto {

CRYPTO_EXPORT BIO* BIO_new_string(std::string* out);

}  

#endif  


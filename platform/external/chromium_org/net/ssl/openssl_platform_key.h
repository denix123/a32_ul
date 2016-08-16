// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_OPENSSL_PLATFORM_KEY_H_
#define NET_SSL_OPENSSL_PLATFORM_KEY_H_

#include "crypto/scoped_openssl_types.h"

namespace net {

class X509Certificate;

crypto::ScopedEVP_PKEY FetchClientCertPrivateKey(
    const X509Certificate* certificate);

}  

#endif  

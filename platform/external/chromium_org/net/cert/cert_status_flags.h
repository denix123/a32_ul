// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_CERT_CERT_STATUS_FLAGS_H_
#define NET_CERT_CERT_STATUS_FLAGS_H_

#include "base/basictypes.h"
#include "net/base/net_export.h"

namespace net {

typedef uint32 CertStatus;

#define CERT_STATUS_FLAG(label, value) \
    CertStatus static const CERT_STATUS_##label = value;
#include "net/cert/cert_status_flags_list.h"
#undef CERT_STATUS_FLAG

static const CertStatus CERT_STATUS_ALL_ERRORS = 0xFFFF;

static inline bool IsCertStatusError(CertStatus status) {
  return (CERT_STATUS_ALL_ERRORS & status) != 0;
}

NET_EXPORT bool IsCertStatusMinorError(CertStatus cert_status);

NET_EXPORT CertStatus MapNetErrorToCertStatus(int error);

NET_EXPORT int MapCertStatusToNetError(CertStatus cert_status);

}  

#endif  

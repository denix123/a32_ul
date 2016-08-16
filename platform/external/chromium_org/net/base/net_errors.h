// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_NET_ERRORS_H__
#define NET_BASE_NET_ERRORS_H__

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file.h"
#include "net/base/net_export.h"

namespace net {

NET_EXPORT extern const char kErrorDomain[];

enum Error {
  
  OK = 0,

#define NET_ERROR(label, value) ERR_ ## label = value,
#include "net/base/net_error_list.h"
#undef NET_ERROR

  
  ERR_CERT_BEGIN = ERR_CERT_COMMON_NAME_INVALID,
};

NET_EXPORT std::string ErrorToString(int error);

NET_EXPORT std::string ErrorToShortString(int error);

NET_EXPORT bool IsCertificateError(int error);

NET_EXPORT Error MapSystemError(int os_error);

NET_EXPORT std::vector<int> GetAllErrorCodesForUma();

NET_EXPORT Error FileErrorToNetError(base::File::Error file_error);

}  

#endif  

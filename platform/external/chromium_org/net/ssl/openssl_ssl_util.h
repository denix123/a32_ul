// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_OPENSSL_SSL_UTIL_H_
#define NET_SSL_OPENSSL_SSL_UTIL_H_

#include "net/base/net_log.h"

namespace crypto {
class OpenSSLErrStackTracer;
}

namespace tracked_objects {
class Location;
}

namespace net {

void OpenSSLPutNetError(const tracked_objects::Location& posted_from, int err);

struct SslSetClearMask {
  SslSetClearMask();
  void ConfigureFlag(long flag, bool state);

  long set_mask;
  long clear_mask;
};

int MapOpenSSLError(int err, const crypto::OpenSSLErrStackTracer& tracer);

struct OpenSSLErrorInfo {
  OpenSSLErrorInfo() : error_code(0), file(NULL), line(0) {}

  uint32_t error_code;
  const char* file;
  int line;
};

int MapOpenSSLErrorWithDetails(int err,
                               const crypto::OpenSSLErrStackTracer& tracer,
                               OpenSSLErrorInfo* out_error_info);

NetLog::ParametersCallback CreateNetLogOpenSSLErrorCallback(
    int net_error,
    int ssl_error,
    const OpenSSLErrorInfo& error_info);

}  

#endif  

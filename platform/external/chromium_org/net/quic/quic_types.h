// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_TYPES_H_
#define NET_QUIC_QUIC_TYPES_H_


#include <stddef.h>
#include <ostream>

#include "net/base/net_export.h"

namespace net {

struct NET_EXPORT_PRIVATE QuicConsumedData {
  QuicConsumedData(size_t bytes_consumed, bool fin_consumed);

  
  
  
  
  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicConsumedData& s);

  
  size_t bytes_consumed;

  
  bool fin_consumed;
};

enum QuicAsyncStatus {
  QUIC_SUCCESS = 0,
  QUIC_FAILURE = 1,
  
  
  QUIC_PENDING = 2,
};

enum WriteStatus {
  WRITE_STATUS_OK,
  WRITE_STATUS_BLOCKED,
  WRITE_STATUS_ERROR,
};

// of bytes written or the error code, depending upon the status.
struct NET_EXPORT_PRIVATE WriteResult {
  WriteResult(WriteStatus status, int bytes_written_or_error_code);
  WriteResult();

  WriteStatus status;
  union {
    int bytes_written;  
    int error_code;  
  };
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_CHILD_REQUEST_PEER_H_
#define CONTENT_PUBLIC_CHILD_REQUEST_PEER_H_

#include <string>

#include "base/basictypes.h"
#include "content/common/content_export.h"

class GURL;

namespace base {
class TimeTicks;
}

namespace net {
struct RedirectInfo;
}

namespace content {

struct ResourceResponseInfo;

class CONTENT_EXPORT RequestPeer {
 public:
  
  
  virtual void OnUploadProgress(uint64 position, uint64 size) = 0;

  
  
  
  
  virtual bool OnReceivedRedirect(const net::RedirectInfo& redirect_info,
                                  const ResourceResponseInfo& info) = 0;

  
  
  virtual void OnReceivedResponse(const ResourceResponseInfo& info) = 0;

  
  
  
  
  
  
  
  virtual void OnDownloadedData(int len, int encoded_data_length) = 0;

  
  
  
  
  
  virtual void OnReceivedData(const char* data,
                              int data_length,
                              int encoded_data_length) = 0;

  
  
  virtual void OnReceivedCachedMetadata(const char* data, int len) {}

  
  
  virtual void OnCompletedRequest(int error_code,
                                  bool was_ignored_by_handler,
                                  bool stale_copy_in_cache,
                                  const std::string& security_info,
                                  const base::TimeTicks& completion_time,
                                  int64 total_transfer_size) = 0;

 protected:
  virtual ~RequestPeer() {}
};

}  

#endif  

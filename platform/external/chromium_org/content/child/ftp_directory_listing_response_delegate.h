// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_FTP_DIRECTORY_LISTING_RESPONSE_DELEGATE_H_
#define CONTENT_CHILD_FTP_DIRECTORY_LISTING_RESPONSE_DELEGATE_H_

#include <string>

#include "base/basictypes.h"
#include "third_party/WebKit/public/platform/WebURLResponse.h"

namespace blink {
class WebURLLoader;
class WebURLLoaderClient;
}

class GURL;

namespace content {

class FtpDirectoryListingResponseDelegate {
 public:
  FtpDirectoryListingResponseDelegate(blink::WebURLLoaderClient* client,
                                      blink::WebURLLoader* loader,
                                      const blink::WebURLResponse& response);

  
  void Cancel();

  
  void OnReceivedData(const char* data, int data_len);
  void OnCompletedRequest();

 private:
  void Init(const GURL& response_url);

  void SendDataToClient(const std::string& data);

  
  
  blink::WebURLLoaderClient* client_;
  blink::WebURLLoader* loader_;

  
  std::string buffer_;

  DISALLOW_COPY_AND_ASSIGN(FtpDirectoryListingResponseDelegate);
};

}  

#endif  

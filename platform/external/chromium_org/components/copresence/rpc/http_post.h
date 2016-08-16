// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_RPC_HTTP_POST_H_
#define COMPONENTS_COPRESENCE_RPC_HTTP_POST_H_

#include <string>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "net/url_request/url_fetcher_delegate.h"

namespace google {
namespace protobuf {
class MessageLite;
}
}

namespace net {
class URLRequestContextGetter;
}

namespace copresence {

class HttpPost : public net::URLFetcherDelegate {
 public:
  
  
  typedef base::Callback<void(int, const std::string&)>
      ResponseCallback;

  
  
  
  HttpPost(net::URLRequestContextGetter* url_context_getter,
           const std::string& server_host,
           const std::string& rpc_name,
           const std::string& tracing_token,
           std::string api_key,  
           const google::protobuf::MessageLite& request_proto);

  
  virtual ~HttpPost();

  
  void Start(const ResponseCallback& response_callback);

 private:
  static const int kUrlFetcherId = 1;
  static const char kApiKeyField[];
  static const char kTracingField[];

  friend class HttpPostTest;

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  ResponseCallback response_callback_;

  scoped_ptr<net::URLFetcher> url_fetcher_;

  DISALLOW_COPY_AND_ASSIGN(HttpPost);
};

}  

#endif  

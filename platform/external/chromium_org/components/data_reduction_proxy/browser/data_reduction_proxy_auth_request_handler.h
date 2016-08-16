// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_AUTH_REQUEST_HANDLER_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_AUTH_REQUEST_HANDLER_H_

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "url/gurl.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace net {
class HostPortPair;
class HttpRequestHeaders;
class HttpResponseHeaders;
class ProxyServer;
class URLRequest;
}

namespace data_reduction_proxy {

#if defined(OS_ANDROID)
extern const char kAndroidWebViewProtocolVersion[];
#endif

extern const char kClientAndroidWebview[];
extern const char kClientChromeAndroid[];
extern const char kClientChromeIOS[];

class DataReductionProxyParams;

class DataReductionProxyAuthRequestHandler {
 public:
  static bool IsKeySetOnCommandLine();

  
  
  DataReductionProxyAuthRequestHandler(
      const std::string& client,
      DataReductionProxyParams* params,
      scoped_refptr<base::SingleThreadTaskRunner> network_task_runner);

  virtual ~DataReductionProxyAuthRequestHandler();

  
  
  
  
  void MaybeAddRequestHeader(net::URLRequest* request,
                             const net::ProxyServer& proxy_server,
                             net::HttpRequestHeaders* request_headers);

  
  
  
  
  void MaybeAddProxyTunnelRequestHandler(
      const net::HostPortPair& proxy_server,
      net::HttpRequestHeaders* request_headers);

  
  
  
  
  
  
  
  void InitAuthentication(const std::string& key);

 protected:
  void Init();

  void AddAuthorizationHeader(net::HttpRequestHeaders* headers);

  
  
  
  static base::string16 AuthHashForSalt(int64 salt,
                                        const std::string& key);
  
  virtual base::Time Now() const;
  virtual void RandBytes(void* output, size_t length);

  
  virtual std::string GetDefaultKey() const;

  
  DataReductionProxyAuthRequestHandler(
      const std::string& client,
      const std::string& version,
      DataReductionProxyParams* params,
      scoped_refptr<base::SingleThreadTaskRunner> network_task_runner);

 private:
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyAuthRequestHandlerTest,
                           AuthorizationOnIO);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyAuthRequestHandlerTest,
                           AuthorizationIgnoresEmptyKey);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyAuthRequestHandlerTest,
                           AuthorizationBogusVersion);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyAuthRequestHandlerTest,
                           AuthHashForSalt);

  
  std::string ChromiumVersion() const;

  
  
  void GetChromiumBuildAndPatch(const std::string& version,
                                std::string* build,
                                std::string* patch) const;

  
  
  void ComputeCredentials(const base::Time& now,
                          std::string* session,
                          std::string* credentials);

  
  
  
  
  void MaybeAddRequestHeaderImpl(const net::HostPortPair& proxy_server,
                                 bool expect_ssl,
                                 net::HttpRequestHeaders* request_headers);

  
  std::string key_;

  
  std::string session_;
  std::string credentials_;

  
  
  std::string client_;
  std::string build_number_;
  std::string patch_number_;

  
  
  base::Time last_update_time_;

  DataReductionProxyParams* data_reduction_proxy_params_;

  scoped_refptr<base::SingleThreadTaskRunner> network_task_runner_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyAuthRequestHandler);
};

}  
#endif  

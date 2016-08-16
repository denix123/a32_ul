// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_BROWSER_AW_SSL_HOST_STATE_DELEGATE_H_
#define ANDROID_WEBVIEW_BROWSER_AW_SSL_HOST_STATE_DELEGATE_H_

#include <map>
#include <string>

#include "content/public/browser/ssl_host_state_delegate.h"
#include "net/base/hash_value.h"
#include "net/cert/cert_status_flags.h"
#include "net/cert/x509_certificate.h"

namespace android_webview {

namespace internal {
class CertPolicy {
 public:
  CertPolicy();
  ~CertPolicy();
  
  
  
  bool Check(const net::X509Certificate& cert, net::CertStatus error) const;

  
  
  void Allow(const net::X509Certificate& cert, net::CertStatus error);

 private:
  
  std::map<net::SHA256HashValue, net::CertStatus, net::SHA256HashValueLessThan>
      allowed_;
};

}  

class AwSSLHostStateDelegate : public content::SSLHostStateDelegate {
 public:
  AwSSLHostStateDelegate();
  virtual ~AwSSLHostStateDelegate();

  
  
  void AllowCert(const std::string& host,
                 const net::X509Certificate& cert,
                 net::CertStatus error) override;

  void Clear() override;

  
  content::SSLHostStateDelegate::CertJudgment QueryPolicy(
      const std::string& host,
      const net::X509Certificate& cert,
      net::CertStatus error,
      bool* expired_previous_decision) override;

  
  void HostRanInsecureContent(const std::string& host, int pid) override;

  
  bool DidHostRunInsecureContent(const std::string& host,
                                 int pid) const override;

 private:
  
  std::map<std::string, internal::CertPolicy> cert_policy_for_host_;

  DISALLOW_COPY_AND_ASSIGN(AwSSLHostStateDelegate);
};

}  

#endif  

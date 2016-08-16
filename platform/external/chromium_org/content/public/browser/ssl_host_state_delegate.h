// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_SSL_HOST_STATE_DELEGATE_H_
#define CONTENT_PUBLIC_BROWSER_SSL_HOST_STATE_DELEGATE_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "content/common/content_export.h"
#include "net/cert/x509_certificate.h"

namespace content {

class SSLHostStateDelegate {
 public:
  
  enum CertJudgment {
    DENIED,
    ALLOWED
  };

  
  
  virtual void AllowCert(const std::string&,
                         const net::X509Certificate& cert,
                         net::CertStatus error) = 0;

  
  virtual void Clear() = 0;

  
  
  
  virtual CertJudgment QueryPolicy(const std::string& host,
                                   const net::X509Certificate& cert,
                                   net::CertStatus error,
                                   bool* expired_previous_decision) = 0;

  
  virtual void HostRanInsecureContent(const std::string& host, int pid) = 0;

  
  virtual bool DidHostRunInsecureContent(const std::string& host,
                                         int pid) const = 0;

 protected:
  virtual ~SSLHostStateDelegate() {}
};

}  

#endif  

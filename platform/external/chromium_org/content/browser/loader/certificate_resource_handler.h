// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_LOADER_CERTIFICATE_RESOURCE_HANDLER_H_
#define CONTENT_BROWSER_LOADER_CERTIFICATE_RESOURCE_HANDLER_H_

#include <string>
#include <utility>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/loader/resource_handler.h"
#include "net/base/mime_util.h"

namespace net {
class IOBuffer;
class URLRequest;
class URLRequestStatus;
}  

namespace content {

class CertificateResourceHandler : public ResourceHandler {
 public:
  explicit CertificateResourceHandler(net::URLRequest* request);
  virtual ~CertificateResourceHandler();

  virtual bool OnUploadProgress(uint64 position, uint64 size) OVERRIDE;

  
  virtual bool OnRequestRedirected(const net::RedirectInfo& redirect_info,
                                   ResourceResponse* resp,
                                   bool* defer) OVERRIDE;

  
  virtual bool OnResponseStarted(ResourceResponse* resp,
                                 bool* defer) OVERRIDE;

  
  virtual bool OnWillStart(const GURL& url, bool* defer) OVERRIDE;

  
  virtual bool OnBeforeNetworkStart(const GURL& url, bool* defer) OVERRIDE;

  
  virtual bool OnWillRead(scoped_refptr<net::IOBuffer>* buf,
                          int* buf_size,
                          int min_size) OVERRIDE;

  
  virtual bool OnReadCompleted(int bytes_read, bool* defer) OVERRIDE;

  
  virtual void OnResponseCompleted(const net::URLRequestStatus& urs,
                                   const std::string& sec_info,
                                   bool* defer) OVERRIDE;

  
  virtual void OnDataDownloaded(int bytes_downloaded) OVERRIDE;

 private:
  typedef std::vector<std::pair<scoped_refptr<net::IOBuffer>,
                                size_t> > ContentVector;

  void AssembleResource();

  size_t content_length_;
  ContentVector buffer_;
  scoped_refptr<net::IOBuffer> read_buffer_;
  scoped_refptr<net::IOBuffer> resource_buffer_;  
  net::CertificateMimeType cert_type_;
  DISALLOW_COPY_AND_ASSIGN(CertificateResourceHandler);
};

}  

#endif  

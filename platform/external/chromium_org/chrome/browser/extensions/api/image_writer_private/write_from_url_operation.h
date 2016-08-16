// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_WRITE_FROM_URL_OPERATION_H_
#define CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_WRITE_FROM_URL_OPERATION_H_

#include "chrome/browser/extensions/api/image_writer_private/operation.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}  

namespace extensions {
namespace image_writer {

class OperationManager;

class WriteFromUrlOperation : public Operation, public net::URLFetcherDelegate {
 public:
  WriteFromUrlOperation(base::WeakPtr<OperationManager> manager,
                        const ExtensionId& extension_id,
                        net::URLRequestContextGetter* request_context,
                        GURL url,
                        const std::string& hash,
                        const std::string& storage_unit_id);
  virtual void StartImpl() OVERRIDE;

 protected:
  virtual ~WriteFromUrlOperation();

  
  void GetDownloadTarget(const base::Closure& continuation);

  
  
  void Download(const base::Closure& continuation);

  
  
  void VerifyDownload(const base::Closure& continuation);

 private:
  
  
  
  void DestroyUrlFetcher();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;
  virtual void OnURLFetchDownloadProgress(const net::URLFetcher* source,
                                          int64 current,
                                          int64 total) OVERRIDE;
  virtual void OnURLFetchUploadProgress(const net::URLFetcher* source,
                                        int64 current,
                                        int64 total) OVERRIDE;

  void VerifyDownloadCompare(const base::Closure& continuation,
                             const std::string& download_hash);
  void VerifyDownloadComplete(const base::Closure& continuation);

  
  net::URLRequestContextGetter* request_context_;
  GURL url_;
  const std::string hash_;

  
  scoped_ptr<net::URLFetcher> url_fetcher_;
  base::Closure download_continuation_;
};

} 
} 

#endif  

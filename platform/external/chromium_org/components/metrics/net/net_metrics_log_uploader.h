// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_NET_NET_METRICS_LOG_UPLOADER_H_
#define COMPONENTS_METRICS_NET_NET_METRICS_LOG_UPLOADER_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "components/metrics/metrics_log_uploader.h"
#include "net/url_request/url_fetcher_delegate.h"

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}

namespace metrics {

class NetMetricsLogUploader : public MetricsLogUploader,
                              public net::URLFetcherDelegate {
 public:
  
  
  
  
  NetMetricsLogUploader(net::URLRequestContextGetter* request_context_getter,
                        const std::string& server_url,
                        const std::string& mime_type,
                        const base::Callback<void(int)>& on_upload_complete);
  virtual ~NetMetricsLogUploader();

  
  virtual bool UploadLog(const std::string& compressed_log_data,
                         const std::string& log_hash) OVERRIDE;

 private:
  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  net::URLRequestContextGetter* const request_context_getter_;

  
  scoped_ptr<net::URLFetcher> current_fetch_;

  DISALLOW_COPY_AND_ASSIGN(NetMetricsLogUploader);
};

}  

#endif  

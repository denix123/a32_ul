// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RAPPOR_LOG_UPLOADER_H_
#define COMPONENTS_RAPPOR_LOG_UPLOADER_H_

#include <queue>
#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "net/url_request/url_request_context_getter.h"
#include "url/gurl.h"

namespace net {
class URLFetcher;
}

namespace rappor {

class LogUploader : public net::URLFetcherDelegate {
 public:
  
  
  
  LogUploader(const GURL& server_url,
              const std::string& mime_type,
              net::URLRequestContextGetter* request_context);

  
  
  virtual ~LogUploader();

  
  
  
  void QueueLog(const std::string& log);

 protected:
  
  virtual bool IsUploadScheduled() const;

  
  
  virtual void ScheduleNextUpload(base::TimeDelta interval);

  
  void StartScheduledUpload();

  
  
  static base::TimeDelta BackOffUploadInterval(base::TimeDelta);

 private:
  
  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  void OnUploadFinished(bool server_is_healthy, bool more_logs_remaining);

  
  const GURL server_url_;

  
  const std::string mime_type_;

  
  scoped_refptr<net::URLRequestContextGetter> request_context_;

  
  scoped_ptr<net::URLFetcher> current_fetch_;

  
  std::queue<std::string> queued_logs_;

  
  base::OneShotTimer<LogUploader> upload_timer_;

  
  bool has_callback_pending_;

  
  
  base::TimeDelta upload_interval_;

  DISALLOW_COPY_AND_ASSIGN(LogUploader);
};

}  

#endif  

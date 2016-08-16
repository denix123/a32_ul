// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DOWNLOAD_DOWNLOAD_RESOURCE_HANDLER_H_
#define CONTENT_BROWSER_DOWNLOAD_DOWNLOAD_RESOURCE_HANDLER_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "content/browser/loader/resource_handler.h"
#include "content/public/browser/download_interrupt_reasons.h"
#include "content/public/browser/download_manager.h"
#include "content/public/browser/download_save_info.h"
#include "content/public/browser/download_url_parameters.h"

namespace net {
class URLRequest;
}  

namespace content {
class ByteStreamReader;
class ByteStreamWriter;
class DownloadRequestHandle;
class PowerSaveBlocker;
struct DownloadCreateInfo;

class CONTENT_EXPORT DownloadResourceHandler
    : public ResourceHandler,
      public base::SupportsWeakPtr<DownloadResourceHandler> {
 public:
  struct DownloadTabInfo;

  
  
  static const int kDownloadByteStreamSize;

  
  
  DownloadResourceHandler(
      uint32 id,
      net::URLRequest* request,
      const DownloadUrlParameters::OnStartedCallback& started_cb,
      scoped_ptr<DownloadSaveInfo> save_info);

  virtual bool OnUploadProgress(uint64 position, uint64 size) OVERRIDE;

  virtual bool OnRequestRedirected(const net::RedirectInfo& redirect_info,
                                   ResourceResponse* response,
                                   bool* defer) OVERRIDE;

  
  virtual bool OnResponseStarted(ResourceResponse* response,
                                 bool* defer) OVERRIDE;

  
  virtual bool OnWillStart(const GURL& url, bool* defer) OVERRIDE;

  
  virtual bool OnBeforeNetworkStart(const GURL& url, bool* defer) OVERRIDE;

  
  
  virtual bool OnWillRead(scoped_refptr<net::IOBuffer>* buf,
                          int* buf_size,
                          int min_size) OVERRIDE;

  virtual bool OnReadCompleted(int bytes_read, bool* defer) OVERRIDE;

  virtual void OnResponseCompleted(const net::URLRequestStatus& status,
                                   const std::string& security_info,
                                   bool* defer) OVERRIDE;

  
  virtual void OnDataDownloaded(int bytes_downloaded) OVERRIDE;

  void PauseRequest();
  void ResumeRequest();

  
  void CancelRequest();

  std::string DebugString() const;

 private:
  virtual ~DownloadResourceHandler();

  
  
  
  void CallStartedCB(DownloadItem* item,
                     DownloadInterruptReason interrupt_reason);

  uint32 download_id_;
  
  
  DownloadUrlParameters::OnStartedCallback started_cb_;
  scoped_ptr<DownloadSaveInfo> save_info_;

  
  
  
  
  DownloadTabInfo* tab_info_;

  
  scoped_refptr<net::IOBuffer> read_buffer_;       
  scoped_ptr<ByteStreamWriter> stream_writer_; 

  
  
  
  scoped_ptr<PowerSaveBlocker> power_save_blocker_;

  
  base::TimeTicks download_start_time_;
  base::TimeTicks last_read_time_;
  base::TimeTicks last_stream_pause_time_;
  base::TimeDelta total_pause_time_;
  size_t last_buffer_size_;
  int64 bytes_read_;

  int pause_count_;
  bool was_deferred_;

  
  bool on_response_started_called_;

  static const int kReadBufSize = 32768;  
  static const int kThrottleTimeMs = 200;  

  DISALLOW_COPY_AND_ASSIGN(DownloadResourceHandler);
};

}  

#endif  

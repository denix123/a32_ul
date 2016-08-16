// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_CRX_DOWNLOADER_H_
#define COMPONENTS_COMPONENT_UPDATER_CRX_DOWNLOADER_H_

#include <stdint.h>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "url/gurl.h"

namespace base {
class SequencedTaskRunner;
class SingleThreadTaskRunner;
}

namespace net {
class URLRequestContextGetter;
}

namespace component_updater {

class CrxDownloader {
 public:
  struct DownloadMetrics {
    enum Downloader { kNone = 0, kUrlFetcher, kBits };

    DownloadMetrics();

    GURL url;

    Downloader downloader;

    int error;

    int64_t downloaded_bytes;  
    int64_t total_bytes;

    uint64_t download_time_ms;
  };

  
  struct Result {
    Result();

    
    int error;

    
    base::FilePath response;

    
    
    int64_t downloaded_bytes;

    
    int64_t total_bytes;
  };

  
  
  
  
  
  typedef base::Callback<void(const Result& result)> DownloadCallback;

  
  
  
  
  typedef base::Callback<void(const Result& result)> ProgressCallback;

  
  
  
  
  
  
  static CrxDownloader* Create(
      bool is_background_download,
      net::URLRequestContextGetter* context_getter,
      scoped_refptr<base::SequencedTaskRunner> url_fetcher_task_runner,
      scoped_refptr<base::SingleThreadTaskRunner> background_task_runner);
  virtual ~CrxDownloader();

  void set_progress_callback(const ProgressCallback& progress_callback);

  
  
  
  
  void StartDownloadFromUrl(const GURL& url,
                            const DownloadCallback& download_callback);
  void StartDownload(const std::vector<GURL>& urls,
                     const DownloadCallback& download_callback);

  const std::vector<DownloadMetrics> download_metrics() const;

 protected:
  explicit CrxDownloader(scoped_ptr<CrxDownloader> successor);

  
  
  
  
  
  
  
  
  void OnDownloadComplete(bool is_handled,
                          const Result& result,
                          const DownloadMetrics& download_metrics);

  
  void OnDownloadProgress(const Result& result);

  
  GURL url() const;

 private:
  virtual void DoStartDownload(const GURL& url) = 0;

  base::ThreadChecker thread_checker_;

  std::vector<GURL> urls_;
  scoped_ptr<CrxDownloader> successor_;
  DownloadCallback download_callback_;
  ProgressCallback progress_callback_;

  std::vector<GURL>::iterator current_url_;

  std::vector<DownloadMetrics> download_metrics_;

  DISALLOW_COPY_AND_ASSIGN(CrxDownloader);
};

}  

#endif  

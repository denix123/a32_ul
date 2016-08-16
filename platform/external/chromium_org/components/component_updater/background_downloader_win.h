// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_BACKGROUND_DOWNLOADER_WIN_H_
#define COMPONENTS_COMPONENT_UPDATER_BACKGROUND_DOWNLOADER_WIN_H_

#include <windows.h>
#include <bits.h>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "base/win/scoped_comptr.h"
#include "components/component_updater/crx_downloader.h"

namespace base {
class FilePath;
class MessageLoopProxy;
class SingleThreadTaskRunner;
}

namespace component_updater {

class BackgroundDownloader : public CrxDownloader {
 protected:
  friend class CrxDownloader;
  BackgroundDownloader(scoped_ptr<CrxDownloader> successor,
                       net::URLRequestContextGetter* context_getter,
                       scoped_refptr<base::SingleThreadTaskRunner> task_runner);
  virtual ~BackgroundDownloader();

 private:
  
  virtual void DoStartDownload(const GURL& url) OVERRIDE;

  
  
  
  
  
  void BeginDownload(const GURL& url);
  void OnDownloading();
  void EndDownload(HRESULT hr);

  
  void OnStateTransferred();
  void OnStateError();
  void OnStateCancelled();
  void OnStateAcknowledged();

  
  
  void OnStateQueued();

  
  void OnStateTransientError();

  
  void OnStateTransferring();

  HRESULT QueueBitsJob(const GURL& url);
  HRESULT CreateOrOpenJob(const GURL& url);
  HRESULT InitializeNewJob(const GURL& url);

  
  
  bool IsStuck();

  
  
  HRESULT CompleteJob();

  
  base::ThreadChecker thread_checker_;

  
  
  scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;

  net::URLRequestContextGetter* context_getter_;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  
  
  
  scoped_ptr<base::RepeatingTimer<BackgroundDownloader> > timer_;

  base::win::ScopedComPtr<IBackgroundCopyManager> bits_manager_;
  base::win::ScopedComPtr<IBackgroundCopyJob> job_;

  
  base::Time download_start_time_;

  
  base::Time job_stuck_begin_time_;

  
  bool is_completed_;

  
  base::FilePath response_;

  DISALLOW_COPY_AND_ASSIGN(BackgroundDownloader);
};

}  

#endif  

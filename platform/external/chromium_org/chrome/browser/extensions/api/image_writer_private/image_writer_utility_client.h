// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_IMAGE_WRITER_UTILITY_CLIENT_H_
#define CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_IMAGE_WRITER_UTILITY_CLIENT_H_

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/sequenced_worker_pool.h"
#include "content/public/browser/utility_process_host.h"
#include "content/public/browser/utility_process_host_client.h"

class ImageWriterUtilityClient : public content::UtilityProcessHostClient {
 public:
  typedef base::Callback<void()> CancelCallback;
  typedef base::Callback<void()> SuccessCallback;
  typedef base::Callback<void(int64)> ProgressCallback;
  typedef base::Callback<void(const std::string&)> ErrorCallback;

  ImageWriterUtilityClient();

  
  
  
  
  
  
  virtual void Write(const ProgressCallback& progress_callback,
                     const SuccessCallback& success_callback,
                     const ErrorCallback& error_callback,
                     const base::FilePath& source,
                     const base::FilePath& target);

  
  
  
  
  
  
  virtual void Verify(const ProgressCallback& progress_callback,
                      const SuccessCallback& success_callback,
                      const ErrorCallback& error_callback,
                      const base::FilePath& source,
                      const base::FilePath& target);

  
  
  virtual void Cancel(const CancelCallback& cancel_callback);

  
  virtual void Shutdown();

 protected:
  
  virtual ~ImageWriterUtilityClient();

 private:
  
  void StartHost();

  
  virtual void OnProcessCrashed(int exit_code) OVERRIDE;
  virtual void OnProcessLaunchFailed() OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual bool Send(IPC::Message* msg);

  
  void OnWriteImageSucceeded();
  void OnWriteImageCancelled();
  void OnWriteImageFailed(const std::string& message);
  void OnWriteImageProgress(int64 progress);

  CancelCallback cancel_callback_;
  ProgressCallback progress_callback_;
  SuccessCallback success_callback_;
  ErrorCallback error_callback_;

  base::WeakPtr<content::UtilityProcessHost> utility_process_host_;

  scoped_refptr<base::MessageLoopProxy> message_loop_proxy_;

  DISALLOW_COPY_AND_ASSIGN(ImageWriterUtilityClient);
};

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_ASYNC_API_FUCTION_H_
#define EXTENSIONS_BROWSER_API_ASYNC_API_FUCTION_H_

#include "content/public/browser/browser_thread.h"
#include "extensions/browser/extension_function.h"

namespace extensions {

class AsyncApiFunction : public AsyncExtensionFunction {
 protected:
  AsyncApiFunction();
  virtual ~AsyncApiFunction();

  
  
  virtual bool PrePrepare();

  
  
  virtual bool Prepare() = 0;

  
  
  virtual void Work();

  
  virtual void AsyncWorkStart();

  
  void AsyncWorkCompleted();

  
  virtual bool Respond() = 0;

  
  virtual bool RunAsync() OVERRIDE;

 protected:
  content::BrowserThread::ID work_thread_id() const { return work_thread_id_; }
  void set_work_thread_id(content::BrowserThread::ID work_thread_id) {
    work_thread_id_ = work_thread_id;
  }

 private:
  void WorkOnWorkThread();
  void RespondOnUIThread();

  
  
  content::BrowserThread::ID work_thread_id_;
};

}  

#endif  

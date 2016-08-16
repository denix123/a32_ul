// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_APPLICATION_MANAGER_BACKGROUND_SHELL_APPLICATION_LOADER_H_
#define MOJO_APPLICATION_MANAGER_BACKGROUND_SHELL_APPLICATION_LOADER_H_

#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/simple_thread.h"
#include "mojo/application_manager/application_loader.h"

namespace mojo {

class MOJO_APPLICATION_MANAGER_EXPORT BackgroundShellApplicationLoader
    : public ApplicationLoader,
      public base::DelegateSimpleThread::Delegate {
 public:
  BackgroundShellApplicationLoader(scoped_ptr<ApplicationLoader> real_loader,
                                   const std::string& thread_name,
                                   base::MessageLoop::Type message_loop_type);
  virtual ~BackgroundShellApplicationLoader();

  
  virtual void Load(ApplicationManager* manager,
                    const GURL& url,
                    scoped_refptr<LoadCallbacks> callbacks) OVERRIDE;
  virtual void OnApplicationError(ApplicationManager* manager,
                                  const GURL& url) OVERRIDE;

 private:
  class BackgroundLoader;

  
  virtual void Run() OVERRIDE;

  
  
  
  
  void LoadOnBackgroundThread(ApplicationManager* manager,
                              const GURL& url,
                              ScopedMessagePipeHandle* shell_handle);
  void OnApplicationErrorOnBackgroundThread(ApplicationManager* manager,
                                            const GURL& url);
  bool quit_on_shutdown_;
  scoped_ptr<ApplicationLoader> loader_;

  const base::MessageLoop::Type message_loop_type_;
  const std::string thread_name_;

  
  
  
  
  scoped_refptr<base::TaskRunner> task_runner_;
  base::WaitableEvent message_loop_created_;

  
  base::Closure quit_closure_;

  scoped_ptr<base::DelegateSimpleThread> thread_;

  
  BackgroundLoader* background_loader_;

  DISALLOW_COPY_AND_ASSIGN(BackgroundShellApplicationLoader);
};

}  

#endif  

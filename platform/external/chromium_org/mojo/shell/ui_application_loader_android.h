// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SHELL_UI_APPLICATION_LOADER_ANDROID_H_
#define MOJO_SHELL_UI_APPLICATION_LOADER_ANDROID_H_

#include "base/memory/scoped_ptr.h"
#include "mojo/application_manager/application_loader.h"

namespace mojo {

class ApplicationManager;

namespace shell {
class Context;
}

class UIApplicationLoader : public ApplicationLoader {
 public:
  UIApplicationLoader(scoped_ptr<ApplicationLoader> real_loader,
                      shell::Context* context);
  virtual ~UIApplicationLoader();

  
  virtual void Load(ApplicationManager* manager,
                    const GURL& url,
                    scoped_refptr<LoadCallbacks> callbacks) OVERRIDE;
  virtual void OnApplicationError(ApplicationManager* manager,
                                  const GURL& url) OVERRIDE;

 private:
  class UILoader;

  
  
  
  
  void LoadOnUIThread(ApplicationManager* manager,
                      const GURL& url,
                      ScopedMessagePipeHandle* shell_handle);
  void OnApplicationErrorOnUIThread(ApplicationManager* manager,
                                    const GURL& url);
  void ShutdownOnUIThread();

  scoped_ptr<ApplicationLoader> loader_;
  shell::Context* context_;

  
  UILoader* ui_loader_;

  DISALLOW_COPY_AND_ASSIGN(UIApplicationLoader);
};

}  

#endif  

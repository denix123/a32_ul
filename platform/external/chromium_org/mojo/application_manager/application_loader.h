// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_APPLICATION_MANAGER_APPLICATION_LOADER_H_
#define MOJO_APPLICATION_MANAGER_APPLICATION_LOADER_H_

#include "base/memory/ref_counted.h"
#include "mojo/application_manager/application_manager_export.h"
#include "mojo/public/cpp/system/core.h"
#include "mojo/services/public/interfaces/network/url_loader.mojom.h"
#include "url/gurl.h"

namespace mojo {

class ApplicationManager;

class MOJO_APPLICATION_MANAGER_EXPORT ApplicationLoader {
 public:
  class MOJO_APPLICATION_MANAGER_EXPORT LoadCallbacks
      : public base::RefCounted<LoadCallbacks> {
   public:
    
    
    
    virtual ScopedMessagePipeHandle RegisterApplication() = 0;

    
    virtual void LoadWithContentHandler(const GURL& content_handler_url,
                                        URLResponsePtr url_response) = 0;

   protected:
    friend base::RefCounted<LoadCallbacks>;
    virtual ~LoadCallbacks() {}
  };

  
  
  class MOJO_APPLICATION_MANAGER_EXPORT SimpleLoadCallbacks
      : public LoadCallbacks {
   public:
    SimpleLoadCallbacks(ScopedMessagePipeHandle shell_handle);
    virtual ScopedMessagePipeHandle RegisterApplication() OVERRIDE;
    virtual void LoadWithContentHandler(const GURL& content_handler_url,
                                        URLResponsePtr response) OVERRIDE;

   private:
    ScopedMessagePipeHandle shell_handle_;
    virtual ~SimpleLoadCallbacks();
  };

  virtual ~ApplicationLoader() {}

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Load(ApplicationManager* application_manager,
                    const GURL& url,
                    scoped_refptr<LoadCallbacks> callbacks) = 0;

  
  virtual void OnApplicationError(ApplicationManager* manager,
                                  const GURL& url) = 0;

 protected:
  ApplicationLoader() {}
};

}  

#endif  

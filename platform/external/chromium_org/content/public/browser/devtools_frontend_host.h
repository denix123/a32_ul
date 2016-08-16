// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_DEVTOOLS_FRONTEND_HOST_H_
#define CONTENT_PUBLIC_BROWSER_DEVTOOLS_FRONTEND_HOST_H_

#include <string>

#include "content/common/content_export.h"

namespace content {

class RenderViewHost;

class DevToolsFrontendHost {
 public:
  
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    virtual void HandleMessageFromDevToolsFrontend(
        const std::string& message) = 0;

    
    
    
    virtual void HandleMessageFromDevToolsFrontendToBackend(
        const std::string& message) = 0;
  };

  
  
  CONTENT_EXPORT static DevToolsFrontendHost* Create(
      RenderViewHost* frontend_rvh, Delegate* delegate);

  CONTENT_EXPORT virtual ~DevToolsFrontendHost() {}
};

}  

#endif  

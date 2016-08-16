// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CONTENT_RENDERER_RENDERER_CLD_DATA_PROVIDER_H_
#define COMPONENTS_TRANSLATE_CONTENT_RENDERER_RENDERER_CLD_DATA_PROVIDER_H_

#include "base/callback.h"
#include "ipc/ipc_listener.h"

namespace IPC {
class Message;
}

namespace content {
class RenderViewObserver;
}

namespace translate {

class RendererCldDataProvider : public IPC::Listener {
 public:
  virtual ~RendererCldDataProvider() {}

  
  
  
  
  
  
  
  
  virtual bool OnMessageReceived(const IPC::Message&) = 0;

  
  
  
  
  
  virtual void SendCldDataRequest() = 0;

  
  
  
  
  virtual bool IsCldDataAvailable() = 0;

  
  
  
  
  
  virtual void SetCldAvailableCallback(base::Callback<void(void)>) = 0;
};

RendererCldDataProvider* CreateRendererCldDataProviderFor(
    content::RenderViewObserver*);

}  

#endif  

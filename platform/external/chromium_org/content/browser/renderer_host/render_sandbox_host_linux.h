// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_SANDBOX_HOST_LINUX_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_SANDBOX_HOST_LINUX_H_

#include <string>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/simple_thread.h"
#include "content/browser/renderer_host/sandbox_ipc_linux.h"
#include "content/common/content_export.h"

template <typename T> struct DefaultSingletonTraits;

namespace content {

class CONTENT_EXPORT RenderSandboxHostLinux {
 public:
  
  static RenderSandboxHostLinux* GetInstance();

  
  
  int GetRendererSocket() const {
    DCHECK(initialized_);
    return renderer_socket_;
  }
  void Init();

 private:
  friend struct DefaultSingletonTraits<RenderSandboxHostLinux>;
  
  RenderSandboxHostLinux();
  ~RenderSandboxHostLinux();

  bool ShutdownIPCChannel();

  
  bool initialized_;

  int renderer_socket_;
  int childs_lifeline_fd_;

  scoped_ptr<SandboxIPCHandler> ipc_handler_;
  scoped_ptr<base::DelegateSimpleThread> ipc_thread_;

  DISALLOW_COPY_AND_ASSIGN(RenderSandboxHostLinux);
};

}  

#endif  

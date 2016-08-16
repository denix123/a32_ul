// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_GPU_PLATFORM_SUPPORT_H_
#define UI_OZONE_PUBLIC_GPU_PLATFORM_SUPPORT_H_

#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "ui/ozone/ozone_base_export.h"

namespace ui {

class OZONE_BASE_EXPORT GpuPlatformSupport : public IPC::Listener {
 public:
  GpuPlatformSupport();
  virtual ~GpuPlatformSupport();

  
  virtual void OnChannelEstablished(IPC::Sender* sender) = 0;
};

OZONE_BASE_EXPORT GpuPlatformSupport* CreateStubGpuPlatformSupport();

}  

#endif  

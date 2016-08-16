// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_WINDOW_DELEGATE_PROXY_H_
#define UI_OZONE_PLATFORM_DRI_DRI_WINDOW_DELEGATE_PROXY_H_

#include "ui/gfx/geometry/rect.h"
#include "ui/ozone/platform/dri/channel_observer.h"
#include "ui/ozone/platform/dri/dri_window_delegate.h"

namespace ui {

class GpuPlatformSupportHostGbm;

class DriWindowDelegateProxy : public DriWindowDelegate,
                               public ChannelObserver {
 public:
  DriWindowDelegateProxy(gfx::AcceleratedWidget widget,
                         GpuPlatformSupportHostGbm* sender);
  virtual ~DriWindowDelegateProxy();

  
  virtual void Initialize() OVERRIDE;
  virtual void Shutdown() OVERRIDE;
  virtual gfx::AcceleratedWidget GetAcceleratedWidget() OVERRIDE;
  virtual HardwareDisplayController* GetController() OVERRIDE;
  virtual void OnBoundsChanged(const gfx::Rect& bounds) OVERRIDE;

  
  virtual void OnChannelEstablished() OVERRIDE;
  virtual void OnChannelDestroyed() OVERRIDE;

 private:
  gfx::AcceleratedWidget widget_;
  GpuPlatformSupportHostGbm* sender_;  

  
  
  gfx::Rect bounds_;

  DISALLOW_COPY_AND_ASSIGN(DriWindowDelegateProxy);
};

}  

#endif  

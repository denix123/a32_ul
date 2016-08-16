// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_NATIVE_NATIVE_VIEW_HOST_MAC_H_
#define UI_VIEWS_CONTROLS_NATIVE_NATIVE_VIEW_HOST_MAC_H_

#include "base/macros.h"
#include "ui/views/controls/native/native_view_host_wrapper.h"
#include "ui/views/views_export.h"

namespace views {

class NativeViewHost;

class VIEWS_EXPORT NativeViewHostMac : public NativeViewHostWrapper {
 public:
  explicit NativeViewHostMac(NativeViewHost* host);
  virtual ~NativeViewHostMac();

  
  virtual void AttachNativeView() OVERRIDE;
  virtual void NativeViewDetaching(bool destroyed) OVERRIDE;
  virtual void AddedToWidget() OVERRIDE;
  virtual void RemovedFromWidget() OVERRIDE;
  virtual void InstallClip(int x, int y, int w, int h) OVERRIDE;
  virtual bool HasInstalledClip() OVERRIDE;
  virtual void UninstallClip() OVERRIDE;
  virtual void ShowWidget(int x, int y, int w, int h) OVERRIDE;
  virtual void HideWidget() OVERRIDE;
  virtual void SetFocus() OVERRIDE;
  virtual gfx::NativeViewAccessible GetNativeViewAccessible() OVERRIDE;
  virtual gfx::NativeCursor GetCursor(int x, int y) OVERRIDE;

 private:
  
  NativeViewHost* host_;

  DISALLOW_COPY_AND_ASSIGN(NativeViewHostMac);
};

}  

#endif  

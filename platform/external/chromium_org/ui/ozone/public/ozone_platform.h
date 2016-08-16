// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_OZONE_PLATFORM_H_
#define UI_OZONE_PUBLIC_OZONE_PLATFORM_H_

#include "base/memory/scoped_ptr.h"
#include "ui/ozone/ozone_export.h"

namespace gfx {
class Rect;
}

namespace ui {

class CursorFactoryOzone;
class NativeDisplayDelegate;
class SurfaceFactoryOzone;
class GpuPlatformSupport;
class GpuPlatformSupportHost;
class PlatformWindow;
class PlatformWindowDelegate;

class OZONE_EXPORT OzonePlatform {
 public:
  OzonePlatform();
  virtual ~OzonePlatform();

  
  
  static void InitializeForUI();

  
  static void InitializeForGPU();

  static OzonePlatform* GetInstance();

  
  
  
  virtual ui::SurfaceFactoryOzone* GetSurfaceFactoryOzone() = 0;
  virtual ui::CursorFactoryOzone* GetCursorFactoryOzone() = 0;
  virtual ui::GpuPlatformSupport* GetGpuPlatformSupport() = 0;
  virtual ui::GpuPlatformSupportHost* GetGpuPlatformSupportHost() = 0;
  virtual scoped_ptr<PlatformWindow> CreatePlatformWindow(
      PlatformWindowDelegate* delegate,
      const gfx::Rect& bounds) = 0;
#if defined(OS_CHROMEOS)
  virtual scoped_ptr<ui::NativeDisplayDelegate>
      CreateNativeDisplayDelegate() = 0;
#endif

 private:
  virtual void InitializeUI() = 0;
  virtual void InitializeGPU() = 0;

  static void CreateInstance();

  static OzonePlatform* instance_;

  DISALLOW_COPY_AND_ASSIGN(OzonePlatform);
};

}  

#endif  

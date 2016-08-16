// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_ANDROID_COMPOSITOR_H_
#define CONTENT_PUBLIC_BROWSER_ANDROID_COMPOSITOR_H_

#include "base/callback.h"
#include "cc/resources/ui_resource_bitmap.h"
#include "content/common/content_export.h"
#include "content/public/browser/android/ui_resource_provider.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"

class SkBitmap;

namespace cc {
class Layer;
}

namespace gfx {
class JavaBitmap;
}

namespace content {
class CompositorClient;
class UIResourceProvider;

class CONTENT_EXPORT Compositor {
 public:
  virtual ~Compositor() {}

  
  
  static void Initialize();

  
  
  static Compositor* Create(CompositorClient* client,
                            gfx::NativeWindow root_window);

  
  virtual void SetRootLayer(scoped_refptr<cc::Layer> root) = 0;

  
  virtual void setDeviceScaleFactor(float factor) = 0;

  
  virtual void SetWindowBounds(const gfx::Size& size) = 0;

  
  
  
  virtual void SetVisible(bool visible) = 0;

  
  virtual void SetSurface(jobject surface) = 0;

  
  virtual void SetHasTransparentBackground(bool flag) = 0;

  
  
  virtual void SetNeedsComposite() = 0;

  
  virtual UIResourceProvider& GetUIResourceProvider() = 0;

 protected:
  Compositor() {}
};

}  

#endif  

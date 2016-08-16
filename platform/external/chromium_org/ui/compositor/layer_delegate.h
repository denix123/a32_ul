// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_LAYER_DELEGATE_H_
#define UI_COMPOSITOR_LAYER_DELEGATE_H_

#include "base/callback_forward.h"
#include "ui/compositor/compositor_export.h"

namespace gfx {
class Canvas;
class Rect;
}

namespace ui {

class COMPOSITOR_EXPORT LayerDelegate {
 public:
  
  
  virtual void OnPaintLayer(gfx::Canvas* canvas) = 0;

  
  
  virtual void OnDelegatedFrameDamage(const gfx::Rect& damage_rect_in_dip) = 0;

  
  virtual void OnDeviceScaleFactorChanged(float device_scale_factor) = 0;

  
  
  virtual base::Closure PrepareForLayerBoundsChange() = 0;

 protected:
  virtual ~LayerDelegate() {}
};

}  

#endif  

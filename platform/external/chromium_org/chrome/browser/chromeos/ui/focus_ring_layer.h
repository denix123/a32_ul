// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_UI_FOCUS_RING_LAYER_H_
#define CHROME_BROWSER_CHROMEOS_UI_FOCUS_RING_LAYER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/compositor/layer_delegate.h"
#include "ui/gfx/rect.h"

namespace aura {
class Window;
}

namespace ui {
class Layer;
}

namespace chromeos {

class FocusRingLayerDelegate {
 public:
  virtual void OnDeviceScaleFactorChanged() = 0;

 protected:
  virtual ~FocusRingLayerDelegate();
};

class FocusRingLayer : public ui::LayerDelegate {
 public:
  explicit FocusRingLayer(FocusRingLayerDelegate* delegate);
  virtual ~FocusRingLayer();

  
  
  void Set(aura::Window* root_window, const gfx::Rect& bounds);

  ui::Layer* layer() { return layer_.get(); }
  aura::Window* root_window() { return root_window_; }

 protected:
  
  
  
  void CreateOrUpdateLayer(aura::Window* root_window, const char* layer_name);

 private:
  
  virtual void OnPaintLayer(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnDelegatedFrameDamage(
      const gfx::Rect& damage_rect_in_dip) OVERRIDE;
  virtual void OnDeviceScaleFactorChanged(float device_scale_factor) OVERRIDE;
  virtual base::Closure PrepareForLayerBoundsChange() OVERRIDE;

  
  FocusRingLayerDelegate* delegate_;

  
  aura::Window* root_window_;

  
  scoped_ptr<ui::Layer> layer_;

  
  
  gfx::Rect focus_ring_;

  DISALLOW_COPY_AND_ASSIGN(FocusRingLayer);
};

}  

#endif  

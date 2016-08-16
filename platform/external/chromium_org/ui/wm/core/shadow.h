// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_SHADOW_H_
#define UI_WM_CORE_SHADOW_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/compositor/layer_animation_observer.h"
#include "ui/gfx/rect.h"
#include "ui/wm/wm_export.h"

namespace ui {
class Layer;
}  

namespace wm {

class WM_EXPORT Shadow : public ui::ImplicitAnimationObserver {
 public:
  enum Style {
    
    
    STYLE_ACTIVE,

    
    STYLE_INACTIVE,

    
    
    STYLE_SMALL,
  };

  Shadow();
  virtual ~Shadow();

  void Init(Style style);

  
  
  
  
  ui::Layer* layer() const { return layer_.get(); }

  const gfx::Rect& content_bounds() const { return content_bounds_; }
  Style style() const { return style_; }

  
  void SetContentBounds(const gfx::Rect& content_bounds);

  
  void SetStyle(Style style);

  
  virtual void OnImplicitAnimationsCompleted() OVERRIDE;

 private:
  
  void UpdateImagesForStyle();

  
  
  void UpdateLayerBounds();

  
  Style style_;

  
  
  scoped_ptr<ui::Layer> layer_;

  
  scoped_ptr<ui::Layer> shadow_layer_;

  
  gfx::Size image_size_;

  
  gfx::Rect content_bounds_;

  
  
  int interior_inset_;

  DISALLOW_COPY_AND_ASSIGN(Shadow);
};

}  

#endif  

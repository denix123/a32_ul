// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_LAYER_OWNER_H_
#define UI_COMPOSITOR_LAYER_OWNER_H_

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/compositor/compositor_export.h"
#include "ui/compositor/layer.h"

namespace ui {
class LayerOwnerDelegate;

class COMPOSITOR_EXPORT LayerOwner {
 public:
  LayerOwner();
  virtual ~LayerOwner();

  void SetLayer(Layer* layer);

  
  
  
  
  
  
  scoped_ptr<Layer> AcquireLayer();

  
  
  
  
  
  scoped_ptr<Layer> RecreateLayer();

  ui::Layer* layer() { return layer_; }
  const ui::Layer* layer() const { return layer_; }

  void set_layer_owner_delegate(LayerOwnerDelegate* delegate) {
    layer_owner_delegate_ = delegate;
  }

 protected:
  void DestroyLayer();

  bool OwnsLayer() const;

 private:
  
  
  
  
  
  scoped_ptr<Layer> layer_owner_;
  Layer* layer_;

  LayerOwnerDelegate* layer_owner_delegate_;

  DISALLOW_COPY_AND_ASSIGN(LayerOwner);
};

}  

#endif  

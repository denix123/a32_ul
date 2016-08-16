// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_LAYERS_LAYER_UTILS_H_
#define CC_LAYERS_LAYER_UTILS_H_

#include "cc/base/cc_export.h"

namespace gfx {
  class BoxF;
}  

namespace cc {
  class LayerImpl;

  class CC_EXPORT LayerUtils {
   public:
    
    
    
    
    
    static bool GetAnimationBounds(const LayerImpl& layer, gfx::BoxF* out);
  };

}  

#endif  

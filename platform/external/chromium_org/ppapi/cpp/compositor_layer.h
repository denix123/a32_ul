// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_COMPOSITOR_LAYER_H_
#define PPAPI_CPP_COMPOSITOR_LAYER_H_

#include "ppapi/c/ppb_compositor_layer.h"
#include "ppapi/cpp/graphics_3d.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/rect.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/size.h"

namespace pp {

class CompositorLayer : public Resource {
 public:
  
  
  CompositorLayer();

  
  
  
  CompositorLayer(const CompositorLayer& other);

  
  
  
  explicit CompositorLayer(const Resource& resource);

  
  
  
  
  CompositorLayer(PassRef, PP_Resource resource);

  
  ~CompositorLayer();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t SetColor(float red,
                   float green,
                   float blue,
                   float alpha,
                   const Size& size);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t SetTexture(const Graphics3D& context,
                     uint32_t target,
                     uint32_t texture,
                     const Size& size,
                     const CompletionCallback& cc);

  
  
  
  
  
  
  
  
  
  
  
  int32_t SetImage(const ImageData& image,
                   const CompletionCallback& callback);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t SetImage(const ImageData& image,
                   const Size& size,
                   const CompletionCallback& callback);

  
  
  
  
  
  
  
  
  int32_t SetClipRect(const Rect& rect);

  
  
  
  
  
  
  int32_t SetTransform(const float matrix[16]);

  
  
  
  
  
  
  
  
  
  
  
  int32_t SetOpacity(float opacity);

  
  
  
  
  
  
  int32_t SetBlendMode(PP_BlendMode mode);

  
  
  
  
  
  
  
  
  
  
  int32_t SetSourceRect(const FloatRect& rect);

  
  
  
  
  
  
  int32_t SetPremultipliedAlpha(bool premult);

  
  
  
  
  
  
  
  static bool IsCompositorLayer(const Resource& resource);
};

}  

#endif  

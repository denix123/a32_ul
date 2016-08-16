// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_COMPOSITOR_H_
#define PPAPI_CPP_COMPOSITOR_H_

#include "ppapi/c/ppb_compositor.h"
#include "ppapi/cpp/completion_callback.h"
#include "ppapi/cpp/compositor_layer.h"
#include "ppapi/cpp/resource.h"

namespace pp {

class Compositor : public Resource {
 public:
  
  
  Compositor();

  
  
  
  explicit Compositor(const InstanceHandle& instance);

  
  
  
  Compositor(const Compositor& other);

  
  
  
  explicit Compositor(const Resource& resource);

  
  
  
  
  Compositor(PassRef, PP_Resource resource);

  
  ~Compositor();

  
  
  
  
  
  
  
  
  
  
  
  CompositorLayer AddLayer();

  
  
  
  
  
  
  
  int32_t CommitLayers(const CompletionCallback& cc);

  
  
  
  int32_t ResetLayers();

  
  
  
  
  
  
  static bool IsCompositor(const Resource& resource);
};

}  

#endif  

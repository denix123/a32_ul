// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_ANDROID_SYSTEM_UI_RESOURCE_MANAGER_H_
#define UI_BASE_ANDROID_SYSTEM_UI_RESOURCE_MANAGER_H_

#include "cc/resources/ui_resource_client.h"
#include "ui/base/ui_base_export.h"

namespace ui {

class UI_BASE_EXPORT SystemUIResourceManager {
 public:
  enum ResourceType {
    OVERSCROLL_EDGE = 0,
    OVERSCROLL_GLOW,
    OVERSCROLL_GLOW_L,
    RESOURCE_TYPE_FIRST = OVERSCROLL_EDGE,
    RESOURCE_TYPE_LAST = OVERSCROLL_GLOW_L
  };

  virtual ~SystemUIResourceManager() {}

  
  
  
  
  
  virtual void PreloadResource(ResourceType resource) = 0;

  
  
  
  
  virtual cc::UIResourceId GetUIResourceId(ResourceType resource) = 0;
};

}  

#endif  

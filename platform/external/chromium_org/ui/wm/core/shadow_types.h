// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_SHADOW_TYPES_H_
#define UI_WM_CORE_SHADOW_TYPES_H_

#include "ui/aura/window.h"
#include "ui/wm/wm_export.h"

namespace aura {
class Window;
}

namespace wm {

enum ShadowType {
  
  SHADOW_TYPE_NONE = 0,
  SHADOW_TYPE_RECTANGULAR,
  SHADOW_TYPE_RECTANGULAR_ALWAYS_ACTIVE,
};

WM_EXPORT void SetShadowType(aura::Window* window, ShadowType shadow_type);
WM_EXPORT ShadowType GetShadowType(aura::Window* window);

extern const aura::WindowProperty<ShadowType>* const kShadowTypeKey;

}  

#endif  

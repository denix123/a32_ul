// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_ROOT_WINDOW_TRANSFORMERS_H_
#define ASH_DISPLAY_ROOT_WINDOW_TRANSFORMERS_H_

#include "ash/ash_export.h"

namespace aura {
class Window;
}

namespace gfx {
class Display;
class Transform;
}

namespace ash {
class DisplayInfo;
class RootWindowTransformer;

ASH_EXPORT RootWindowTransformer* CreateRootWindowTransformerForDisplay(
    aura::Window* root,
    const gfx::Display& display);

ASH_EXPORT RootWindowTransformer* CreateRootWindowTransformerForMirroredDisplay(
    const DisplayInfo& source_display_info,
    const DisplayInfo& mirror_display_info);

}  

#endif  

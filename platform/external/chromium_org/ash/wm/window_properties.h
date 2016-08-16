// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WINDOW_PROPERTIES_H_
#define ASH_WM_WINDOW_PROPERTIES_H_

#include "ash/ash_export.h"
#include "ui/base/ui_base_types.h"
#include "ui/gfx/rect.h"

namespace aura {
class Window;

template<typename T>
struct WindowProperty;
}

namespace ash {
namespace wm {
class WindowState;
}  



ASH_EXPORT extern const aura::WindowProperty<gfx::Rect*>* const
    kRestoreBoundsOverrideKey;

ASH_EXPORT extern const aura::WindowProperty<ui::WindowShowState>* const
    kRestoreShowStateOverrideKey;

extern const aura::WindowProperty<bool>* const kSnapChildrenToPixelBoundary;

ASH_EXPORT extern const aura::WindowProperty<bool>* const
    kStayInSameRootWindowKey;

extern const aura::WindowProperty<bool>* const kUsesScreenCoordinatesKey;

extern const aura::WindowProperty<wm::WindowState*>* const kWindowStateKey;


}  

#endif  

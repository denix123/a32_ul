// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_WINDOW_UTIL_H_
#define UI_WM_CORE_WINDOW_UTIL_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/wm/wm_export.h"

namespace aura {
class Window;
}

namespace ui {
class Layer;
class LayerOwner;
class LayerTreeOwner;
}

namespace wm {

WM_EXPORT void ActivateWindow(aura::Window* window);
WM_EXPORT void DeactivateWindow(aura::Window* window);
WM_EXPORT bool IsActiveWindow(aura::Window* window);
WM_EXPORT bool CanActivateWindow(aura::Window* window);

WM_EXPORT aura::Window* GetActivatableWindow(aura::Window* window);

WM_EXPORT aura::Window* GetToplevelWindow(aura::Window* window);

WM_EXPORT scoped_ptr<ui::LayerTreeOwner> RecreateLayers(
    ui::LayerOwner* root);

WM_EXPORT aura::Window* GetTransientParent(aura::Window* window);
WM_EXPORT const aura::Window* GetTransientParent(
    const aura::Window* window);
WM_EXPORT const std::vector<aura::Window*>& GetTransientChildren(
    const aura::Window* window);
WM_EXPORT void AddTransientChild(aura::Window* parent, aura::Window* child);
WM_EXPORT void RemoveTransientChild(aura::Window* parent, aura::Window* child);

WM_EXPORT bool HasTransientAncestor(const aura::Window* window,
                                    const aura::Window* ancestor);

}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_COCOA_FOCUS_WINDOW_SET_H_
#define UI_BASE_COCOA_FOCUS_WINDOW_SET_H_

#include <set>

#include "ui/base/ui_base_export.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {

UI_BASE_EXPORT void FocusWindowSet(const std::set<gfx::NativeWindow>& windows);

UI_BASE_EXPORT void FocusWindowSetOnCurrentSpace(
    const std::set<gfx::NativeWindow>& windows);

}  

#endif  

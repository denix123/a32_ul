// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_KEYBOARD_KEYBOARD_UTIL_H_
#define UI_KEYBOARD_KEYBOARD_UTIL_H_

#include <string>

#include "base/strings/string16.h"
#include "ui/aura/window.h"
#include "ui/keyboard/keyboard_export.h"

struct GritResourceMap;

namespace aura {
class WindowTreeHost;
}

class GURL;

namespace keyboard {

enum CursorMoveDirection {
  kCursorMoveRight = 0x01,
  kCursorMoveLeft = 0x02,
  kCursorMoveUp = 0x04,
  kCursorMoveDown = 0x08
};

enum KeyboardControlEvent {
  KEYBOARD_CONTROL_SHOW = 0,
  KEYBOARD_CONTROL_HIDE_AUTO,
  KEYBOARD_CONTROL_HIDE_USER,
  KEYBOARD_CONTROL_MAX,
};

enum KeyboardOverscrolOverride {
  KEYBOARD_OVERSCROLL_OVERRIDE_DISABLED = 0,
  KEYBOARD_OVERSCROLL_OVERRIDE_ENABLED,
  KEYBOARD_OVERSCROLL_OVERRIDE_NONE,
};

enum KeyboardShowOverride {
  KEYBOARD_SHOW_OVERRIDE_DISABLED = 0,
  KEYBOARD_SHOW_OVERRIDE_ENABLED,
  KEYBOARD_SHOW_OVERRIDE_NONE,
};

KEYBOARD_EXPORT gfx::Rect DefaultKeyboardBoundsFromWindowBounds(
    const gfx::Rect& window_bounds);

KEYBOARD_EXPORT gfx::Rect KeyboardBoundsFromWindowBounds(
    const gfx::Rect& window_bounds, int keyboard_height);

KEYBOARD_EXPORT void SetAccessibilityKeyboardEnabled(bool enabled);

KEYBOARD_EXPORT bool GetAccessibilityKeyboardEnabled();

KEYBOARD_EXPORT void SetTouchKeyboardEnabled(bool enabled);

KEYBOARD_EXPORT bool GetTouchKeyboardEnabled();

KEYBOARD_EXPORT std::string GetKeyboardLayout();

KEYBOARD_EXPORT bool IsKeyboardEnabled();

KEYBOARD_EXPORT bool IsKeyboardOverscrollEnabled();

KEYBOARD_EXPORT void SetKeyboardOverscrollOverride(
    KeyboardOverscrolOverride override);

KEYBOARD_EXPORT void SetKeyboardShowOverride(KeyboardShowOverride override);

KEYBOARD_EXPORT bool IsInputViewEnabled();

KEYBOARD_EXPORT bool IsExperimentalInputViewEnabled();

KEYBOARD_EXPORT bool InsertText(const base::string16& text,
                                aura::Window* root_window);

KEYBOARD_EXPORT bool MoveCursor(int swipe_direction,
                                int modifier_flags,
                                aura::WindowTreeHost* host);

KEYBOARD_EXPORT bool SendKeyEvent(std::string type,
                                   int key_value,
                                   int key_code,
                                   std::string key_name,
                                   int modifiers,
                                   aura::WindowTreeHost* host);

KEYBOARD_EXPORT void MarkKeyboardLoadStarted();

KEYBOARD_EXPORT void MarkKeyboardLoadFinished();

KEYBOARD_EXPORT const GritResourceMap* GetKeyboardExtensionResources(
    size_t* size);

KEYBOARD_EXPORT void SetOverrideContentUrl(const GURL& url);

KEYBOARD_EXPORT const GURL& GetOverrideContentUrl();

void LogKeyboardControlEvent(KeyboardControlEvent event);

}  

#endif  

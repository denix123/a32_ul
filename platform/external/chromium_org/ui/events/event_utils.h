// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_EVENT_UTILS_H_
#define UI_EVENTS_EVENT_UTILS_H_

#include "base/basictypes.h"
#include "base/event_types.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "ui/events/event_constants.h"
#include "ui/events/keycodes/keyboard_codes.h"
#include "ui/gfx/display.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/events/events_export.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace gfx {
class Point;
class Vector2d;
}

namespace base {
class TimeDelta;
}

namespace ui {

class Event;
class MouseEvent;

EVENTS_EXPORT void UpdateDeviceList();

EVENTS_EXPORT scoped_ptr<Event> EventFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT EventType EventTypeFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT int EventFlagsFromNative(const base::NativeEvent& native_event);

EVENTS_EXPORT base::TimeDelta EventTimeFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT base::TimeDelta EventTimeForNow();

EVENTS_EXPORT gfx::Point EventLocationFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT gfx::Point EventSystemLocationFromNative(
    const base::NativeEvent& native_event);

#if defined(USE_X11)
EVENTS_EXPORT int EventButtonFromNative(const base::NativeEvent& native_event);
#endif

EVENTS_EXPORT KeyboardCode KeyboardCodeFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT const char* CodeFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT uint32 PlatformKeycodeFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT base::char16 GetControlCharacterForKeycode(int windows_key_code,
                                                         bool shift);

EVENTS_EXPORT bool IsCharFromNative(const base::NativeEvent& native_event);

EVENTS_EXPORT int GetChangedMouseButtonFlagsFromNative(
    const base::NativeEvent& native_event);

EVENTS_EXPORT gfx::Vector2d GetMouseWheelOffset(
    const base::NativeEvent& native_event);

base::NativeEvent CopyNativeEvent(
    const base::NativeEvent& native_event);

void ReleaseCopiedNativeEvent(
    const base::NativeEvent& native_event);

EVENTS_EXPORT int GetTouchId(const base::NativeEvent& native_event);

EVENTS_EXPORT void IncrementTouchIdRefCount(
    const base::NativeEvent& native_event);

EVENTS_EXPORT void ClearTouchIdIfReleased(
    const base::NativeEvent& native_event);

EVENTS_EXPORT float GetTouchRadiusX(const base::NativeEvent& native_event);
EVENTS_EXPORT float GetTouchRadiusY(const base::NativeEvent& native_event);

EVENTS_EXPORT float GetTouchAngle(const base::NativeEvent& native_event);

EVENTS_EXPORT float GetTouchForce(const base::NativeEvent& native_event);

EVENTS_EXPORT bool GetFlingData(const base::NativeEvent& native_event,
                                float* vx,
                                float* vy,
                                float* vx_ordinal,
                                float* vy_ordinal,
                                bool* is_cancel);

EVENTS_EXPORT bool GetScrollOffsets(const base::NativeEvent& native_event,
                                    float* x_offset,
                                    float* y_offset,
                                    float* x_offset_ordinal,
                                    float* y_offset_ordinal,
                                    int* finger_count);

EVENTS_EXPORT bool ShouldDefaultToNaturalScroll();

EVENTS_EXPORT gfx::Display::TouchSupport GetInternalDisplayTouchSupport();

#if defined(OS_WIN)
EVENTS_EXPORT int GetModifiersFromACCEL(const ACCEL& accel);
EVENTS_EXPORT int GetModifiersFromKeyState();

EVENTS_EXPORT bool IsMouseEventFromTouch(UINT message);

EVENTS_EXPORT uint16 GetScanCodeFromLParam(LPARAM lParam);
EVENTS_EXPORT LPARAM GetLParamFromScanCode(uint16 scan_code);

#endif

#if defined(USE_X11)
EVENTS_EXPORT void UpdateX11EventForFlags(Event* event);
EVENTS_EXPORT void UpdateX11EventForChangedButtonFlags(MouseEvent* event);
#endif

EVENTS_EXPORT int RegisterCustomEventType();

}  

#endif  

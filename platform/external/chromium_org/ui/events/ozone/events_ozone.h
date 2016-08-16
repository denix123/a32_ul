// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_OZONE_EVENTS_OZONE_H_
#define UI_EVENTS_OZONE_EVENTS_OZONE_H_

#include "base/callback.h"
#include "base/event_types.h"
#include "ui/events/events_export.h"

namespace ui {

class Event;

EVENTS_EXPORT void DispatchEventFromNativeUiEvent(
    const base::NativeEvent& native_event,
    base::Callback<void(ui::Event*)> callback);

}  

#endif  

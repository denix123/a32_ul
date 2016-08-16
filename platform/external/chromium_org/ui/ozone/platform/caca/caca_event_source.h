// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_CACA_CACA_EVENT_SOURCE_H_
#define UI_OZONE_PLATFORM_CACA_CACA_EVENT_SOURCE_H_

#include <caca.h>

#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "ui/events/platform/platform_event_source.h"
#include "ui/events/platform/scoped_event_dispatcher.h"
#include "ui/gfx/geometry/point_f.h"

namespace ui {

class CacaWindow;

class CacaEventSource : public PlatformEventSource {
 public:
  CacaEventSource();
  virtual ~CacaEventSource();

  
  
  void TryProcessingEvent(CacaWindow* window);

  
  void OnInputEvent(caca_event_t* event, CacaWindow* window);

 private:
  
  
  gfx::PointF last_cursor_location_;

  int modifier_flags_;

  DISALLOW_COPY_AND_ASSIGN(CacaEventSource);
};

}  

#endif  

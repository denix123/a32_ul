// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WM_EVENT_H_
#define ASH_WM_WM_EVENT_H_

#include "ash/ash_export.h"
#include "ash/wm/wm_types.h"
#include "ui/gfx/rect.h"

namespace ash {
namespace wm {

enum WMEventType {
  
  
  

  
  WM_EVENT_NORMAL,
  WM_EVENT_MAXIMIZE,
  WM_EVENT_MINIMIZE,
  WM_EVENT_FULLSCREEN,
  WM_EVENT_SNAP_LEFT,
  WM_EVENT_SNAP_RIGHT,

  
  
  
  WM_EVENT_SET_BOUNDS,

  
  

  
  
  WM_EVENT_TOGGLE_MAXIMIZE_CAPTION,

  
  WM_EVENT_TOGGLE_MAXIMIZE,

  
  
  WM_EVENT_TOGGLE_VERTICAL_MAXIMIZE,

  
  
  WM_EVENT_TOGGLE_HORIZONTAL_MAXIMIZE,

  
  WM_EVENT_TOGGLE_FULLSCREEN,

  
  WM_EVENT_CENTER,

  
  
  WM_EVENT_SHOW_INACTIVE,

  
  

  
  
  WM_EVENT_ADDED_TO_WORKSPACE,

  
  WM_EVENT_DISPLAY_BOUNDS_CHANGED,

  
  
  WM_EVENT_WORKAREA_BOUNDS_CHANGED,
};

class ASH_EXPORT WMEvent {
 public:
  explicit WMEvent(WMEventType type);
  virtual ~WMEvent();

  WMEventType type() const { return type_; }

 private:
  WMEventType type_;
  DISALLOW_COPY_AND_ASSIGN(WMEvent);
};

class SetBoundsEvent : public WMEvent {
public:
  SetBoundsEvent(WMEventType type, const gfx::Rect& requested_bounds);
  virtual ~SetBoundsEvent();

  const gfx::Rect& requested_bounds() const { return requested_bounds_; }

 private:
  gfx::Rect requested_bounds_;

  DISALLOW_COPY_AND_ASSIGN(SetBoundsEvent);
};

}  
}  

#endif  


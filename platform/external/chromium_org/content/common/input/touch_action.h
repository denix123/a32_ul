// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_INPUT_TOUCH_ACTION_H_
#define CONTENT_COMMON_INPUT_TOUCH_ACTION_H_

namespace content {

enum TouchAction {
  
  TOUCH_ACTION_AUTO = 0,

  
  TOUCH_ACTION_NONE = 1 << 0,

  TOUCH_ACTION_PAN_X = 1 << 1,

  TOUCH_ACTION_PAN_Y = 1 << 2,

  TOUCH_ACTION_PAN_X_Y = TOUCH_ACTION_PAN_X | TOUCH_ACTION_PAN_Y,

  TOUCH_ACTION_PINCH_ZOOM = 1 << 3,

  TOUCH_ACTION_MANIPULATION = TOUCH_ACTION_PAN_X_Y | TOUCH_ACTION_PINCH_ZOOM,

  TOUCH_ACTION_MAX = (1 << 4) - 1
};

}  

#endif  

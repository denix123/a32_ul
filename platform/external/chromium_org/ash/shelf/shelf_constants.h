// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELF_SHELF_CONSTANTS_H_
#define ASH_SHELF_SHELF_CONSTANTS_H_

#include "ash/ash_export.h"

namespace ash {

ASH_EXPORT extern const int kShelfBackgroundAlpha;

extern const int kInvalidImageResourceID;

const int kInvalidShelfID = 0;

ASH_EXPORT extern const int kShelfSize;

ASH_EXPORT extern const int kShelfButtonSpacing;

ASH_EXPORT extern const int kShelfButtonSize;

ASH_EXPORT extern const int kTimeToSwitchBackgroundMs;

enum CycleDirection {
  CYCLE_FORWARD,
  CYCLE_BACKWARD
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SWITCHABLE_WINDOWS_H_
#define ASH_SWITCHABLE_WINDOWS_H_

#include "ash/ash_export.h"
#include "base/macros.h"

namespace aura {
  class Window;
}

namespace ash {

ASH_EXPORT extern const int kSwitchableWindowContainerIds[];

ASH_EXPORT extern const size_t kSwitchableWindowContainerIdsLength;

ASH_EXPORT bool IsSwitchableContainer(const aura::Window* window);

}  

#endif  

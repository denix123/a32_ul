// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_CHROMEOS_NETWORK_NETWORK_ICON_ANIMATION_OBSERVER_H_
#define UI_CHROMEOS_NETWORK_NETWORK_ICON_ANIMATION_OBSERVER_H_

#include "ui/chromeos/ui_chromeos_export.h"

namespace ui {
namespace network_icon {

class UI_CHROMEOS_EXPORT AnimationObserver {
 public:
  
  
  virtual void NetworkIconChanged() = 0;

 protected:
  virtual ~AnimationObserver() {}
};

}  
}  

#endif  

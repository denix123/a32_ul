// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_OBJECT_H_
#define UI_OZONE_PLATFORM_OBJECT_H_

#include "base/memory/scoped_ptr.h"

namespace ui {

template <class T>
class PlatformObject {
 public:
  static scoped_ptr<T> Create();
};

}  

#endif  

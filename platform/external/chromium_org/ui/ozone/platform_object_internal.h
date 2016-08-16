// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_OBJECT_INTERNAL_H_
#define UI_OZONE_PLATFORM_OBJECT_INTERNAL_H_

#include "ui/ozone/ozone_export.h"
#include "ui/ozone/platform_constructor_list.h"
#include "ui/ozone/platform_object.h"
#include "ui/ozone/platform_selection.h"

namespace ui {

template <class T>
scoped_ptr<T> PlatformObject<T>::Create() {
  typedef typename PlatformConstructorList<T>::Constructor Constructor;

  
  int platform = GetOzonePlatformId();

  
  Constructor constructor = PlatformConstructorList<T>::kConstructors[platform];

  
  return make_scoped_ptr(constructor());
}

}  

#endif  

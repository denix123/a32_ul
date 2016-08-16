// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_NATIVE_THEME_NATIVE_THEME_OBSERVER_H_
#define UI_NATIVE_THEME_NATIVE_THEME_OBSERVER_H_

#include "ui/native_theme/native_theme_export.h"

namespace ui {

class NativeTheme;

class NATIVE_THEME_EXPORT NativeThemeObserver {
 public:
  
  
  virtual void OnNativeThemeUpdated(ui::NativeTheme* observed_theme) = 0;

 protected:
  virtual ~NativeThemeObserver();
};

}  

#endif  

// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_WIN_WINDOW_EVENT_TARGET_H_
#define UI_BASE_WIN_WINDOW_EVENT_TARGET_H_

#include <windows.h>

#include "base/basictypes.h"
#include "ui/base/ui_base_export.h"

namespace ui {

class UI_BASE_EXPORT WindowEventTarget {
 public:
  static const char kWin32InputEventTarget[];

  
  
  
  
  
  
  
  virtual LRESULT HandleMouseMessage(unsigned int message,
                                     WPARAM w_param,
                                     LPARAM l_param,
                                     bool* handled) = 0;

  
  
  
  
  
  
  
  virtual LRESULT HandleKeyboardMessage(unsigned int message,
                                        WPARAM w_param,
                                        LPARAM l_param,
                                        bool* handled) = 0;

  
  
  
  
  
  
  virtual LRESULT HandleTouchMessage(unsigned int message,
                                     WPARAM w_param,
                                     LPARAM l_param,
                                     bool* handled) = 0;

  
  
  
  
  
  virtual LRESULT HandleScrollMessage(unsigned int message,
                                      WPARAM w_param,
                                      LPARAM l_param,
                                      bool* handled) = 0;

  
  
  
  
  
  
  virtual LRESULT HandleNcHitTestMessage(unsigned int message,
                                         WPARAM w_param,
                                         LPARAM l_param,
                                         bool* handled) = 0;
 protected:
  WindowEventTarget();
  virtual ~WindowEventTarget();
};

}  

#endif  



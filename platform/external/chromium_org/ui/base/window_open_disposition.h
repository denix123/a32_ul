// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_WINDOW_OPEN_DISPOSITION_H_
#define UI_BASE_WINDOW_OPEN_DISPOSITION_H_

#include "ui/base/ui_base_export.h"

enum WindowOpenDisposition {
  UNKNOWN,
  SUPPRESS_OPEN,
  CURRENT_TAB,
  
  SINGLETON_TAB,
  NEW_FOREGROUND_TAB,
  NEW_BACKGROUND_TAB,
  NEW_POPUP,
  NEW_WINDOW,
  SAVE_TO_DISK,
  OFF_THE_RECORD,
  IGNORE_ACTION,
  
  WINDOW_OPEN_DISPOSITION_LAST = IGNORE_ACTION
};

namespace ui {

UI_BASE_EXPORT WindowOpenDisposition DispositionFromClick(bool middle_button,
                                                          bool alt_key,
                                                          bool ctrl_key,
                                                          bool meta_key,
                                                          bool shift_key);

UI_BASE_EXPORT WindowOpenDisposition DispositionFromEventFlags(int event_flags);

}  

#endif  

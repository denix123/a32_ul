// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WINDOW_STATE_UTIL_H_
#define ASH_WM_WINDOW_STATE_UTIL_H_

namespace ash {
namespace wm {
class WindowState;
class WindowStateDelegate;

void ToggleFullScreen(WindowState* window_state, WindowStateDelegate* delegate);

}  
}  

#endif  

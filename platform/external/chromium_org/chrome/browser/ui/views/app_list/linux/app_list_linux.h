// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APP_LIST_LINUX_APP_LIST_LINUX_H_
#define CHROME_BROWSER_UI_VIEWS_APP_LIST_LINUX_APP_LIST_LINUX_H_

#include "chrome/browser/ui/app_list/app_list_positioner.h"

namespace app_list {
class AppListView;
}

namespace gfx {
class Display;
class Point;
class Size;
}  

class AppListLinux {
 public:
  
  
  
  static AppListPositioner::ScreenEdge ShelfLocationInDisplay(
      const gfx::Display& display);

  
  
  
  
  
  static gfx::Point FindAnchorPoint(const gfx::Size& view_size,
                                    const gfx::Display& display,
                                    const gfx::Point& cursor,
                                    AppListPositioner::ScreenEdge edge,
                                    bool center_window);

  static void MoveNearCursor(app_list::AppListView* view);
};

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_APP_LIST_WIN_APP_LIST_WIN_H_
#define CHROME_BROWSER_UI_VIEWS_APP_LIST_WIN_APP_LIST_WIN_H_

namespace app_list {
class AppListView;
}

namespace gfx {
class Display;
class Point;
class Rect;
class Size;
}

class AppListWin {
 public:
  
  
  
  
  
  static gfx::Point FindAnchorPoint(const gfx::Size& view_size,
                                    const gfx::Display& display,
                                    const gfx::Point& cursor,
                                    const gfx::Rect& taskbar_rect,
                                    bool center_window);

  static void MoveNearCursor(app_list::AppListView* view);
};

#endif  

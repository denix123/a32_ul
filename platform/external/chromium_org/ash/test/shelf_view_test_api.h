// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_SHELF_VIEW_TEST_API_H_
#define ASH_TEST_SHELF_VIEW_TEST_API_H_

#include "ash/shelf/shelf_item_types.h"
#include "base/basictypes.h"

namespace gfx {
class Rect;
class Size;
}

namespace ui {
class Event;
}

namespace views {
class Button;
}

namespace ash {
class OverflowBubble;
class ShelfButton;
class ShelfDelegate;
class ShelfView;

namespace test {

class ShelfViewTestAPI {
 public:
  explicit ShelfViewTestAPI(ShelfView* shelf_view);
  ~ShelfViewTestAPI();

  
  int GetButtonCount();

  
  ShelfButton* GetButton(int index);

  
  int GetFirstVisibleIndex();

  
  int GetLastVisibleIndex();

  
  const gfx::Rect& GetBoundsByIndex(int index);
  const gfx::Rect& GetIdealBoundsByIndex(int index);

  
  bool IsOverflowButtonVisible();

  
  void ShowOverflowBubble();

  
  void SetAnimationDuration(int duration_ms);

  
  void RunMessageLoopUntilAnimationsDone();

  
  ShelfView* shelf_view() { return shelf_view_; }

  
  OverflowBubble* overflow_bubble();

  
  gfx::Size GetPreferredSize();

  
  int GetButtonSize();

  
  int GetButtonSpacing();

  
  void ButtonPressed(views::Button* sender, const ui::Event& event);

  
  bool SameDragType(ShelfItemType typea, ShelfItemType typeb) const;

  
  void SetShelfDelegate(ShelfDelegate* delegate);

  
  gfx::Rect GetBoundsForDragInsertInScreen();

  
  bool IsRippedOffFromShelf();

  
  bool DraggedItemFromOverflowToShelf();

 private:
  ShelfView* shelf_view_;

  DISALLOW_COPY_AND_ASSIGN(ShelfViewTestAPI);
};

}  
}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELF_SHELF_H_
#define ASH_SHELF_SHELF_H_

#include "ash/ash_export.h"
#include "ash/shelf/shelf_constants.h"
#include "ash/shelf/shelf_types.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/size.h"
#include "ui/views/widget/widget_observer.h"

namespace app_list {
class ApplicationDragAndDropHost;
}

namespace aura {
class Window;
}

namespace gfx {
class Rect;
}

namespace views {
class View;
}

namespace ash {
class FocusCycler;
class ShelfDelegate;
class ShelfIconObserver;
class ShelfLayoutManager;
class ShelfModel;
class ShelfView;
class ShelfWidget;

namespace test {
class ShelfTestAPI;
}


class ASH_EXPORT Shelf {
 public:
  static const char kNativeViewName[];

  Shelf(ShelfModel* model, ShelfDelegate* delegate, ShelfWidget* widget);
  virtual ~Shelf();

  
  static Shelf* ForPrimaryDisplay();

  
  
  
  static Shelf* ForWindow(aura::Window* window);

  void SetAlignment(ShelfAlignment alignment);
  ShelfAlignment alignment() const { return alignment_; }

  
  
  gfx::Rect GetScreenBoundsOfItemIconForWindow(const aura::Window* window);

  
  
  void UpdateIconPositionForWindow(aura::Window* window);

  
  
  void ActivateShelfItem(int index);

  
  void CycleWindowLinear(CycleDirection direction);

  void AddIconObserver(ShelfIconObserver* observer);
  void RemoveIconObserver(ShelfIconObserver* observer);

  
  bool IsShowingMenu() const;

  bool IsShowingOverflowBubble() const;

  void SetVisible(bool visible) const;
  bool IsVisible() const;

  void SchedulePaint();

  views::View* GetAppListButtonView() const;

  
  
  void LaunchAppIndexAt(int item_index);

  ShelfWidget* shelf_widget() { return shelf_widget_; }

  
  void SetShelfViewBounds(gfx::Rect bounds);
  gfx::Rect GetShelfViewBounds() const;

  
  
  gfx::Rect GetVisibleItemsBoundsInScreen() const;

  
  app_list::ApplicationDragAndDropHost* GetDragAndDropHostForAppList();

 private:
  friend class test::ShelfTestAPI;

  
  ShelfView* shelf_view_;

  ShelfAlignment alignment_;

  ShelfDelegate* delegate_;

  ShelfWidget* shelf_widget_;

  DISALLOW_COPY_AND_ASSIGN(Shelf);
};

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_BUTTON_MENU_BUTTON_H_
#define UI_VIEWS_CONTROLS_BUTTON_MENU_BUTTON_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "ui/views/background.h"
#include "ui/views/controls/button/label_button.h"

namespace views {

class MenuButtonListener;

class VIEWS_EXPORT MenuButton : public LabelButton {
 public:
  
  
  class VIEWS_EXPORT PressedLock {
   public:
    explicit PressedLock(MenuButton* menu_button);
    ~PressedLock();

   private:
    base::WeakPtr<MenuButton> menu_button_;

    DISALLOW_COPY_AND_ASSIGN(PressedLock);
  };

  static const char kViewClassName[];

  
  static const int kMenuMarkerPaddingLeft;
  static const int kMenuMarkerPaddingRight;

  
  MenuButton(ButtonListener* listener,
             const base::string16& text,
             MenuButtonListener* menu_button_listener,
             bool show_menu_marker);
  virtual ~MenuButton();

  bool show_menu_marker() const { return show_menu_marker_; }
  void set_menu_marker(const gfx::ImageSkia* menu_marker) {
    menu_marker_ = menu_marker;
  }
  const gfx::ImageSkia* menu_marker() const { return menu_marker_; }

  const gfx::Point& menu_offset() const { return menu_offset_; }
  void set_menu_offset(int x, int y) { menu_offset_.SetPoint(x, y); }

  
  virtual bool Activate();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseEntered(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseExited(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseMoved(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;
  virtual bool OnKeyReleased(const ui::KeyEvent& event) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;

 protected:
  
  void PaintMenuMarker(gfx::Canvas* canvas);

  
  virtual gfx::Rect GetChildAreaBounds() OVERRIDE;

  
  gfx::Point menu_offset_;

 private:
  friend class PressedLock;

  
  
  void IncrementPressedLocked();
  void DecrementPressedLocked();

  
  
  int GetMaximumScreenXCoordinate();

  
  
  
  
  
  
  base::TimeTicks menu_closed_time_;

  
  MenuButtonListener* listener_;

  
  bool show_menu_marker_;

  
  const gfx::ImageSkia* menu_marker_;

  
  
  bool* destroyed_flag_;

  
  int pressed_lock_count_;

  base::WeakPtrFactory<MenuButton> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MenuButton);
};

}  

#endif  

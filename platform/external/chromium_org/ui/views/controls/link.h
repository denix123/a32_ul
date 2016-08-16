// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_LINK_H_
#define UI_VIEWS_CONTROLS_LINK_H_

#include <string>

#include "third_party/skia/include/core/SkColor.h"
#include "ui/views/controls/label.h"

namespace views {

class LinkListener;

class VIEWS_EXPORT Link : public Label {
 public:
  Link();
  explicit Link(const base::string16& title);
  virtual ~Link();

  static SkColor GetDefaultEnabledColor();

  const LinkListener* listener() { return listener_; }
  void set_listener(LinkListener* listener) { listener_ = listener; }

  
  virtual const char* GetClassName() const OVERRIDE;
  virtual gfx::NativeCursor GetCursor(const ui::MouseEvent& event) OVERRIDE;
  virtual bool CanProcessEventsWithinSubtree() const OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseCaptureLost() OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;
  virtual bool SkipDefaultKeyEventProcessing(
      const ui::KeyEvent& event) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual void OnEnabledChanged() OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;
  virtual void SetFontList(const gfx::FontList& font_list) OVERRIDE;
  virtual void SetText(const base::string16& text) OVERRIDE;
  virtual void SetEnabledColor(SkColor color) OVERRIDE;

  void SetPressedColor(SkColor color);
  void SetUnderline(bool underline);

  static const char kViewClassName[];

 private:
  void Init();

  void SetPressed(bool pressed);

  void RecalculateFont();

  LinkListener* listener_;

  
  bool underline_;

  
  bool pressed_;

  
  SkColor requested_enabled_color_;

  
  SkColor requested_pressed_color_;

  DISALLOW_COPY_AND_ASSIGN(Link);
};

}  

#endif  
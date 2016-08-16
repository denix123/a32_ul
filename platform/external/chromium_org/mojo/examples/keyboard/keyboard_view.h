// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EXAMPLES_KEYBOARD_KEYBOARD_VIEW_H_
#define MOJO_EXAMPLES_KEYBOARD_KEYBOARD_VIEW_H_

#include <vector>

#include "ui/gfx/font_list.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/view.h"

namespace views {
class LabelButton;
}

namespace mojo {
namespace examples {

class KeyboardDelegate;
struct Key;
struct Row;

class KeyboardView : public views::View, public views::ButtonListener {
 public:
  explicit KeyboardView(KeyboardDelegate* delegate);
  virtual ~KeyboardView();

  
  virtual void Layout() OVERRIDE;

 private:
  
  enum KeyboardLayout {
    KEYBOARD_LAYOUT_ALPHA,

    
    KEYBOARD_LAYOUT_SHIFT,

    
    KEYBOARD_LAYOUT_NUMERIC,
  };

  int event_flags() const {
    return (keyboard_layout_ == KEYBOARD_LAYOUT_SHIFT) ?
      ui::EF_SHIFT_DOWN : ui::EF_NONE;
  }

  void SetLayout(KeyboardLayout layout);

  
  void LayoutRow(const Row& row,
                 int row_index,
                 int initial_x,
                 int button_width,
                 int button_height);

  
  void SetRows(const std::vector<const Row*>& rows);

  
  void ConfigureButtonsInRow(int row_index, const Row& row);

  
  views::View* CreateButton();

  
  views::LabelButton* GetButton(int row, int column);

  const Key& GetKeyForButton(views::Button* button) const;

  
  
  void ResetFonts(const gfx::FontList& button_font,
                  const gfx::FontList& special_font);

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  KeyboardDelegate* delegate_;

  
  int max_keys_in_row_;

  KeyboardLayout keyboard_layout_;

  std::vector<const Row*> rows_;

  gfx::Size last_layout_size_;

  gfx::FontList button_font_;

  DISALLOW_COPY_AND_ASSIGN(KeyboardView);
};

}  
}  

#endif  

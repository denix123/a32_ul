// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_EXAMPLES_SCROLL_VIEW_EXAMPLE_H_
#define UI_VIEWS_EXAMPLES_SCROLL_VIEW_EXAMPLE_H_

#include <string>

#include "base/macros.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/scroll_view.h"
#include "ui/views/examples/example_base.h"

namespace views {

class LabelButton;

namespace examples {

class VIEWS_EXAMPLES_EXPORT ScrollViewExample : public ExampleBase,
                                                public ButtonListener {
 public:
  ScrollViewExample();
  virtual ~ScrollViewExample();

  
  virtual void CreateExampleView(View* container) OVERRIDE;

 private:
  
  virtual void ButtonPressed(Button* sender, const ui::Event& event) OVERRIDE;

  
  
  LabelButton* wide_;
  LabelButton* tall_;
  LabelButton* big_square_;
  LabelButton* small_square_;
  LabelButton* scroll_to_;

  class ScrollableView;
  
  ScrollableView* scrollable_;

  
  ScrollView* scroll_view_;

  DISALLOW_COPY_AND_ASSIGN(ScrollViewExample);
};

}  
}  

#endif  
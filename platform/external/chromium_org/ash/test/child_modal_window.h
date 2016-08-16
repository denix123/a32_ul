// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_CHILD_MODAL_WINDOW_H_
#define ASH_TEST_CHILD_MODAL_WINDOW_H_

#include "ui/views/controls/button/button.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/views/widget/widget_observer.h"

namespace views {
class LabelButton;
class NativeViewHost;
class Textfield;
class View;
class Widget;
}

namespace ash {
namespace test {

void CreateChildModalParent(gfx::NativeView context);

class ChildModalParent : public views::WidgetDelegateView,
                         public views::ButtonListener,
                         public views::WidgetObserver {
 public:
  ChildModalParent(gfx::NativeView context);
  virtual ~ChildModalParent();

  void ShowChild();
  gfx::NativeWindow GetModalParent() const;
  gfx::NativeWindow GetChild() const;

 private:
  views::Widget* CreateChild();

  
  virtual View* GetContentsView() OVERRIDE;
  virtual base::string16 GetWindowTitle() const OVERRIDE;
  virtual bool CanResize() const OVERRIDE;
  virtual void DeleteDelegate() OVERRIDE;

  
  virtual void Layout() OVERRIDE;
  virtual void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void OnWidgetDestroying(views::Widget* widget) OVERRIDE;

  
  
  views::LabelButton* button_;

  
  views::Textfield* textfield_;

  
  views::NativeViewHost* host_;

  
  
  gfx::NativeWindow modal_parent_;

  
  views::Widget* child_;

  DISALLOW_COPY_AND_ASSIGN(ChildModalParent);
};

}  
}  

#endif  

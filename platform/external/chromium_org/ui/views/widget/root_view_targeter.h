// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_ROOT_VIEW_TARGETER_H_
#define UI_VIEWS_WIDGET_ROOT_VIEW_TARGETER_H_

#include "ui/views/view_targeter.h"
#include "ui/views/views_export.h"

namespace views {

namespace internal {
class RootView;
}  

class View;
class ViewTargeterDelegate;

class VIEWS_EXPORT RootViewTargeter : public ViewTargeter {
 public:
  RootViewTargeter(ViewTargeterDelegate* delegate,
                   internal::RootView* root_view);
  virtual ~RootViewTargeter();

 private:
  
  virtual View* FindTargetForGestureEvent(
      View* root,
      const ui::GestureEvent& gesture) OVERRIDE;
  virtual ui::EventTarget* FindNextBestTargetForGestureEvent(
      ui::EventTarget* previous_target,
      const ui::GestureEvent& gesture) OVERRIDE;

  
  internal::RootView* root_view_;

  DISALLOW_COPY_AND_ASSIGN(RootViewTargeter);
};

}  

#endif  

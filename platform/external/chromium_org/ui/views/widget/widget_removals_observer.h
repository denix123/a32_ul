// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_WIDGET_REMOVALS_OBSERVER_H_
#define UI_VIEWS_WIDGET_WIDGET_REMOVALS_OBSERVER_H_

#include "ui/views/views_export.h"

namespace views {

class Widget;
class View;

class VIEWS_EXPORT WidgetRemovalsObserver {
 public:
  
  virtual void OnWillRemoveView(Widget* widget, View* view) {}

 protected:
  virtual ~WidgetRemovalsObserver() {}
};

}  

#endif  

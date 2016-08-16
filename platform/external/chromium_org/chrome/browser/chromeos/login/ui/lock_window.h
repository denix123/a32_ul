// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOCK_WINDOW_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOCK_WINDOW_H_

#include "base/basictypes.h"

namespace views {
class View;
class Widget;
}

namespace chromeos {

class LockWindow {
 public:
  
  
  class Observer {
   public:
    
    
    virtual void OnLockWindowReady() = 0;
  };

  LockWindow();

  
  
  virtual void Grab() = 0;

  
  virtual views::Widget* GetWidget() = 0;

  
  void set_observer(Observer* observer) {
    observer_ = observer;
  }

  
  void set_initially_focused_view(views::View* view) {
    initially_focused_view_ = view;
  }

  
  static LockWindow* Create();

 protected:
  
  
  Observer* observer_;

  
  views::View* initially_focused_view_;

 private:
  DISALLOW_COPY_AND_ASSIGN(LockWindow);
};

}  

#endif  

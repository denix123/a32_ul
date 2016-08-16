// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_TOUCH_VIEW_CONTROLLER_DELEGATE_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_TOUCH_VIEW_CONTROLLER_DELEGATE_H_

#include "ash/shell_observer.h"
#include "base/observer_list.h"

namespace chromeos {

class TouchViewControllerDelegate : public ash::ShellObserver {
 public:
  
  
  class Observer {
   public:
    
    virtual void OnMaximizeModeStarted() {}
    virtual void OnMaximizeModeEnded() {}

   protected:
    virtual ~Observer() {}
  };

  TouchViewControllerDelegate();
  virtual ~TouchViewControllerDelegate();

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  bool IsMaximizeModeEnabled() const;


 private:
  
  virtual void OnMaximizeModeStarted() OVERRIDE;
  virtual void OnMaximizeModeEnded() OVERRIDE;

  
  ObserverList<Observer> observers_;

  DISALLOW_COPY_AND_ASSIGN(TouchViewControllerDelegate);
};

}  

#endif  

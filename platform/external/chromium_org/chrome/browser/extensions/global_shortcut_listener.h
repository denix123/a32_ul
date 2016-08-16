// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_GLOBAL_SHORTCUT_LISTENER_H_
#define CHROME_BROWSER_EXTENSIONS_GLOBAL_SHORTCUT_LISTENER_H_

#include <map>

#include "base/basictypes.h"
#include "ui/events/keycodes/keyboard_codes.h"

namespace ui {
class Accelerator;
}

namespace extensions {

class GlobalShortcutListener {
 public:
  class Observer {
   public:
    
    virtual void OnKeyPressed(const ui::Accelerator& accelerator) = 0;
  };

  virtual ~GlobalShortcutListener();

  static GlobalShortcutListener* GetInstance();

  
  
  
  
  
  
  
  
  bool RegisterAccelerator(const ui::Accelerator& accelerator,
                           Observer* observer);

  
  
  void UnregisterAccelerator(const ui::Accelerator& accelerator,
                             Observer* observer);

  
  
  void UnregisterAccelerators(Observer* observer);

  
  
  
  void SetShortcutHandlingSuspended(bool suspended);

  
  bool IsShortcutHandlingSuspended() const;

 protected:
  GlobalShortcutListener();

  
  
  void NotifyKeyPressed(const ui::Accelerator& accelerator);

 private:
  
  
  
  
  
  
  
  
  
  
  virtual void StartListening() = 0;
  virtual void StopListening() = 0;
  virtual bool RegisterAcceleratorImpl(const ui::Accelerator& accelerator) = 0;
  virtual void UnregisterAcceleratorImpl(
      const ui::Accelerator& accelerator) = 0;

  
  
  typedef std::map<ui::Accelerator, Observer*> AcceleratorMap;
  AcceleratorMap accelerator_map_;

  
  bool shortcut_handling_suspended_;

  DISALLOW_COPY_AND_ASSIGN(GlobalShortcutListener);
};

}  

#endif  

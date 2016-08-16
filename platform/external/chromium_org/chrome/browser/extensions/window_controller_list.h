// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_WINDOW_CONTROLLER_LIST_H_
#define CHROME_BROWSER_EXTENSIONS_WINDOW_CONTROLLER_LIST_H_

#include <list>

#include "base/compiler_specific.h"
#include "base/memory/singleton.h"
#include "base/observer_list.h"
#include "chrome/browser/extensions/window_controller.h"

class Profile;
class ChromeExtensionFunctionDetails;

namespace extensions {

class WindowControllerListObserver;

class WindowControllerList {
 public:
  typedef std::list<WindowController*> ControllerList;

  WindowControllerList();
  ~WindowControllerList();

  void AddExtensionWindow(WindowController* window);
  void RemoveExtensionWindow(WindowController* window);

  void AddObserver(WindowControllerListObserver* observer);
  void RemoveObserver(WindowControllerListObserver* observer);

  
  WindowController* FindWindowById(int id) const;

  
  WindowController* FindWindowForFunctionById(
      const ChromeExtensionFunctionDetails& function_details,
      int id) const;

  
  
  WindowController* CurrentWindowForFunction(
      const ChromeExtensionFunctionDetails& function_details) const;

  const ControllerList& windows() const { return windows_; }

  static WindowControllerList* GetInstance();

 private:
  friend struct DefaultSingletonTraits<WindowControllerList>;

  
  ControllerList windows_;

  ObserverList<WindowControllerListObserver> observers_;

  DISALLOW_COPY_AND_ASSIGN(WindowControllerList);
};

}  

#endif  
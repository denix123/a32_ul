// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/ash_export.h"

#include "ash/ime/input_method_menu_item.h"
#include "base/observer_list.h"

#ifndef ASH_IME_INPUT_METHOD_MENU_MANAGER_H_
#define ASH_IME_INPUT_METHOD_MENU_MANAGER_H_

template<typename Type> struct DefaultSingletonTraits;

namespace ash {
namespace ime {

class ASH_EXPORT InputMethodMenuManager {
public:
  class Observer {
   public:
    virtual ~Observer() {}

    
    virtual void InputMethodMenuItemChanged(
        InputMethodMenuManager* manager) = 0;
  };

  ~InputMethodMenuManager();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  static InputMethodMenuManager* GetInstance();

  
  void SetCurrentInputMethodMenuItemList(
      const InputMethodMenuItemList& menu_list);

  
  InputMethodMenuItemList GetCurrentInputMethodMenuItemList() const;

  
  bool HasInputMethodMenuItemForKey(const std::string& key) const;

 private:
  InputMethodMenuManager();

  
  friend struct DefaultSingletonTraits<InputMethodMenuManager>;

  
  InputMethodMenuItemList menu_list_;

  
  ObserverList<Observer> observers_;

  DISALLOW_COPY_AND_ASSIGN(InputMethodMenuManager);
};

}  
}  

#endif 

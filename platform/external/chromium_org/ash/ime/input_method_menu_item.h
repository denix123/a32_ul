// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_IME_INPUT_METHOD_MENU_ITEM_H_
#define ASH_IME_INPUT_METHOD_MENU_ITEM_H_

#include <string>
#include <vector>
#include "ash/ash_export.h"

namespace ash {
namespace ime {

struct ASH_EXPORT InputMethodMenuItem {
  InputMethodMenuItem(const std::string& in_key,
                      const std::string& in_label,
                      bool in_is_selection_item,
                      bool in_is_selection_item_checked);

  InputMethodMenuItem();
  ~InputMethodMenuItem();

  bool operator==(const InputMethodMenuItem& other) const;
  bool operator!=(const InputMethodMenuItem& other) const;

  
  std::string ToString() const;

  std::string key;  
                    
  std::string label;  
                      
  bool is_selection_item;  
  bool is_selection_item_checked;  
                                   
};
typedef std::vector<InputMethodMenuItem> InputMethodMenuItemList;

}  
}  

#endif  

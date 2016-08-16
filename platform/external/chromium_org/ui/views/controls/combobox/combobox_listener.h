// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_COMBOBOX_COMBOBOX_LISTENER_H_
#define UI_VIEWS_CONTROLS_COMBOBOX_COMBOBOX_LISTENER_H_

#include "ui/views/views_export.h"

namespace views {

class Combobox;

class VIEWS_EXPORT ComboboxListener {
 public:
  
  
  
  
  
  
  
  virtual void OnPerformAction(Combobox* combobox) = 0;

 protected:
  virtual ~ComboboxListener() {}
};

}  

#endif  

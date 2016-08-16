// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_SINGLE_SPLIT_VIEW_LISTENER_H_
#define UI_VIEWS_CONTROLS_SINGLE_SPLIT_VIEW_LISTENER_H_

#include "ui/views/views_export.h"

namespace views {

class SingleSplitView;

class VIEWS_EXPORT SingleSplitViewListener {
 public:
  
  
  
  
  virtual bool SplitHandleMoved(SingleSplitView* sender) = 0;

 protected:
  virtual ~SingleSplitViewListener() {}
};

}  

#endif  

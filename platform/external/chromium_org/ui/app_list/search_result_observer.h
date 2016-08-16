// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_SEARCH_RESULT_OBSERVER_H_
#define UI_APP_LIST_SEARCH_RESULT_OBSERVER_H_

#include "ui/app_list/app_list_export.h"

namespace app_list {

class APP_LIST_EXPORT SearchResultObserver {
 public:
  
  virtual void OnIconChanged() {}

  
  virtual void OnActionsChanged() {}

  
  virtual void OnIsInstallingChanged() {}

  
  virtual void OnPercentDownloadedChanged() {}

  
  virtual void OnItemInstalled() {}

  
  virtual void OnItemUninstalled() {}

  
  virtual void OnResultDestroying() {}

 protected:
  virtual ~SearchResultObserver() {}
};

}  

#endif  

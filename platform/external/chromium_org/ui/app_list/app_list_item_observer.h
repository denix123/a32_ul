// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_APP_LIST_ITEM_OBSERVER_H_
#define UI_APP_LIST_APP_LIST_ITEM_OBSERVER_H_

#include "ui/app_list/app_list_export.h"

namespace app_list {

class APP_LIST_EXPORT AppListItemObserver {
 public:
  
  virtual void ItemIconChanged() {}

  
  virtual void ItemNameChanged() {}

  
  virtual void ItemHighlightedChanged() {}

  
  virtual void ItemIsInstallingChanged() {}

  
  virtual void ItemPercentDownloadedChanged() {}

  
  virtual void ItemBeingDestroyed() {}

 protected:
  virtual ~AppListItemObserver() {}
};

}  

#endif  

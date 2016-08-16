// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_FOLDER_HEADER_VIEW_DELEGATE_H_
#define UI_APP_LIST_VIEWS_FOLDER_HEADER_VIEW_DELEGATE_H_

#include <string>

namespace ui {
class Event;
}

namespace app_list {

class AppListFolderItem;

class FolderHeaderViewDelegate {
 public:
  
  
  
  
  virtual void NavigateBack(AppListFolderItem* item,
                            const ui::Event& event_flags) = 0;

  
  virtual void GiveBackFocusToSearchBox() = 0;

  
  virtual void SetItemName(AppListFolderItem* item,
                           const std::string& name) = 0;

  virtual ~FolderHeaderViewDelegate() {}
};

}  

#endif  
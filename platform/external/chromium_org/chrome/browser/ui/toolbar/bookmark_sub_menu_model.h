// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_TOOLBAR_BOOKMARK_SUB_MENU_MODEL_H_
#define CHROME_BROWSER_UI_TOOLBAR_BOOKMARK_SUB_MENU_MODEL_H_


#include "ui/base/models/simple_menu_model.h"

class Browser;

class BookmarkSubMenuModel : public ui::SimpleMenuModel {
 public:
  BookmarkSubMenuModel(ui::SimpleMenuModel::Delegate* delegate,
                       Browser* browser);
  virtual ~BookmarkSubMenuModel();

 private:
  void Build(Browser* browser);

  DISALLOW_COPY_AND_ASSIGN(BookmarkSubMenuModel);
};

#endif  
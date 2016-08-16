// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_APP_INDICATOR_ICON_MENU_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_APP_INDICATOR_ICON_MENU_H_

#include "base/callback.h"
#include "chrome/browser/ui/libgtk2ui/gtk2_signal.h"

typedef struct _GtkMenu GtkMenu;
typedef struct _GtkWidget GtkWidget;

namespace ui {
class MenuModel;
}

namespace libgtk2ui {

class AppIndicatorIconMenu {
 public:
  explicit AppIndicatorIconMenu(ui::MenuModel* model);
  virtual ~AppIndicatorIconMenu();

  
  
  
  void UpdateClickActionReplacementMenuItem(const char* label,
                                            const base::Closure& callback);

  
  void Refresh();

  GtkMenu* GetGtkMenu();

 private:
  
  CHROMEGTK_CALLBACK_0(AppIndicatorIconMenu,
                       void,
                       OnClickActionReplacementMenuItemActivated);

  
  CHROMEGTK_CALLBACK_0(AppIndicatorIconMenu, void, OnMenuItemActivated);

  
  ui::MenuModel* menu_model_;

  
  bool click_action_replacement_menu_item_added_;

  
  
  
  base::Closure click_action_replacement_callback_;

  GtkWidget* gtk_menu_;

  bool block_activation_;

  DISALLOW_COPY_AND_ASSIGN(AppIndicatorIconMenu);
};

}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_APP_INDICATOR_ICON_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_APP_INDICATOR_ICON_H_

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/libgtk2ui/gtk2_signal.h"
#include "ui/views/linux_ui/status_icon_linux.h"

typedef struct _AppIndicator AppIndicator;
typedef struct _GtkWidget GtkWidget;

namespace gfx {
class ImageSkia;
}

namespace ui {
class MenuModel;
}

namespace libgtk2ui {
class AppIndicatorIconMenu;

class AppIndicatorIcon : public views::StatusIconLinux {
 public:
  
  
  AppIndicatorIcon(std::string id,
                   const gfx::ImageSkia& image,
                   const base::string16& tool_tip);
  virtual ~AppIndicatorIcon();

  
  static bool CouldOpen();

  
  virtual void SetImage(const gfx::ImageSkia& image) OVERRIDE;
  virtual void SetToolTip(const base::string16& tool_tip) OVERRIDE;
  virtual void UpdatePlatformContextMenu(ui::MenuModel* menu) OVERRIDE;
  virtual void RefreshPlatformContextMenu() OVERRIDE;

 private:
  void SetImageFromFile(const base::FilePath& icon_file_path);
  void SetMenu();

  
  
  
  void UpdateClickActionReplacementMenuItem();

  
  void OnClickActionReplacementMenuItemActivated();

  std::string id_;
  std::string tool_tip_;

  
  bool using_kde4_;

  
  AppIndicator* icon_;

  scoped_ptr<AppIndicatorIconMenu> menu_;
  ui::MenuModel* menu_model_;

  base::FilePath icon_file_path_;
  int icon_change_count_;

  base::WeakPtrFactory<AppIndicatorIcon> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AppIndicatorIcon);
};

}  

#endif  

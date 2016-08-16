// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_MENU_MODEL_H_
#define CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_MENU_MODEL_H_

#include "chrome/browser/ui/website_settings/website_settings_ui.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "ui/base/models/simple_menu_model.h"
#include "url/gurl.h"

class PermissionMenuModel : public ui::SimpleMenuModel,
                            public ui::SimpleMenuModel::Delegate {
 public:
  typedef base::Callback<void(const WebsiteSettingsUI::PermissionInfo&)>
      ChangeCallback;

  
  PermissionMenuModel(const GURL& url,
                      const WebsiteSettingsUI::PermissionInfo& info,
                      const ChangeCallback& callback);
  
  
  
  
  PermissionMenuModel(const GURL& url,
                      ContentSetting setting,
                      const ChangeCallback& callback);
  virtual ~PermissionMenuModel();

  
  virtual bool IsCommandIdChecked(int command_id) const OVERRIDE;
  virtual bool IsCommandIdEnabled(int command_id) const OVERRIDE;
  virtual bool GetAcceleratorForCommandId(
      int command_id,
      ui::Accelerator* accelerator) OVERRIDE;
  virtual void ExecuteCommand(int command_id, int event_flags) OVERRIDE;

 private:
  
  WebsiteSettingsUI::PermissionInfo permission_;

  
  ChangeCallback callback_;

  DISALLOW_COPY_AND_ASSIGN(PermissionMenuModel);
};

#endif  

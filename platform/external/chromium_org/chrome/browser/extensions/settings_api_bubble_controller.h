// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_SETTINGS_API_BUBBLE_CONTROLLER_H_
#define CHROME_BROWSER_EXTENSIONS_SETTINGS_API_BUBBLE_CONTROLLER_H_

#include <string>
#include "chrome/browser/extensions/extension_message_bubble_controller.h"
#include "chrome/common/extensions/manifest_handlers/settings_overrides_handler.h"

namespace extensions {

class SettingsApiBubble;

class SettingsApiBubbleController : public ExtensionMessageBubbleController {
 public:
  SettingsApiBubbleController(Profile* profile, SettingsApiOverrideType type);
  virtual ~SettingsApiBubbleController();

  
  
  bool ShouldShow(const std::string& extension_id);

  
  virtual bool CloseOnDeactivate() OVERRIDE;

 private:
  
  Profile* profile_;

  
  SettingsApiOverrideType type_;

  DISALLOW_COPY_AND_ASSIGN(SettingsApiBubbleController);
};

}  

#endif  

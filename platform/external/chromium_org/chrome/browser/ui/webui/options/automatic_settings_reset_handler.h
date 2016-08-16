// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_AUTOMATIC_SETTINGS_RESET_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_AUTOMATIC_SETTINGS_RESET_HANDLER_H_

#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/webui/options/options_ui.h"

namespace options {

class AutomaticSettingsResetHandler : public OptionsPageUIHandler {
 public:
  AutomaticSettingsResetHandler();
  virtual ~AutomaticSettingsResetHandler();

  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;
  virtual void InitializePage() OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(AutomaticSettingsResetHandler);
};

}  

#endif  

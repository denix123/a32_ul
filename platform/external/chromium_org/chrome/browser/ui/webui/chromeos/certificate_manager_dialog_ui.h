// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_CERTIFICATE_MANAGER_DIALOG_UI_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_CERTIFICATE_MANAGER_DIALOG_UI_H_

#include "chrome/browser/ui/webui/options/options_ui.h"
#include "ui/web_dialogs/web_dialog_ui.h"

namespace options {
class CertificateManagerHandler;
}

namespace chromeos {

namespace options {
class CoreChromeOSOptionsHandler;
}

class CertificateManagerDialogUI : public ui::WebDialogUI,
                                   public ::options::OptionsPageUIHandlerHost {
 public:
  explicit CertificateManagerDialogUI(content::WebUI* web_ui);
  virtual ~CertificateManagerDialogUI();

 private:
  
  virtual void InitializeHandlers() OVERRIDE;

  bool initialized_handlers_;

  ::options::CertificateManagerHandler* cert_handler_;  
  options::CoreChromeOSOptionsHandler* core_handler_;  

  DISALLOW_COPY_AND_ASSIGN(CertificateManagerDialogUI);
};

}  

#endif  

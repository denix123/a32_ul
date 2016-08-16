// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CERTIFICATE_VIEWER_UI_H_
#define CHROME_BROWSER_UI_WEBUI_CERTIFICATE_VIEWER_UI_H_

#include "chrome/browser/ui/webui/constrained_web_dialog_ui.h"
#include "ui/web_dialogs/web_dialog_ui.h"

class CertificateViewerModalDialogUI : public ui::WebDialogUI {
 public:
  explicit CertificateViewerModalDialogUI(content::WebUI* web_ui);
  virtual ~CertificateViewerModalDialogUI();

 private:
  DISALLOW_COPY_AND_ASSIGN(CertificateViewerModalDialogUI);
};

class CertificateViewerUI : public ConstrainedWebDialogUI {
 public:
  explicit CertificateViewerUI(content::WebUI* web_ui);
  virtual ~CertificateViewerUI();

 private:
  DISALLOW_COPY_AND_ASSIGN(CertificateViewerUI);
};

#endif  

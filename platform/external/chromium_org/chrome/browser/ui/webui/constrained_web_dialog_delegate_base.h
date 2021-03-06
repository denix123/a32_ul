// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CONSTRAINED_WEB_DIALOG_DELEGATE_BASE_H_
#define CHROME_BROWSER_UI_WEBUI_CONSTRAINED_WEB_DIALOG_DELEGATE_BASE_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/webui/constrained_web_dialog_ui.h"
#include "ui/web_dialogs/web_dialog_ui.h"
#include "ui/web_dialogs/web_dialog_web_contents_delegate.h"

namespace content {
class BrowserContext;
}

namespace ui {
class WebDialogDelegate;
}

class ConstrainedWebDialogDelegateBase
    : public ConstrainedWebDialogDelegate,
      public ui::WebDialogWebContentsDelegate {
 public:
  ConstrainedWebDialogDelegateBase(content::BrowserContext* browser_context,
                                   ui::WebDialogDelegate* delegate,
                                   WebDialogWebContentsDelegate* tab_delegate);
  virtual ~ConstrainedWebDialogDelegateBase();

  bool closed_via_webui() const;

  
  virtual const ui::WebDialogDelegate* GetWebDialogDelegate() const OVERRIDE;
  virtual ui::WebDialogDelegate* GetWebDialogDelegate() OVERRIDE;
  virtual void OnDialogCloseFromWebUI() OVERRIDE;
  virtual void ReleaseWebContentsOnDialogClose() OVERRIDE;
  virtual web_modal::NativeWebContentsModalDialog GetNativeDialog() OVERRIDE;
  virtual content::WebContents* GetWebContents() OVERRIDE;

  
  virtual void HandleKeyboardEvent(
      content::WebContents* source,
      const content::NativeWebKeyboardEvent& event) OVERRIDE;

 private:
  scoped_ptr<ui::WebDialogDelegate> web_dialog_delegate_;

  
  scoped_ptr<content::WebContents> web_contents_;

  
  
  bool closed_via_webui_;

  
  bool release_contents_on_close_;

  scoped_ptr<WebDialogWebContentsDelegate> override_tab_delegate_;

  DISALLOW_COPY_AND_ASSIGN(ConstrainedWebDialogDelegateBase);
};

#endif  

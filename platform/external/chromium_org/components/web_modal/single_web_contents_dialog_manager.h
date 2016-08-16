// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_WEB_MODAL_SINGLE_WEB_CONTENTS_DIALOG_MANAGER_H_
#define COMPONENTS_WEB_MODAL_SINGLE_WEB_CONTENTS_DIALOG_MANAGER_H_

#include "components/web_modal/native_web_contents_modal_dialog.h"

namespace content {
class WebContents;
}  

namespace web_modal {

class WebContentsModalDialogHost;

class SingleWebContentsDialogManagerDelegate {
 public:
  SingleWebContentsDialogManagerDelegate() {}
  virtual ~SingleWebContentsDialogManagerDelegate() {}

  virtual content::WebContents* GetWebContents() const = 0;

  
  
  virtual void WillClose(NativeWebContentsModalDialog dialog) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(SingleWebContentsDialogManagerDelegate);
};

class SingleWebContentsDialogManager {
 public:
  virtual ~SingleWebContentsDialogManager() {}

  
  
  virtual void Show() = 0;

  
  virtual void Hide() = 0;

  
  
  
  virtual void Close() = 0;

  
  virtual void Focus() = 0;

  
  virtual void Pulse() = 0;

  
  virtual void HostChanged(WebContentsModalDialogHost* new_host) = 0;

  
  virtual NativeWebContentsModalDialog dialog() = 0;

 protected:
  SingleWebContentsDialogManager() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(SingleWebContentsDialogManager);
};

}  

#endif  

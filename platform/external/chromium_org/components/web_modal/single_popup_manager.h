// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_WEB_MODAL_SINGLE_POPUP_MANAGER_H_
#define COMPONENTS_WEB_MODAL_SINGLE_POPUP_MANAGER_H_

#include "components/web_modal/native_web_contents_modal_dialog.h"

namespace content {
class WebContents;
}

namespace web_modal {

class SinglePopupManagerDelegate {
 public:
  SinglePopupManagerDelegate() {}
  virtual ~SinglePopupManagerDelegate() {}

  
  
  virtual void WillClose(NativePopup popup) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(SinglePopupManagerDelegate);
};

class SinglePopupManager {
 public:
  virtual ~SinglePopupManager() {}

  
  
  virtual content::WebContents* GetBoundWebContents() = 0;

  
  virtual void Show() = 0;

  
  virtual void Hide() = 0;

  
  
  
  
  virtual void Close() = 0;

  
  virtual void Focus() = 0;

  
  virtual void Pulse() = 0;

  
  virtual NativePopup popup() = 0;

  
  
  
  
  virtual bool HasUserGesture() = 0;

  
  
  
  virtual bool MayBeOverlapped() = 0;

  
  
  
  
  
  
  
  virtual bool ShouldCloseOnNavigation() = 0;

 protected:
  SinglePopupManager() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(SinglePopupManager);
};

}  

#endif  

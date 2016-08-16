// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_WEB_MODAL_POPUP_MANAGER_H_
#define COMPONENTS_WEB_MODAL_POPUP_MANAGER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/web_modal/single_popup_manager.h"

namespace content {
class WebContents;
}

namespace gfx {
class Size;
}

namespace web_modal {

class WebContentsModalDialogHost;

class PopupManager : public SinglePopupManagerDelegate {
 public:
  
  PopupManager(WebContentsModalDialogHost* host);

  virtual ~PopupManager();

  
  virtual gfx::NativeView GetHostView() const;

  
  
  virtual void ShowPopup(scoped_ptr<SinglePopupManager> manager);

  
  
  virtual void ShowModalDialog(NativePopup popup,
                               content::WebContents* web_contents);

  
  
  
  virtual bool IsWebModalDialogActive(
      const content::WebContents* web_contents) const;

  
  virtual void WillClose(NativePopup popup) OVERRIDE;

  
  
  
  
  
  virtual void WasFocused(const content::WebContents* web_contents);

  
  
  
  
  static PopupManager* FromWebContents(content::WebContents* web_contents);

  
  void RegisterWith(content::WebContents* web_contents);
  void UnregisterWith(content::WebContents* web_contents);

  
  virtual void CloseAllDialogsForTesting(content::WebContents* web_contents);

 private:
  WebContentsModalDialogHost* host_;

  base::WeakPtrFactory<PopupManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PopupManager);
};

}  

#endif  

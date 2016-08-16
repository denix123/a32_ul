// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_GUEST_DELEGATE_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_GUEST_DELEGATE_H_

#include "extensions/browser/guest_view/guest_view_base.h"

namespace content {
class RenderViewHost;
class WebContents;
}  

namespace extensions {

class WebViewGuest;

namespace api {
namespace web_view_internal {

struct ContextMenuItem;
}  
}  

class WebViewGuestDelegate {
 public :
  virtual ~WebViewGuestDelegate() {}

  typedef std::vector<linked_ptr<api::web_view_internal::ContextMenuItem> >
      MenuItemVector;

  
  virtual double GetZoom() = 0;

  
  virtual bool HandleContextMenu(const content::ContextMenuParams& params) = 0;

  
  virtual void OnAttachWebViewHelpers(content::WebContents* contents) = 0;

  
  virtual void OnEmbedderDestroyed() = 0;

  
  
  virtual void OnDidAttachToEmbedder() = 0;

  
  virtual void OnDidCommitProvisionalLoadForFrame(bool is_main_frame) = 0;

  
  virtual void OnDidInitialize() = 0;

  virtual void OnDocumentLoadedInFrame(
      content::RenderFrameHost* render_frame_host) = 0;

  
  virtual void OnGuestDestroyed() = 0;

  
  virtual void OnSetZoom(double zoom_factor) = 0;

  
  
  
  
  virtual void OnShowContextMenu(
      int request_id,
      const MenuItemVector* items) = 0;
};

}  

#endif  

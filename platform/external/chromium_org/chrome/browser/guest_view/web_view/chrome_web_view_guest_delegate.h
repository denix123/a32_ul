// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GUEST_VIEW_WEB_VIEW_CHROME_WEB_VIEW_GUEST_DELEGATE_H_
#define CHROME_BROWSER_GUEST_VIEW_WEB_VIEW_CHROME_WEB_VIEW_GUEST_DELEGATE_H_

#include "chrome/browser/extensions/api/web_view/chrome_web_view_internal_api.h"
#include "chrome/browser/ui/zoom/zoom_observer.h"
#include "extensions/browser/guest_view/web_view/web_view_guest.h"
#include "extensions/browser/guest_view/web_view/web_view_guest_delegate.h"

#if defined(OS_CHROMEOS)
#include "chrome/browser/chromeos/accessibility/accessibility_manager.h"
#endif

class RenderViewContextMenu;

namespace ui {
class SimpleMenuModel;
}  

class ChromeWebViewGuestDelegate : public extensions::WebViewGuestDelegate,
                                   public ZoomObserver {
 public :
  explicit ChromeWebViewGuestDelegate(
      extensions::WebViewGuest* web_view_guest);
  virtual ~ChromeWebViewGuestDelegate();

  
  virtual double GetZoom() OVERRIDE;
  virtual bool HandleContextMenu(
      const content::ContextMenuParams& params) OVERRIDE;
  virtual void OnAttachWebViewHelpers(content::WebContents* contents) OVERRIDE;
  virtual void OnEmbedderDestroyed() OVERRIDE;
  virtual void OnDidAttachToEmbedder() OVERRIDE;
  virtual void OnDidCommitProvisionalLoadForFrame(bool is_main_frame) OVERRIDE;
  virtual void OnDidInitialize() OVERRIDE;
  virtual void OnDocumentLoadedInFrame(
      content::RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void OnGuestDestroyed() OVERRIDE;
  virtual void OnSetZoom(double zoom_factor) OVERRIDE;
  virtual void OnShowContextMenu(
      int request_id,
      const MenuItemVector* items) OVERRIDE;

  
  virtual void OnZoomChanged(
      const ZoomController::ZoomChangedEventData& data) OVERRIDE;

  extensions::WebViewGuest* web_view_guest() const { return web_view_guest_; }

 private:
  content::WebContents* guest_web_contents() const {
    return web_view_guest()->web_contents();
  }

  
  static scoped_ptr<base::ListValue> MenuModelToValue(
      const ui::SimpleMenuModel& menu_model);

  void InjectChromeVoxIfNeeded(content::RenderViewHost* render_view_host);

#if defined(OS_CHROMEOS)
  
  void OnAccessibilityStatusChanged(
      const chromeos::AccessibilityStatusEventDetails& details);
#endif

  
  
  int pending_context_menu_request_id_;

  
  bool chromevox_injected_;

  
  double current_zoom_factor_;

  
  
  scoped_ptr<RenderViewContextMenu> pending_menu_;

#if defined(OS_CHROMEOS)
  
  scoped_ptr<chromeos::AccessibilityStatusSubscription>
      accessibility_subscription_;
#endif

  extensions::WebViewGuest* const web_view_guest_;

  DISALLOW_COPY_AND_ASSIGN(ChromeWebViewGuestDelegate);
};

#endif  


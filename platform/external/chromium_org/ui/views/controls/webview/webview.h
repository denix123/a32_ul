// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_WEBVIEW_WEBVIEW_H_
#define UI_VIEWS_CONTROLS_WEBVIEW_WEBVIEW_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"
#include "ui/views/accessibility/native_view_accessibility.h"
#include "ui/views/controls/webview/webview_export.h"
#include "ui/views/view.h"

namespace views {

class NativeViewHost;

class WEBVIEW_EXPORT WebView : public View,
                               public content::WebContentsDelegate,
                               public content::WebContentsObserver {
 public:
  static const char kViewClassName[];

  explicit WebView(content::BrowserContext* browser_context);
  virtual ~WebView();

  
  
  content::WebContents* GetWebContents();

  
  
  void SetWebContents(content::WebContents* web_contents);

  
  
  
  
  void SetEmbedFullscreenWidgetMode(bool mode);

  content::BrowserContext* browser_context() { return browser_context_; }

  
  
  
  
  
  void LoadInitialURL(const GURL& url);

  
  
  
  
  
  
  
  void SetFastResize(bool fast_resize);

  
  
  
  
  void OnWebContentsFocused(content::WebContents* web_contents);

  
  
  void set_allow_accelerators(bool allow_accelerators) {
    allow_accelerators_ = allow_accelerators;
  }

  
  
  void SetPreferredSize(const gfx::Size& preferred_size);

  
  virtual const char* GetClassName() const OVERRIDE;
  virtual ui::TextInputClient* GetTextInputClient() OVERRIDE;

 protected:
  
  
  scoped_ptr<content::WebContents> SwapWebContents(
      scoped_ptr<content::WebContents> new_web_contents);

  
  virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;
  virtual void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) OVERRIDE;
  virtual bool SkipDefaultKeyEventProcessing(
      const ui::KeyEvent& event) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void AboutToRequestFocusFromTabTraversal(bool reverse) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual gfx::NativeViewAccessible GetNativeViewAccessible() OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;

  
  virtual void WebContentsFocused(content::WebContents* web_contents) OVERRIDE;
  virtual bool EmbedsFullscreenWidget() const OVERRIDE;

  
  virtual void RenderViewDeleted(
      content::RenderViewHost* render_view_host) OVERRIDE;
  virtual void RenderProcessGone(base::TerminationStatus status) OVERRIDE;
  virtual void RenderViewHostChanged(
      content::RenderViewHost* old_host,
      content::RenderViewHost* new_host) OVERRIDE;
  virtual void DidShowFullscreenWidget(int routing_id) OVERRIDE;
  virtual void DidDestroyFullscreenWidget(int routing_id) OVERRIDE;
  virtual void DidToggleFullscreenModeForTab(bool entered_fullscreen) OVERRIDE;
  virtual void DidAttachInterstitialPage() OVERRIDE;
  virtual void DidDetachInterstitialPage() OVERRIDE;
  
  
  virtual void OnChannelConnected(int32 peer_id) OVERRIDE {}
  virtual void OnChannelError() OVERRIDE {}
  virtual void OnBadMessageReceived(const IPC::Message& message) OVERRIDE {}

 private:
  void AttachWebContents();
  void DetachWebContents();
  void ReattachForFullscreenChange(bool enter_fullscreen);
  void NotifyMaybeTextInputClientChanged();

  
  
  content::WebContents* CreateWebContents(
      content::BrowserContext* browser_context);

  NativeViewHost* const holder_;
  
  scoped_ptr<content::WebContents> wc_owner_;
  
  bool embed_fullscreen_widget_mode_enabled_;
  
  
  
  bool is_embedding_fullscreen_widget_;
  content::BrowserContext* browser_context_;
  bool allow_accelerators_;
  gfx::Size preferred_size_;

  DISALLOW_COPY_AND_ASSIGN(WebView);
};

}  

#endif  

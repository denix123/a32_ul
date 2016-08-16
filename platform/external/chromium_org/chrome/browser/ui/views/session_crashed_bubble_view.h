// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_SESSION_CRASHED_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_SESSION_CRASHED_BUBBLE_VIEW_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_contents_observer.h"
#include "ui/views/bubble/bubble_delegate.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/styled_label_listener.h"

namespace views {
class Checkbox;
class GridLayout;
class LabelButton;
class Widget;
}

namespace content {
class WebContents;
class RenderViewHost;
}

class Browser;

class SessionCrashedBubbleView
    : public views::BubbleDelegateView,
      public views::ButtonListener,
      public views::StyledLabelListener,
      public content::WebContentsObserver,
      public content::NotificationObserver,
      public TabStripModelObserver {
 public:
  static void Show(Browser* browser);

 private:
  
  class BrowserRemovalObserver;

  SessionCrashedBubbleView(views::View* anchor_view,
                           Browser* browser,
                           content::WebContents* web_contents,
                           bool offer_uma_optin);
  virtual ~SessionCrashedBubbleView();

  
  
  
  static void ShowForReal(scoped_ptr<BrowserRemovalObserver> browser_observer,
                          bool uma_opted_in_already);

  
  virtual views::View* GetInitiallyFocusedView() OVERRIDE;
  virtual base::string16 GetWindowTitle() const OVERRIDE;
  virtual bool ShouldShowWindowTitle() const OVERRIDE;
  virtual bool ShouldShowCloseButton() const OVERRIDE;
  virtual void OnWidgetDestroying(views::Widget* widget) OVERRIDE;

  
  virtual void Init() OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void StyledLabelLinkClicked(const gfx::Range& range,
                                      int event_flags) OVERRIDE;

  
  virtual void DidStartNavigationToPendingEntry(
      const GURL& url,
      content::NavigationController::ReloadType reload_type) OVERRIDE;
  virtual void DidFinishLoad(content::RenderFrameHost* render_frame_host,
                             const GURL& validated_url) OVERRIDE;
  virtual void WasShown() OVERRIDE;
  virtual void WasHidden() OVERRIDE;

  
  virtual void Observe(
      int type,
      const content::NotificationSource& source,
      const content::NotificationDetails& details) OVERRIDE;

  
  
  
  
  virtual void TabDetachedAt(
      content::WebContents* contents,
      int index) OVERRIDE;

  
  views::View* CreateUMAOptinView();

  
  void RestorePreviousSession(views::Button* sender);

  
  void CloseBubble();

  content::NotificationRegistrar registrar_;

  
  Browser* browser_;

  
  content::WebContents* web_contents_;

  
  views::LabelButton* restore_button_;

  
  views::Checkbox* uma_option_;

  
  bool offer_uma_optin_;

  
  bool started_navigation_;

  
  
  bool restored_;

  DISALLOW_COPY_AND_ASSIGN(SessionCrashedBubbleView);
};

#endif  

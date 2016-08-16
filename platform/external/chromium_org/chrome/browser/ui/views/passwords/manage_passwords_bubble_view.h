// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_VIEW_H_

#include "chrome/browser/ui/passwords/manage_passwords_bubble.h"
#include "ui/views/bubble/bubble_delegate.h"

class ManagePasswordsIconView;

namespace content {
class WebContents;
}

class ManagePasswordsBubbleView : public ManagePasswordsBubble,
                                  public views::BubbleDelegateView {
 public:
  
  static void ShowBubble(content::WebContents* web_contents,
                         DisplayReason reason);

  
  static void CloseBubble();

  
  static void ActivateBubble();

  
  static bool IsShowing();

  
  static const ManagePasswordsBubbleView* manage_password_bubble() {
    return manage_passwords_bubble_;
  }

  content::WebContents* web_contents() const;

  const View* initially_focused_view() const {
    return initially_focused_view_;
  }

 private:
  class BlacklistedView;
  class ConfirmNeverView;
  class ManageView;
  class PendingView;
  class SaveConfirmationView;

  ManagePasswordsBubbleView(content::WebContents* web_contents,
                            ManagePasswordsIconView* anchor_view,
                            DisplayReason reason);
  virtual ~ManagePasswordsBubbleView();

  
  
  
  
  void AdjustForFullscreen(const gfx::Rect& screen_bounds);

  
  void Close();

  
  
  void Refresh();

  
  
  void NotifyNeverForThisSiteClicked();

  
  
  void NotifyConfirmedNeverForThisSite();

  
  
  void NotifyUndoNeverForThisSite();

  
  virtual void Init() OVERRIDE;
  virtual void WindowClosing() OVERRIDE;

  
  virtual views::View* GetInitiallyFocusedView() OVERRIDE;

  void set_initially_focused_view(views::View* view) {
    DCHECK(!initially_focused_view_);
    initially_focused_view_ = view;
  }

  
  
  
  
  static ManagePasswordsBubbleView* manage_passwords_bubble_;

  ManagePasswordsIconView* anchor_view_;

  
  
  bool never_save_passwords_;

  views::View* initially_focused_view_;

  
  class WebContentMouseHandler;
  scoped_ptr<WebContentMouseHandler> mouse_handler_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordsBubbleView);
};

#endif  

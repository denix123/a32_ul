// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_MESSAGE_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_MESSAGE_BUBBLE_VIEW_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/extensions/extension_message_bubble.h"
#include "chrome/browser/ui/views/toolbar/browser_actions_container_observer.h"
#include "ui/views/bubble/bubble_delegate.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/link_listener.h"

class Profile;
class BrowserActionsContainer;
class ToolbarView;

namespace views {
class Label;
class LabelButton;
class View;
}

namespace extensions {

class DevModeBubbleController;
class ExtensionMessageBubbleController;

class ExtensionMessageBubbleFactory : public BrowserActionsContainerObserver {
 public:
  ExtensionMessageBubbleFactory(Profile* profile, ToolbarView* toolbar_view);
  virtual ~ExtensionMessageBubbleFactory();

  void MaybeShow(views::View* anchor_view);

 private:
  
  
  
  
  
  enum Stage { STAGE_START, STAGE_HIGHLIGHTED, STAGE_COMPLETE };

  
  
  
  bool MaybeShowSuspiciousExtensionsBubble(views::View* anchor_view);

  
  
  
  bool MaybeShowStartupOverrideExtensionsBubble(views::View* anchor_view);

  
  
  
  bool MaybeShowProxyOverrideExtensionsBubble(views::View* anchor_view);

  
  
  
  bool MaybeShowDevModeExtensionsBubble(views::View* anchor_view);

  
  void MaybeObserve();
  void MaybeStopObserving();

  
  
  void RecordProfileCheck(Profile* profile);
  
  bool IsInitialProfileCheck(Profile* profile);

  
  virtual void OnBrowserActionsContainerAnimationEnded() OVERRIDE;
  virtual void OnBrowserActionsContainerDestroyed() OVERRIDE;

  
  
  void PrepareToHighlightExtensions(
      scoped_ptr<ExtensionMessageBubbleController> controller,
      views::View* anchor_view);

  
  void HighlightExtensions();

  
  void ShowHighlightingBubble();

  
  void Finish();

  
  Profile* profile_;

  
  ToolbarView* toolbar_view_;

  
  bool shown_suspicious_extensions_bubble_;

  
  
  bool shown_startup_override_extensions_bubble_;

  
  
  bool shown_proxy_override_extensions_bubble_;

  
  bool shown_dev_mode_extensions_bubble_;

  
  
  bool is_observing_;

  
  Stage stage_;

  
  
  BrowserActionsContainer* container_;

  
  
  views::View* anchor_view_;

  
  
  scoped_ptr<ExtensionMessageBubbleController> controller_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionMessageBubbleFactory);
};

class ExtensionMessageBubbleView : public ExtensionMessageBubble,
                                   public views::BubbleDelegateView,
                                   public views::ButtonListener,
                                   public views::LinkListener {
 public:
  ExtensionMessageBubbleView(
      views::View* anchor_view,
      views::BubbleBorder::Arrow arrow_location,
      scoped_ptr<ExtensionMessageBubbleController> controller);

  
  virtual void OnActionButtonClicked(const base::Closure& callback) OVERRIDE;
  virtual void OnDismissButtonClicked(const base::Closure& callback) OVERRIDE;
  virtual void OnLinkClicked(const base::Closure& callback) OVERRIDE;
  virtual void Show() OVERRIDE;

  
  virtual void OnWidgetDestroying(views::Widget* widget) OVERRIDE;

 private:
  virtual ~ExtensionMessageBubbleView();

  void ShowBubble();

  
  virtual void Init() OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void LinkClicked(views::Link* source, int event_flags) OVERRIDE;

  
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual void ViewHierarchyChanged(const ViewHierarchyChangedDetails& details)
      OVERRIDE;

  
  scoped_ptr<ExtensionMessageBubbleController> controller_;

  
  views::View* anchor_view_;

  
  views::Label* headline_;
  views::Link* learn_more_;
  views::LabelButton* action_button_;
  views::LabelButton* dismiss_button_;

  
  
  bool link_clicked_;
  bool action_taken_;

  
  base::Closure action_callback_;
  base::Closure dismiss_callback_;
  base::Closure link_callback_;

  base::WeakPtrFactory<ExtensionMessageBubbleView> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionMessageBubbleView);
};

}  

#endif  

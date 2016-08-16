// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_INSTALL_DIALOG_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_EXTENSIONS_EXTENSION_INSTALL_DIALOG_VIEW_H_

#include "chrome/browser/extensions/extension_install_prompt.h"
#include "ui/gfx/animation/animation_delegate.h"
#include "ui/gfx/animation/slide_animation.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/link_listener.h"
#include "ui/views/view.h"
#include "ui/views/window/dialog_delegate.h"

typedef std::vector<base::string16> PermissionDetails;
class ExpandableContainerView;

namespace content {
class PageNavigator;
}

namespace extensions {
class ExperienceSamplingEvent;
}

namespace ui {
class ResourceBundle;
}

namespace views {
class GridLayout;
class ImageButton;
class Label;
class Link;
}

class CustomScrollableView : public views::View {
 public:
  CustomScrollableView();
  virtual ~CustomScrollableView();

 private:
  virtual void Layout() OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(CustomScrollableView);
};

class ExtensionInstallDialogView : public views::DialogDelegateView,
                                   public views::LinkListener,
                                   public views::ButtonListener {
 public:
  ExtensionInstallDialogView(
      content::PageNavigator* navigator,
      ExtensionInstallPrompt::Delegate* delegate,
      scoped_refptr<ExtensionInstallPrompt::Prompt> prompt);
  virtual ~ExtensionInstallDialogView();

  
  
  const views::ScrollView* scroll_view() const { return scroll_view_; }

  
  void ContentsChanged();

 private:
  
  virtual int GetDialogButtons() const OVERRIDE;
  virtual base::string16 GetDialogButtonLabel(
      ui::DialogButton button) const OVERRIDE;
  virtual int GetDefaultDialogButton() const OVERRIDE;
  virtual bool Cancel() OVERRIDE;
  virtual bool Accept() OVERRIDE;
  virtual ui::ModalType GetModalType() const OVERRIDE;
  virtual base::string16 GetWindowTitle() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) OVERRIDE;

  
  virtual void LinkClicked(views::Link* source, int event_flags) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  void ToggleInlineExplanations();

  
  void InitView();

  
  bool AddPermissions(views::GridLayout* layout,
                      ui::ResourceBundle& rb,
                      int column_set_id,
                      int left_column_width,
                      ExtensionInstallPrompt::PermissionsType perm_type);

  
  views::GridLayout* CreateLayout(
      views::View* parent,
      int left_column_width,
      int column_set_id,
      bool single_detail_row) const;

  bool is_inline_install() const {
    return prompt_->type() == ExtensionInstallPrompt::INLINE_INSTALL_PROMPT;
  }

  bool is_bundle_install() const {
    return prompt_->type() == ExtensionInstallPrompt::BUNDLE_INSTALL_PROMPT;
  }

  bool is_external_install() const {
    return prompt_->type() == ExtensionInstallPrompt::EXTERNAL_INSTALL_PROMPT;
  }

  
  void UpdateInstallResultHistogram(bool accepted) const;

  
  
  void UpdateLinkActionHistogram(int action_type) const;

  content::PageNavigator* navigator_;
  ExtensionInstallPrompt::Delegate* delegate_;
  scoped_refptr<ExtensionInstallPrompt::Prompt> prompt_;

  
  
  views::ScrollView* scroll_view_;

  
  CustomScrollableView* scrollable_;

  
  
  
  CustomScrollableView* scrollable_header_only_;

  
  gfx::Size dialog_size_;

  
  
  views::Link* show_details_link_;

  
  views::Label* checkbox_info_label_;

  
  typedef std::vector<ExpandableContainerView*> InlineExplanations;
  InlineExplanations inline_explanations_;

  
  
  int unchecked_boxes_;

  
  scoped_ptr<extensions::ExperienceSamplingEvent> sampling_event_;

  
  
  bool handled_result_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionInstallDialogView);
};

class BulletedView : public views::View {
 public:
  explicit BulletedView(views::View* view);
 private:
  DISALLOW_COPY_AND_ASSIGN(BulletedView);
};

class CheckboxedView : public views::View {
 public:
  CheckboxedView(views::View* view, views::ButtonListener* listener);
 private:
  DISALLOW_COPY_AND_ASSIGN(CheckboxedView);
};

class ExpandableContainerView : public views::View,
                                public views::ButtonListener,
                                public views::LinkListener,
                                public gfx::AnimationDelegate {
 public:
  ExpandableContainerView(ExtensionInstallDialogView* owner,
                          const base::string16& description,
                          const PermissionDetails& details,
                          int horizontal_space,
                          bool parent_bulleted,
                          bool show_expand_link,
                          bool lighter_color_details);
  virtual ~ExpandableContainerView();

  
  virtual void ChildPreferredSizeChanged(views::View* child) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void LinkClicked(views::Link* source, int event_flags) OVERRIDE;

  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;
  virtual void AnimationEnded(const gfx::Animation* animation) OVERRIDE;

  
  void ToggleDetailLevel();

  
  
  void ExpandWithoutAnimation();

 private:
  
  class DetailsView : public views::View {
   public:
    explicit DetailsView(int horizontal_space, bool parent_bulleted,
                         bool lighter_color);
    virtual ~DetailsView() {}

    
    virtual gfx::Size GetPreferredSize() const OVERRIDE;

    void AddDetail(const base::string16& detail);

    
    void AnimateToState(double state);

   private:
    views::GridLayout* layout_;
    double state_;

    
    bool lighter_color_;

    DISALLOW_COPY_AND_ASSIGN(DetailsView);
  };

  
  ExtensionInstallDialogView* owner_;

  
  DetailsView* details_view_;

  
  
  views::Link* more_details_;

  gfx::SlideAnimation slide_animation_;

  
  
  views::ImageButton* arrow_toggle_;

  
  bool expanded_;

  DISALLOW_COPY_AND_ASSIGN(ExpandableContainerView);
};

void ShowExtensionInstallDialogImpl(
    const ExtensionInstallPrompt::ShowParams& show_params,
    ExtensionInstallPrompt::Delegate* delegate,
    scoped_refptr<ExtensionInstallPrompt::Prompt> prompt);

#endif  

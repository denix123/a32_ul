// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TOOLBAR_BROWSER_ACTIONS_CONTAINER_H_
#define CHROME_BROWSER_UI_VIEWS_TOOLBAR_BROWSER_ACTIONS_CONTAINER_H_

#include "base/observer_list.h"
#include "chrome/browser/extensions/extension_keybinding_registry.h"
#include "chrome/browser/extensions/extension_toolbar_model.h"
#include "chrome/browser/ui/views/extensions/browser_action_overflow_menu_controller.h"
#include "chrome/browser/ui/views/extensions/extension_keybinding_registry_views.h"
#include "chrome/browser/ui/views/toolbar/browser_action_view.h"
#include "ui/gfx/animation/animation_delegate.h"
#include "ui/gfx/animation/tween.h"
#include "ui/views/controls/button/menu_button_listener.h"
#include "ui/views/controls/resize_area_delegate.h"
#include "ui/views/drag_controller.h"
#include "ui/views/view.h"

class BrowserActionsContainerObserver;
class ExtensionPopup;

namespace extensions {
class ActiveTabPermissionGranter;
class Command;
class Extension;
}

namespace gfx {
class SlideAnimation;
}

namespace views {
class ResizeArea;
}

class BrowserActionsContainer
    : public views::View,
      public views::MenuButtonListener,
      public views::ResizeAreaDelegate,
      public gfx::AnimationDelegate,
      public extensions::ExtensionToolbarModel::Observer,
      public BrowserActionOverflowMenuController::Observer,
      public BrowserActionView::Delegate,
      public extensions::ExtensionKeybindingRegistry::Delegate {
 public:
  
  
  static const int kItemSpacing;

  
  
  
  BrowserActionsContainer(Browser* browser,
                          views::View* owner_view,
                          BrowserActionsContainer* main_container);
  virtual ~BrowserActionsContainer();

  void Init();

  
  size_t num_browser_actions() const { return browser_action_views_.size(); }

  
  bool animating() const { return animation_target_size_ > 0; }

  
  views::View* chevron() { return chevron_; }
  const views::View* chevron() const { return chevron_; }

  
  Profile* profile() const { return profile_; }

  
  extensions::ExtensionKeybindingRegistry* extension_keybinding_registry() {
    return extension_keybinding_registry_.get();
  }

  
  BrowserActionView* GetBrowserActionViewAt(int index) {
    return browser_action_views_[index];
  }

  
  
  BrowserActionView* GetViewForExtension(
      const extensions::Extension* extension);

  
  void RefreshBrowserActionViews();

  
  void CreateBrowserActionViews();

  
  void DeleteBrowserActionViews();

  
  
  
  size_t VisibleBrowserActions() const;

  
  
  
  size_t VisibleBrowserActionsAfterAnimation() const;

  
  void ExecuteExtensionCommand(const extensions::Extension* extension,
                               const extensions::Command& command);

  
  
  void NotifyActionMovedToOverflow();

  
  void AddObserver(BrowserActionsContainerObserver* observer);
  void RemoveObserver(BrowserActionsContainerObserver* observer);

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual int GetHeightForWidth(int width) const OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual bool GetDropFormats(int* formats,
      std::set<ui::OSExchangeData::CustomFormat>* custom_formats) OVERRIDE;
  virtual bool AreDropTypesRequired() OVERRIDE;
  virtual bool CanDrop(const ui::OSExchangeData& data) OVERRIDE;
  virtual int OnDragUpdated(const ui::DropTargetEvent& event) OVERRIDE;
  virtual void OnDragExited() OVERRIDE;
  virtual int OnPerformDrop(const ui::DropTargetEvent& event) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;

  
  virtual void OnMenuButtonClicked(views::View* source,
                                   const gfx::Point& point) OVERRIDE;

  
  virtual void WriteDragDataForView(View* sender,
                                    const gfx::Point& press_pt,
                                    ui::OSExchangeData* data) OVERRIDE;
  virtual int GetDragOperationsForView(View* sender,
                                       const gfx::Point& p) OVERRIDE;
  virtual bool CanStartDragForView(View* sender,
                                   const gfx::Point& press_pt,
                                   const gfx::Point& p) OVERRIDE;

  
  virtual void OnResize(int resize_amount, bool done_resizing) OVERRIDE;

  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;
  virtual void AnimationEnded(const gfx::Animation* animation) OVERRIDE;

  
  virtual void NotifyMenuDeleted(
      BrowserActionOverflowMenuController* controller) OVERRIDE;

  
  virtual content::WebContents* GetCurrentWebContents() OVERRIDE;
  virtual bool ShownInsideMenu() const OVERRIDE;
  virtual void OnBrowserActionViewDragDone() OVERRIDE;
  virtual views::MenuButton* GetOverflowReferenceView() OVERRIDE;
  virtual void SetPopupOwner(BrowserActionView* popup_owner) OVERRIDE;
  virtual void HideActivePopup() OVERRIDE;
  virtual BrowserActionView* GetMainViewForExtension(
      const extensions::Extension* extension) OVERRIDE;

  
  virtual extensions::ActiveTabPermissionGranter*
      GetActiveTabPermissionGranter() OVERRIDE;

  
  ExtensionPopup* TestGetPopup();

  
  
  void TestSetIconVisibilityCount(size_t icons);

  
  static int IconWidth(bool include_padding);

  
  static int IconHeight();

  
  
  
  static bool disable_animations_during_testing_;

 protected:
  
  virtual void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnThemeChanged() OVERRIDE;

 private:
  
  struct DropPosition;

  typedef std::vector<BrowserActionView*> BrowserActionViews;

  
  virtual void ToolbarExtensionAdded(const extensions::Extension* extension,
                                     int index) OVERRIDE;
  virtual void ToolbarExtensionRemoved(
      const extensions::Extension* extension) OVERRIDE;
  virtual void ToolbarExtensionMoved(const extensions::Extension* extension,
                                     int index) OVERRIDE;
  virtual void ToolbarExtensionUpdated(
      const extensions::Extension* extension) OVERRIDE;
  virtual bool ShowExtensionActionPopup(
      const extensions::Extension* extension,
      bool grant_active_tab) OVERRIDE;
  virtual void ToolbarVisibleCountChanged() OVERRIDE;
  virtual void ToolbarHighlightModeChanged(bool is_highlighting) OVERRIDE;
  virtual Browser* GetBrowser() OVERRIDE;

  void LoadImages();

  
  void OnBrowserActionVisibilityChanged();

  
  
  int GetPreferredWidth();

  
  
  void SetChevronVisibility();

  
  void CloseOverflowMenu();

  
  void StopShowFolderDropMenuTimer();

  
  void StartShowFolderDropMenuTimer();

  
  void ShowDropFolder();

  
  
  
  int IconCountToWidth(int icons, bool display_chevron) const;

  
  
  
  size_t WidthToIconCount(int pixels) const;

  
  
  
  
  int MinimumNonemptyWidth() const;

  
  
  void Animate(gfx::Tween::Type type, size_t num_visible_icons);

  
  
  
  bool ShouldDisplayBrowserAction(const extensions::Extension* extension) const;

  
  
  size_t GetIconCount() const;

  
  
  bool in_overflow_mode() const { return main_container_ != NULL; }

  
  bool initialized_;

  
  
  
  BrowserActionViews browser_action_views_;

  Profile* profile_;

  
  Browser* browser_;

  
  views::View* owner_view_;

  
  
  
  BrowserActionsContainer* main_container_;

  
  
  BrowserActionView* popup_owner_;

  
  extensions::ExtensionToolbarModel* model_;

  
  int container_width_;

  
  views::ResizeArea* resize_area_;

  
  
  views::MenuButton* chevron_;

  
  scoped_ptr<views::Painter> highlight_painter_;

  
  
  BrowserActionOverflowMenuController* overflow_menu_;

  
  scoped_ptr<gfx::SlideAnimation> resize_animation_;

  
  bool suppress_chevron_;

  
  
  
  int resize_amount_;

  
  
  int animation_target_size_;

  
  
  scoped_ptr<DropPosition> drop_position_;

  
  scoped_ptr<ExtensionKeybindingRegistryViews> extension_keybinding_registry_;

  ObserverList<BrowserActionsContainerObserver> observers_;

  
  
  static int icons_per_overflow_menu_row_;

  
  base::WeakPtrFactory<BrowserActionsContainer> show_menu_task_factory_;

  DISALLOW_COPY_AND_ASSIGN(BrowserActionsContainer);
};

#endif  

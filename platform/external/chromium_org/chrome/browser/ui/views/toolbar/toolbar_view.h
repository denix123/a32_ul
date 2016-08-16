// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_H_

#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_member.h"
#include "chrome/browser/command_observer.h"
#include "chrome/browser/ui/toolbar/back_forward_menu_model.h"
#include "chrome/browser/ui/toolbar/wrench_menu_badge_controller.h"
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/views/accessible_pane_view.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/button/menu_button_listener.h"
#include "ui/views/view.h"

class BackButton;
class BrowserActionsContainer;
class Browser;
class HomeButton;
class ReloadButton;
class ToolbarButton;
class WrenchMenu;
class WrenchMenuModel;
class WrenchToolbarButton;

namespace extensions {
class Command;
class Extension;
class ExtensionMessageBubbleFactory;
}

namespace views {
class MenuListener;
}

class ToolbarView : public views::AccessiblePaneView,
                    public views::MenuButtonListener,
                    public ui::AcceleratorProvider,
                    public LocationBarView::Delegate,
                    public content::NotificationObserver,
                    public CommandObserver,
                    public views::ButtonListener,
                    public views::WidgetObserver,
                    public views::ViewTargeterDelegate,
                    public WrenchMenuBadgeController::Delegate {
 public:
  
  static const char kViewClassName[];

  explicit ToolbarView(Browser* browser);
  virtual ~ToolbarView();

  
  void Init();

  
  
  
  
  void Update(content::WebContents* tab);

  
  
  
  void SetPaneFocusAndFocusAppMenu();

  
  bool IsAppMenuFocused();

  
  void AddMenuListener(views::MenuListener* listener);

  
  void RemoveMenuListener(views::MenuListener* listener);

  virtual bool GetAcceleratorInfo(int id, ui::Accelerator* accel);

  
  views::View* GetBookmarkBubbleAnchor();

  
  views::View* GetTranslateBubbleAnchor();

  
  void ExecuteExtensionCommand(const extensions::Extension* extension,
                               const extensions::Command& command);

  
  
  void ShowAppMenu(bool for_drop);

  
  Browser* browser() const { return browser_; }
  BrowserActionsContainer* browser_actions() const { return browser_actions_; }
  ReloadButton* reload_button() const { return reload_; }
  LocationBarView* location_bar() const { return location_bar_; }
  views::MenuButton* app_menu() const;
  HomeButton* home_button() const { return home_; }

  
  virtual bool SetPaneFocus(View* initial_focus) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;

  
  virtual void OnMenuButtonClicked(views::View* source,
                                   const gfx::Point& point) OVERRIDE;

  
  virtual content::WebContents* GetWebContents() OVERRIDE;
  virtual ToolbarModel* GetToolbarModel() OVERRIDE;
  virtual const ToolbarModel* GetToolbarModel() const OVERRIDE;
  virtual InstantController* GetInstant() OVERRIDE;
  virtual views::Widget* CreateViewsBubble(
      views::BubbleDelegateView* bubble_delegate) OVERRIDE;
  virtual PageActionImageView* CreatePageActionImageView(
      LocationBarView* owner, ExtensionAction* action) OVERRIDE;
  virtual ContentSettingBubbleModelDelegate*
      GetContentSettingBubbleModelDelegate() OVERRIDE;
  virtual void ShowWebsiteSettings(content::WebContents* web_contents,
                                   const GURL& url,
                                   const content::SSLStatus& ssl) OVERRIDE;

  
  virtual void EnabledStateChangedForCommand(int id, bool enabled) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void OnWidgetVisibilityChanged(views::Widget* widget,
                                         bool visible) OVERRIDE;
  virtual void OnWidgetActivationChanged(views::Widget* widget,
                                         bool active) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual bool GetAcceleratorForCommandId(
      int command_id, ui::Accelerator* accelerator) OVERRIDE;

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnThemeChanged() OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  virtual bool AcceleratorPressed(const ui::Accelerator& acc) OVERRIDE;

  
  bool IsWrenchMenuShowing() const;

  
  
  bool ShouldPaintBackground() const;

  enum {
    
    
    kStandardSpacing = 3,

    
    
    kVertSpacing = 5,
  };

 protected:
  
  virtual bool SetPaneFocusAndFocusDefault() OVERRIDE;
  virtual void RemovePaneFocus() OVERRIDE;

 private:
  
  enum DisplayMode {
    DISPLAYMODE_NORMAL,       
    DISPLAYMODE_LOCATION      
                              
  };

  
  virtual bool DoesIntersectRect(const views::View* target,
                                 const gfx::Rect& rect) const OVERRIDE;

  
  virtual void UpdateBadgeSeverity(WrenchMenuBadgeController::BadgeType type,
                                   WrenchIconPainter::Severity severity,
                                   bool animate) OVERRIDE;

  
  int PopupTopSpacing() const;

  
  gfx::Size SizeForContentSize(gfx::Size size) const;

  
  void LoadImages();

  bool is_display_mode_normal() const {
    return display_mode_ == DISPLAYMODE_NORMAL;
  }

  
  void ShowCriticalNotification();

  
  
  void ShowOutdatedInstallNotification(bool auto_update_enabled);

  void OnShowHomeButtonChanged();

  int content_shadow_height() const;

  
  BackButton* back_;
  ToolbarButton* forward_;
  ReloadButton* reload_;
  HomeButton* home_;
  LocationBarView* location_bar_;
  BrowserActionsContainer* browser_actions_;
  WrenchToolbarButton* app_menu_;
  Browser* browser_;

  WrenchMenuBadgeController badge_controller_;

  
  BooleanPrefMember show_home_button_;

  
  DisplayMode display_mode_;

  
  
  
  scoped_ptr<WrenchMenuModel> wrench_menu_model_;
  scoped_ptr<WrenchMenu> wrench_menu_;

  
  
  scoped_ptr<extensions::ExtensionMessageBubbleFactory>
      extension_message_bubble_factory_;

  
  ObserverList<views::MenuListener> menu_listeners_;

  content::NotificationRegistrar registrar_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(ToolbarView);
};

#endif  

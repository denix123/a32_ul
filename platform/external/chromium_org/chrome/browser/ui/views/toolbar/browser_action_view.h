// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TOOLBAR_BROWSER_ACTION_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_TOOLBAR_BROWSER_ACTION_VIEW_H_

#include "chrome/browser/ui/views/extensions/extension_action_view_controller.h"
#include "chrome/browser/ui/views/extensions/extension_action_view_delegate.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/button/menu_button_listener.h"
#include "ui/views/drag_controller.h"
#include "ui/views/view.h"

class Browser;
class ExtensionAction;

namespace extensions {
class Extension;
}

namespace gfx {
class Image;
}

class BrowserActionView : public views::MenuButton,
                          public ExtensionActionViewDelegate,
                          public views::ButtonListener,
                          public content::NotificationObserver {
 public:
  
  
  class Delegate : public views::DragController {
   public:
    
    virtual content::WebContents* GetCurrentWebContents() = 0;

    
    virtual bool ShownInsideMenu() const = 0;

    
    
    
    
    virtual void OnBrowserActionViewDragDone() = 0;

    
    
    virtual views::MenuButton* GetOverflowReferenceView() = 0;

    
    virtual void SetPopupOwner(BrowserActionView* popup_owner) = 0;

    
    virtual void HideActivePopup() = 0;

    
    
    virtual BrowserActionView* GetMainViewForExtension(
        const extensions::Extension* extension) = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  class IconObserver {
   public:
    virtual void OnIconUpdated(const gfx::ImageSkia& icon) = 0;

   protected:
    virtual ~IconObserver() {}
  };

  BrowserActionView(const extensions::Extension* extension,
                    ExtensionAction* extension_action,
                    Browser* browser,
                    BrowserActionView::Delegate* delegate);
  virtual ~BrowserActionView();

  const extensions::Extension* extension() const {
    return view_controller_->extension();
  }
  ExtensionAction* extension_action() {
    return view_controller_->extension_action();
  }
  ExtensionActionViewController* view_controller() {
    return view_controller_.get();
  }
  void set_icon_observer(IconObserver* icon_observer) {
    icon_observer_ = icon_observer;
  }

  
  void UpdateState();

  
  bool IsPopup();

  
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  
  
  
  virtual bool Activate() OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseExited(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnKeyReleased(const ui::KeyEvent& event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;
  virtual scoped_ptr<views::LabelButtonBorder> CreateDefaultBorder() const
      OVERRIDE;

  
  
  
  bool IsEnabled(int tab_id) const;

  
  gfx::ImageSkia GetIconWithBadge();

  
  gfx::ImageSkia GetIconForTest();

 private:
  
  virtual void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) OVERRIDE;
  virtual void OnDragDone() OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void PaintChildren(gfx::Canvas* canvas,
                             const views::CullSet& cull_set) OVERRIDE;

  
  virtual views::View* GetAsView() OVERRIDE;
  virtual bool IsShownInMenu() OVERRIDE;
  virtual views::FocusManager* GetFocusManagerForAccelerator() OVERRIDE;
  virtual views::Widget* GetParentForContextMenu() OVERRIDE;
  virtual ExtensionActionViewController* GetPreferredPopupViewController()
      OVERRIDE;
  virtual views::View* GetReferenceViewForPopup() OVERRIDE;
  virtual views::MenuButton* GetContextMenuButton() OVERRIDE;
  virtual content::WebContents* GetCurrentWebContents() OVERRIDE;
  virtual void HideActivePopup() OVERRIDE;
  virtual void OnIconUpdated() OVERRIDE;
  virtual void OnPopupShown(bool grant_tab_permissions) OVERRIDE;
  virtual void CleanupPopup() OVERRIDE;

  
  scoped_ptr<ExtensionActionViewController> view_controller_;

  
  BrowserActionView::Delegate* delegate_;

  
  bool called_registered_extension_command_;

  content::NotificationRegistrar registrar_;

  
  
  IconObserver* icon_observer_;

  
  scoped_ptr<views::MenuButton::PressedLock> pressed_lock_;

  DISALLOW_COPY_AND_ASSIGN(BrowserActionView);
};

#endif  

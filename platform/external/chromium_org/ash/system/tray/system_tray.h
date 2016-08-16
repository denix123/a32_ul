// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_TRAY_SYSTEM_TRAY_H_
#define ASH_SYSTEM_TRAY_SYSTEM_TRAY_H_

#include "ash/ash_export.h"
#include "ash/system/tray/system_tray_bubble.h"
#include "ash/system/tray/tray_background_view.h"
#include "ash/system/user/login_status.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "ui/views/bubble/tray_bubble_view.h"
#include "ui/views/view.h"

#include <map>
#include <vector>

namespace ash {
class ScreenTrayItem;
class SystemBubbleWrapper;
class SystemTrayDelegate;
class SystemTrayItem;
class TrayAccessibility;
class TrayDate;
class TrayUser;

enum BubbleCreationType {
  BUBBLE_CREATE_NEW,    
  BUBBLE_USE_EXISTING,  
};

class ASH_EXPORT SystemTray : public TrayBackgroundView,
                              public views::TrayBubbleView::Delegate {
 public:
  explicit SystemTray(StatusAreaWidget* status_area_widget);
  virtual ~SystemTray();

  
  
  void InitializeTrayItems(SystemTrayDelegate* delegate);

  
  void AddTrayItem(SystemTrayItem* item);

  
  void RemoveTrayItem(SystemTrayItem* item);

  
  const std::vector<SystemTrayItem*>& GetTrayItems() const;

  
  void ShowDefaultView(BubbleCreationType creation_type);

  
  void ShowPersistentDefaultView();

  
  
  void ShowDetailedView(SystemTrayItem* item,
                        int close_delay_in_seconds,
                        bool activate,
                        BubbleCreationType creation_type);

  
  
  void SetDetailedViewCloseDelay(int close_delay);

  
  void HideDetailedView(SystemTrayItem* item);

  
  void ShowNotificationView(SystemTrayItem* item);

  
  void HideNotificationView(SystemTrayItem* item);

  
  void UpdateAfterLoginStatusChange(user::LoginStatus login_status);

  
  void UpdateAfterShelfAlignmentChange(ShelfAlignment alignment);

  
  void SetHideNotifications(bool hidden);

  
  bool ShouldShowShelf() const;

  
  
  bool HasSystemBubble() const;

  
  bool HasNotificationBubble() const;

  
  bool HasSystemBubbleType(SystemTrayBubble::BubbleType type);

  
  SystemTrayBubble* GetSystemBubble();

  
  bool IsAnyBubbleVisible() const;

  
  bool IsMouseInNotificationBubble() const;

  
  bool CloseSystemBubble() const;

  
  
  views::View* GetHelpButtonView() const;

  

  
  bool CloseNotificationBubbleForTest() const;

  
  virtual void SetShelfAlignment(ShelfAlignment alignment) OVERRIDE;
  virtual void AnchorUpdated() OVERRIDE;
  virtual base::string16 GetAccessibleNameForTray() OVERRIDE;
  virtual void BubbleResized(const views::TrayBubbleView* bubble_view) OVERRIDE;
  virtual void HideBubbleWithView(
      const views::TrayBubbleView* bubble_view) OVERRIDE;
  virtual bool ClickedOutsideBubble() OVERRIDE;

  
  virtual void BubbleViewDestroyed() OVERRIDE;
  virtual void OnMouseEnteredView() OVERRIDE;
  virtual void OnMouseExitedView() OVERRIDE;
  virtual base::string16 GetAccessibleNameForBubble() OVERRIDE;
  virtual gfx::Rect GetAnchorRect(
      views::Widget* anchor_widget,
      AnchorType anchor_type,
      AnchorAlignment anchor_alignment) const OVERRIDE;
  virtual void HideBubble(const views::TrayBubbleView* bubble_view) OVERRIDE;

  ScreenTrayItem* GetScreenShareItem() { return screen_share_tray_item_; }
  ScreenTrayItem* GetScreenCaptureItem() { return screen_capture_tray_item_; }

  TrayAccessibility* GetTrayAccessibilityForTest() {
    return tray_accessibility_;
  }

  
  views::View* GetTrayItemViewForTest(SystemTrayItem* tray_item);

  
  TrayDate* GetTrayDateForTesting() const;

 private:
  
  void CreateItems(SystemTrayDelegate* delegate);

  
  void DestroySystemBubble();

  
  void DestroyNotificationBubble();

  
  
  base::string16 GetAccessibleTimeString(const base::Time& now) const;

  
  
  int GetTrayXOffset(SystemTrayItem* item) const;

  
  void ShowDefaultViewWithOffset(BubbleCreationType creation_type,
                                 int x_offset,
                                 bool persistent);

  
  
  
  void ShowItems(const std::vector<SystemTrayItem*>& items,
                 bool details,
                 bool activate,
                 BubbleCreationType creation_type,
                 int x_offset,
                 bool persistent);

  
  
  void UpdateNotificationBubble();

  
  
  void UpdateWebNotifications();

  
  void CloseSystemBubbleAndDeactivateSystemTray();

  const ScopedVector<SystemTrayItem>& items() const { return items_; }

  
  virtual bool PerformAction(const ui::Event& event) OVERRIDE;

  
  ScopedVector<SystemTrayItem> items_;

  
  SystemTrayItem* detailed_item_;
  std::vector<SystemTrayItem*> notification_items_;

  
  std::map<SystemTrayItem*, views::View*> tray_item_map_;

  
  scoped_ptr<SystemBubbleWrapper> system_bubble_;

  
  scoped_ptr<SystemBubbleWrapper> notification_bubble_;

  
  
  int default_bubble_height_;

  
  
  bool hide_notifications_;

  
  
  
  bool full_system_tray_menu_;

  TrayAccessibility* tray_accessibility_;  
  TrayDate* tray_date_;

  
  ScreenTrayItem* screen_capture_tray_item_;  
  ScreenTrayItem* screen_share_tray_item_;  

  DISALLOW_COPY_AND_ASSIGN(SystemTray);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_OVERVIEW_OVERVIEW_BUTTON_TRAY_H_
#define ASH_SYSTEM_OVERVIEW_OVERVIEW_BUTTON_TRAY_H_

#include "ash/ash_export.h"
#include "ash/shell_observer.h"
#include "ash/system/tray/tray_background_view.h"

namespace views {
class ImageView;
}

namespace ash {

class ASH_EXPORT OverviewButtonTray : public TrayBackgroundView,
                                      public ShellObserver {
 public:
  explicit OverviewButtonTray(StatusAreaWidget* status_area_widget);
  virtual ~OverviewButtonTray();

  
  
  virtual void UpdateAfterLoginStatusChange(user::LoginStatus status);

  
  virtual bool PerformAction(const ui::Event& event) OVERRIDE;

  
  virtual void OnMaximizeModeStarted() OVERRIDE;
  virtual void OnMaximizeModeEnded() OVERRIDE;

  
  virtual bool ClickedOutsideBubble() OVERRIDE;
  virtual base::string16 GetAccessibleNameForTray() OVERRIDE;
  virtual void HideBubbleWithView(
      const views::TrayBubbleView* bubble_view) OVERRIDE;
  virtual void SetShelfAlignment(ShelfAlignment alignment) OVERRIDE;

 private:
  friend class OverviewButtonTrayTest;

  
  
  void SetIconBorderForShelfAlignment();

  
  
  void UpdateIconVisibility();

  
  views::ImageView* icon_;

  DISALLOW_COPY_AND_ASSIGN(OverviewButtonTray);
};

}  

#endif  

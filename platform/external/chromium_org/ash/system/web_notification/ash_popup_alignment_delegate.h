// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_WEB_NOTIFICATION_ASH_POPUP_ALIGNMENT_DELEGATE_H_
#define ASH_SYSTEM_WEB_NOTIFICATION_ASH_POPUP_ALIGNMENT_DELEGATE_H_

#include "ash/ash_export.h"
#include "ash/shelf/shelf_layout_manager_observer.h"
#include "ash/shelf/shelf_types.h"
#include "ash/shell_observer.h"
#include "base/macros.h"
#include "ui/gfx/display_observer.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/message_center/views/popup_alignment_delegate.h"

namespace aura {
class Window;
}

namespace gfx {
class Screen;
}

namespace ash {

class AshPopupAlignmentDelegateTest;
class ShelfLayoutManager;
class WebNotificationTrayTest;

class ASH_EXPORT AshPopupAlignmentDelegate
    : public message_center::PopupAlignmentDelegate,
      public ShelfLayoutManagerObserver,
      public ShellObserver,
      public gfx::DisplayObserver {
 public:
  AshPopupAlignmentDelegate();
  virtual ~AshPopupAlignmentDelegate();

  
  void StartObserving(gfx::Screen* screen, const gfx::Display& display);

  
  
  void SetSystemTrayHeight(int height);

  
  virtual int GetToastOriginX(const gfx::Rect& toast_bounds) const OVERRIDE;
  virtual int GetBaseLine() const OVERRIDE;
  virtual int GetWorkAreaBottom() const OVERRIDE;
  virtual bool IsTopDown() const OVERRIDE;
  virtual bool IsFromLeft() const OVERRIDE;
  virtual void RecomputeAlignment(const gfx::Display& display) OVERRIDE;

 private:
  friend class AshPopupAlignmentDelegateTest;
  friend class WebNotificationTrayTest;

  
  ShelfAlignment GetAlignment() const;

  
  
  
  void UpdateShelf();

  
  virtual void OnDisplayWorkAreaInsetsChanged() OVERRIDE;

  
  virtual void OnAutoHideStateChanged(ShelfAutoHideState new_state) OVERRIDE;

  
  virtual void OnDisplayAdded(const gfx::Display& new_display) OVERRIDE;
  virtual void OnDisplayRemoved(const gfx::Display& old_display) OVERRIDE;
  virtual void OnDisplayMetricsChanged(const gfx::Display& display,
                                       uint32_t metrics) OVERRIDE;

  int64_t display_id_;
  gfx::Screen* screen_;
  gfx::Rect work_area_;
  aura::Window* root_window_;
  ShelfLayoutManager* shelf_;
  int system_tray_height_;

  DISALLOW_COPY_AND_ASSIGN(AshPopupAlignmentDelegate);
};

}  

#endif  

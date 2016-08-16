// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_VIEWS_MESSAGE_POPUP_COLLECTION_H_
#define UI_MESSAGE_CENTER_VIEWS_MESSAGE_POPUP_COLLECTION_H_

#include <list>
#include <map>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"
#include "ui/message_center/message_center_export.h"
#include "ui/message_center/message_center_observer.h"
#include "ui/message_center/views/message_center_controller.h"
#include "ui/message_center/views/toast_contents_view.h"
#include "ui/views/widget/widget_observer.h"

namespace base {
class RunLoop;
}

namespace views {
class Widget;
}

namespace gfx {
class Display;
class Screen;
}

namespace message_center {
namespace test {
class MessagePopupCollectionTest;
}

class MessageCenter;
class MessageCenterTray;
class MessageViewContextMenuController;
class PopupAlignmentDelegate;

class MESSAGE_CENTER_EXPORT MessagePopupCollection
    : public MessageCenterController,
      public MessageCenterObserver {
 public:
  
  
  
  MessagePopupCollection(gfx::NativeView parent,
                         MessageCenter* message_center,
                         MessageCenterTray* tray,
                         PopupAlignmentDelegate* alignment_delegate);
  virtual ~MessagePopupCollection();

  
  virtual void ClickOnNotification(const std::string& notification_id) OVERRIDE;
  virtual void RemoveNotification(const std::string& notification_id,
                                  bool by_user) OVERRIDE;
  virtual scoped_ptr<ui::MenuModel> CreateMenuModel(
      const NotifierId& notifier_id,
      const base::string16& display_source) OVERRIDE;
  virtual bool HasClickedListener(const std::string& notification_id) OVERRIDE;
  virtual void ClickOnNotificationButton(const std::string& notification_id,
                                         int button_index) OVERRIDE;

  void MarkAllPopupsShown();

  
  
  void OnMouseEntered(ToastContentsView* toast_entered);
  void OnMouseExited(ToastContentsView* toast_exited);

  
  
  
  
  
  void IncrementDeferCounter();
  void DecrementDeferCounter();

  
  
  void DoUpdateIfPossible();

  
  
  void ForgetToast(ToastContentsView* toast);

  
  void OnDisplayMetricsChanged(const gfx::Display& display);

  
  gfx::NativeView parent() const { return parent_; }

 private:
  friend class test::MessagePopupCollectionTest;
  typedef std::list<ToastContentsView*> Toasts;

  
  std::set<std::string> CloseAllWidgets();

  
  void RemoveToast(ToastContentsView* toast, bool mark_as_shown);

  
  
  void UpdateWidgets();

  
  void RepositionWidgets();

  
  
  
  void RepositionWidgetsWithTarget();

  
  
  int GetBaseLine(ToastContentsView* last_toast) const;

  
  virtual void OnNotificationAdded(const std::string& notification_id) OVERRIDE;
  virtual void OnNotificationRemoved(const std::string& notification_id,
                                     bool by_user) OVERRIDE;
  virtual void OnNotificationUpdated(
      const std::string& notification_id) OVERRIDE;

  ToastContentsView* FindToast(const std::string& notification_id) const;

  
  
  
  
  void OnDeferTimerExpired();

  
  views::Widget* GetWidgetForTest(const std::string& id) const;
  void CreateRunLoopForTest();
  void WaitForTest();
  gfx::Rect GetToastRectAt(size_t index) const;

  gfx::NativeView parent_;
  MessageCenter* message_center_;
  MessageCenterTray* tray_;
  Toasts toasts_;

  PopupAlignmentDelegate* alignment_delegate_;

  int defer_counter_;

  
  
  ToastContentsView* latest_toast_entered_;

  
  
  
  
  bool user_is_closing_toasts_by_clicking_;
  scoped_ptr<base::OneShotTimer<MessagePopupCollection> > defer_timer_;
  
  
  
  int target_top_edge_;

  
  scoped_ptr<base::RunLoop> run_loop_for_test_;

  scoped_ptr<MessageViewContextMenuController> context_menu_controller_;

  
  
  base::WeakPtrFactory<MessagePopupCollection> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MessagePopupCollection);
};

}  

#endif 

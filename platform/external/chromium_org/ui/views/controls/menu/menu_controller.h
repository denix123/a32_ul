// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_CONTROLLER_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_CONTROLLER_H_

#include "build/build_config.h"

#include <list>
#include <set>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "ui/events/event.h"
#include "ui/events/event_constants.h"
#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/menu/menu_config.h"
#include "ui/views/controls/menu/menu_delegate.h"
#include "ui/views/widget/widget_observer.h"

namespace base {
class MessagePumpDispatcher;
}
namespace gfx {
class Screen;
}
namespace ui {
class NativeTheme;
class OSExchangeData;
class ScopedEventDispatcher;
}
namespace views {

class MenuButton;
class MenuHostRootView;
class MenuItemView;
class MenuMessageLoop;
class MouseEvent;
class SubmenuView;
class View;

namespace internal {
class MenuControllerDelegate;
class MenuEventDispatcher;
class MenuMessagePumpDispatcher;
class MenuRunnerImpl;
}


class VIEWS_EXPORT MenuController : public WidgetObserver {
 public:
  
  enum ExitType {
    
    EXIT_NONE,

    
    EXIT_ALL,

    
    EXIT_OUTERMOST,

    
    
    EXIT_DESTROYED
  };

  
  static MenuController* GetActiveInstance();

  
  
  
  MenuItemView* Run(Widget* parent,
                    MenuButton* button,
                    MenuItemView* root,
                    const gfx::Rect& bounds,
                    MenuAnchorPosition position,
                    bool context_menu,
                    bool is_nested_drag,
                    int* event_flags);

  
  bool IsBlockingRun() const { return blocking_run_; }

  bool in_nested_run() const { return !menu_stack_.empty(); }

  
  bool drag_in_progress() const { return drag_in_progress_; }

  
  
  bool did_initiate_drag() const { return did_initiate_drag_; }

  
  
  Widget* owner() { return owner_; }

  
  MenuAnchorPosition GetAnchorPosition() { return state_.anchor; }

  
  
  void Cancel(ExitType type);

  
  void CancelAll() { Cancel(EXIT_ALL); }

  
  
  ExitType exit_type() const { return exit_type_; }

  
  base::TimeDelta closing_event_time() const { return closing_event_time_; }

  void set_is_combobox(bool is_combobox) { is_combobox_ = is_combobox; }

  
  
  
  
  void OnMousePressed(SubmenuView* source, const ui::MouseEvent& event);
  void OnMouseDragged(SubmenuView* source, const ui::MouseEvent& event);
  void OnMouseReleased(SubmenuView* source, const ui::MouseEvent& event);
  void OnMouseMoved(SubmenuView* source, const ui::MouseEvent& event);
  void OnMouseEntered(SubmenuView* source, const ui::MouseEvent& event);
  bool OnMouseWheel(SubmenuView* source, const ui::MouseWheelEvent& event);
  void OnGestureEvent(SubmenuView* source, ui::GestureEvent* event);

  bool GetDropFormats(
      SubmenuView* source,
      int* formats,
      std::set<ui::OSExchangeData::CustomFormat>* custom_formats);
  bool AreDropTypesRequired(SubmenuView* source);
  bool CanDrop(SubmenuView* source, const ui::OSExchangeData& data);
  void OnDragEntered(SubmenuView* source, const ui::DropTargetEvent& event);
  int OnDragUpdated(SubmenuView* source, const ui::DropTargetEvent& event);
  void OnDragExited(SubmenuView* source);
  int OnPerformDrop(SubmenuView* source, const ui::DropTargetEvent& event);

  
  void OnDragEnteredScrollButton(SubmenuView* source, bool is_up);
  void OnDragExitedScrollButton(SubmenuView* source);

  
  
  
  void OnDragWillStart();

  
  
  void OnDragComplete(bool should_close);

  
  void UpdateSubmenuSelection(SubmenuView* source);

  
  virtual void OnWidgetDestroying(Widget* widget) OVERRIDE;

  
  bool IsCancelAllTimerRunningForTest();

  
  static void TurnOffMenuSelectionHoldForTest();

 private:
  friend class internal::MenuEventDispatcher;
  friend class internal::MenuMessagePumpDispatcher;
  friend class internal::MenuRunnerImpl;
  friend class MenuControllerTest;
  friend class MenuHostRootView;
  friend class MenuItemView;
  friend class SubmenuView;

  class MenuScrollTask;

  struct SelectByCharDetails;

  
  enum SetSelectionTypes {
    SELECTION_DEFAULT               = 0,

    
    
    SELECTION_UPDATE_IMMEDIATELY    = 1 << 0,

    
    SELECTION_OPEN_SUBMENU          = 1 << 1,

    
    
    SELECTION_EXIT                  = 1 << 2,
  };

  
  enum SendAcceleratorResultType {
    
    ACCELERATOR_NOT_PROCESSED,

    
    ACCELERATOR_PROCESSED,

    
    ACCELERATOR_PROCESSED_EXIT
  };

  
  struct State {
    State();
    ~State();

    
    MenuItemView* item;

    
    bool submenu_open;

    
    gfx::Rect initial_bounds;

    
    MenuAnchorPosition anchor;

    
    std::list<bool> open_leading;

    
    gfx::Rect monitor_bounds;

    
    bool context_menu;
  };

  
  struct MenuPart {
    
    enum Type {
      NONE,
      MENU_ITEM,
      SCROLL_UP,
      SCROLL_DOWN
    };

    MenuPart() : type(NONE), menu(NULL), parent(NULL), submenu(NULL) {}

    
    bool is_scroll() const { return type == SCROLL_DOWN || type == SCROLL_UP; }

    
    Type type;

    
    
    
    
    
    
    MenuItemView* menu;

    
    
    MenuItemView* parent;

    
    SubmenuView* submenu;
  };

  
  
  
  
  
  
  
  void SetSelection(MenuItemView* menu_item, int types);

  void SetSelectionOnPointerDown(SubmenuView* source,
                                 const ui::LocatedEvent& event);
  void StartDrag(SubmenuView* source, const gfx::Point& location);

  
  
  
  bool OnKeyDown(ui::KeyboardCode key_code);

  
  
  MenuController(ui::NativeTheme* theme,
                 bool blocking,
                 internal::MenuControllerDelegate* delegate);

  virtual ~MenuController();

  
  
  
  void RunMessageLoop(bool nested_menu);

  
  SendAcceleratorResultType SendAcceleratorToHotTrackedView();

  void UpdateInitialLocation(const gfx::Rect& bounds,
                             MenuAnchorPosition position,
                             bool context_menu);

  
  
  void Accept(MenuItemView* item, int event_flags);

  bool ShowSiblingMenu(SubmenuView* source, const gfx::Point& mouse_location);

  
  
  
  bool ShowContextMenu(MenuItemView* menu_item,
                       SubmenuView* source,
                       const ui::LocatedEvent& event,
                       ui::MenuSourceType source_type);

  
  void CloseAllNestedMenus();

  
  
  
  
  MenuItemView* GetMenuItemAt(View* menu, int x, int y);

  
  MenuItemView* GetEmptyMenuItemAt(View* source, int x, int y);

  
  
  
  bool IsScrollButtonAt(SubmenuView* source,
                        int x,
                        int y,
                        MenuPart::Type* part);

  
  
  MenuPart GetMenuPart(SubmenuView* source, const gfx::Point& source_loc);

  
  
  MenuPart GetMenuPartByScreenCoordinateUsingMenu(MenuItemView* item,
                                                  const gfx::Point& screen_loc);

  
  
  
  bool GetMenuPartByScreenCoordinateImpl(SubmenuView* menu,
                                         const gfx::Point& screen_loc,
                                         MenuPart* part);

  
  
  bool DoesSubmenuContainLocation(SubmenuView* submenu,
                                  const gfx::Point& screen_loc);

  
  
  
  void CommitPendingSelection();

  
  
  void CloseMenu(MenuItemView* item);

  
  
  void OpenMenu(MenuItemView* item);

  
  
  void OpenMenuImpl(MenuItemView* item, bool show);

  
  
  void MenuChildrenChanged(MenuItemView* item);

  
  
  
  void BuildPathsAndCalculateDiff(MenuItemView* old_item,
                                  MenuItemView* new_item,
                                  std::vector<MenuItemView*>* old_path,
                                  std::vector<MenuItemView*>* new_path,
                                  size_t* first_diff_at);

  
  void BuildMenuItemPath(MenuItemView* item, std::vector<MenuItemView*>* path);

  
  
  void StartShowTimer();
  void StopShowTimer();

  
  
  void StartCancelAllTimer();
  void StopCancelAllTimer();

  
  
  gfx::Rect CalculateMenuBounds(MenuItemView* item,
                                bool prefer_leading,
                                bool* is_leading);

  
  
  gfx::Rect CalculateBubbleMenuBounds(MenuItemView* item,
                                      bool prefer_leading,
                                      bool* is_leading);

  
  static int MenuDepth(MenuItemView* item);

  
  void IncrementSelection(int delta);

  
  
  
  MenuItemView* FindNextSelectableMenuItem(MenuItemView* parent,
                                           int index,
                                           int delta);

  
  
  void OpenSubmenuChangeSelectionIfCan();

  
  void CloseSubmenu();

  
  
  SelectByCharDetails FindChildForMnemonic(
      MenuItemView* parent,
      base::char16 key,
      bool (*match_function)(MenuItemView* menu, base::char16 mnemonic));

  
  
  
  bool AcceptOrSelect(MenuItemView* parent, const SelectByCharDetails& details);

  
  
  bool SelectByChar(base::char16 key);

  
  
  
  
  
  
  void RepostEvent(SubmenuView* source, const ui::LocatedEvent& event);

  
  void SetDropMenuItem(MenuItemView* new_item,
                       MenuDelegate::DropPosition position);

  
  
  void UpdateScrolling(const MenuPart& part);

  
  void StopScrolling();

  
  
  
  
  void UpdateActiveMouseView(SubmenuView* event_source,
                             const ui::MouseEvent& event,
                             View* target_menu);

  
  
  void SendMouseReleaseToActiveView(SubmenuView* event_source,
                                    const ui::MouseEvent& event);

  
  
  void SendMouseCaptureLostToActiveView();

  
  void SetActiveMouseView(View* view);
  View* GetActiveMouseView();

  
  void SetExitType(ExitType type);

  
  void TerminateNestedMessageLoop();

  
  bool ShouldQuitNow() const;

  
  void HandleMouseLocation(SubmenuView* source,
                           const gfx::Point& mouse_location);

  
  gfx::Screen* GetScreen();

  
  static MenuController* active_instance_;

  
  
  
  
  bool blocking_run_;

  
  bool showing_;

  
  ExitType exit_type_;

  
  
  bool did_capture_;

  
  
  
  
  
  
  State pending_state_;
  State state_;

  
  MenuItemView* result_;

  
  int accept_event_flags_;

  
  
  
  typedef std::pair<State, linked_ptr<MenuButton::PressedLock> > NestedState;
  std::list<NestedState> menu_stack_;

  
  
  base::OneShotTimer<MenuController> show_timer_;

  
  
  
  
  base::OneShotTimer<MenuController> cancel_all_timer_;

  
  MenuItemView* drop_target_;
  MenuDelegate::DropPosition drop_position_;

  
  
  Widget* owner_;

  
  bool possible_drag_;

  
  bool drag_in_progress_;

  
  
  
  bool did_initiate_drag_;

  
  gfx::Point press_pt_;

  
  
  bool valid_drop_coordinates_;
  gfx::Point drop_pt_;
  int last_drop_operation_;

  
  bool showing_submenu_;

  
  
  scoped_ptr<MenuScrollTask> scroll_task_;

  
  scoped_ptr<MenuButton::PressedLock> pressed_lock_;

  
  
  const int active_mouse_view_id_;

  internal::MenuControllerDelegate* delegate_;

  
  
  int message_loop_depth_;

  views::MenuConfig menu_config_;

  
  base::TimeDelta closing_event_time_;

  
  base::TimeTicks menu_start_time_;

  
  
  gfx::Point menu_start_mouse_press_loc_;

  
  
  bool is_combobox_;

  
  bool item_selected_by_touch_;

  scoped_ptr<MenuMessageLoop> message_loop_;

  DISALLOW_COPY_AND_ASSIGN(MenuController);
};

}  

#endif  

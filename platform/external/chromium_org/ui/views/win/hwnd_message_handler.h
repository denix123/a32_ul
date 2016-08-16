// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIN_HWND_MESSAGE_HANDLER_H_
#define UI_VIEWS_WIN_HWND_MESSAGE_HANDLER_H_

#include <windows.h>

#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/win/scoped_gdi_object.h"
#include "base/win/win_util.h"
#include "ui/accessibility/ax_enums.h"
#include "ui/base/ui_base_types.h"
#include "ui/base/win/window_event_target.h"
#include "ui/events/event.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/sequential_id_generator.h"
#include "ui/gfx/win/window_impl.h"
#include "ui/views/ime/input_method_delegate.h"
#include "ui/views/views_export.h"

namespace gfx {
class Canvas;
class ImageSkia;
class Insets;
}

namespace ui  {
class ViewProp;
}

namespace views {

class FullscreenHandler;
class HWNDMessageHandlerDelegate;
class InputMethod;

const int WM_NCUAHDRAWCAPTION = 0xAE;
const int WM_NCUAHDRAWFRAME = 0xAF;

#define IsMsgHandled() !ref.get() || msg_handled_

#define BEGIN_SAFE_MSG_MAP_EX(the_class) \
 private: \
  base::WeakPtrFactory<the_class> weak_factory_; \
  BOOL msg_handled_; \
\
 public: \
   \
  void SetMsgHandled(BOOL handled) { \
    msg_handled_ = handled; \
  } \
  BOOL ProcessWindowMessage(HWND hwnd, \
                            UINT msg, \
                            WPARAM w_param, \
                            LPARAM l_param, \
                            LRESULT& l_result, \
                            DWORD msg_map_id = 0) { \
    base::WeakPtr<HWNDMessageHandler> ref(weak_factory_.GetWeakPtr()); \
    BOOL old_msg_handled = msg_handled_; \
    BOOL ret = _ProcessWindowMessage(hwnd, msg, w_param, l_param, l_result, \
                                     msg_map_id); \
    if (ref.get()) \
      msg_handled_ = old_msg_handled; \
    return ret; \
  } \
  BOOL _ProcessWindowMessage(HWND hWnd, \
                             UINT uMsg, \
                             WPARAM wParam, \
                             LPARAM lParam, \
                             LRESULT& lResult, \
                             DWORD dwMsgMapID) { \
    base::WeakPtr<HWNDMessageHandler> ref(weak_factory_.GetWeakPtr()); \
    BOOL bHandled = TRUE; \
    hWnd; \
    uMsg; \
    wParam; \
    lParam; \
    lResult; \
    bHandled; \
    switch(dwMsgMapID) { \
      case 0:

class VIEWS_EXPORT HWNDMessageHandler :
    public gfx::WindowImpl,
    public internal::InputMethodDelegate,
    public ui::WindowEventTarget {
 public:
  explicit HWNDMessageHandler(HWNDMessageHandlerDelegate* delegate);
  ~HWNDMessageHandler();

  void Init(HWND parent, const gfx::Rect& bounds);
  void InitModalType(ui::ModalType modal_type);

  void Close();
  void CloseNow();

  gfx::Rect GetWindowBoundsInScreen() const;
  gfx::Rect GetClientAreaBoundsInScreen() const;
  gfx::Rect GetRestoredBounds() const;
  
  gfx::Rect GetClientAreaBounds() const;

  void GetWindowPlacement(gfx::Rect* bounds,
                          ui::WindowShowState* show_state) const;

  
  
  void SetBounds(const gfx::Rect& bounds_in_pixels, bool force_size_changed);

  void SetSize(const gfx::Size& size);
  void CenterWindow(const gfx::Size& size);

  void SetRegion(HRGN rgn);

  void StackAbove(HWND other_hwnd);
  void StackAtTop();

  void Show();
  void ShowWindowWithState(ui::WindowShowState show_state);
  void ShowMaximizedWithBounds(const gfx::Rect& bounds);
  void Hide();

  void Maximize();
  void Minimize();
  void Restore();

  void Activate();
  void Deactivate();

  void SetAlwaysOnTop(bool on_top);

  bool IsVisible() const;
  bool IsActive() const;
  bool IsMinimized() const;
  bool IsMaximized() const;
  bool IsAlwaysOnTop() const;

  bool RunMoveLoop(const gfx::Vector2d& drag_offset, bool hide_on_escape);
  void EndMoveLoop();

  
  void SendFrameChanged();

  void FlashFrame(bool flash);

  void ClearNativeFocus();

  void SetCapture();
  void ReleaseCapture();
  bool HasCapture() const;

  FullscreenHandler* fullscreen_handler() { return fullscreen_handler_.get(); }

  void SetVisibilityChangedAnimationsEnabled(bool enabled);

  
  bool SetTitle(const base::string16& title);

  void SetCursor(HCURSOR cursor);

  void FrameTypeChanged();

  void SchedulePaintInRect(const gfx::Rect& rect);
  void SetOpacity(BYTE opacity);

  void SetWindowIcons(const gfx::ImageSkia& window_icon,
                      const gfx::ImageSkia& app_icon);

  void set_remove_standard_frame(bool remove_standard_frame) {
    remove_standard_frame_ = remove_standard_frame;
  }

  void set_use_system_default_icon(bool use_system_default_icon) {
    use_system_default_icon_ = use_system_default_icon;
  }

  void SetFullscreen(bool fullscreen);

  
  void SizeConstraintsChanged();

 private:
  typedef std::set<DWORD> TouchIDs;

  
  virtual void DispatchKeyEventPostIME(const ui::KeyEvent& key) OVERRIDE;

  
  virtual HICON GetDefaultWindowIcon() const OVERRIDE;
  virtual LRESULT OnWndProc(UINT message,
                            WPARAM w_param,
                            LPARAM l_param) OVERRIDE;

  
  virtual LRESULT HandleMouseMessage(unsigned int message,
                                     WPARAM w_param,
                                     LPARAM l_param,
                                     bool* handled) OVERRIDE;
  virtual LRESULT HandleKeyboardMessage(unsigned int message,
                                        WPARAM w_param,
                                        LPARAM l_param,
                                        bool* handled) OVERRIDE;
  virtual LRESULT HandleTouchMessage(unsigned int message,
                                     WPARAM w_param,
                                     LPARAM l_param,
                                     bool* handled) OVERRIDE;

  virtual LRESULT HandleScrollMessage(unsigned int message,
                                      WPARAM w_param,
                                      LPARAM l_param,
                                      bool* handled) OVERRIDE;

  virtual LRESULT HandleNcHitTestMessage(unsigned int message,
                                         WPARAM w_param,
                                         LPARAM l_param,
                                         bool* handled) OVERRIDE;

  
  
  
  int GetAppbarAutohideEdges(HMONITOR monitor);

  
  
  void OnAppbarAutohideEdgesChanged();

  
  
  void SetInitialFocus();

  
  
  void PostProcessActivateMessage(int activation_state, bool minimized);

  
  
  void RestoreEnabledIfNecessary();

  
  void ExecuteSystemMenuCommand(int command);

  
  
  void TrackMouseEvents(DWORD mouse_tracking_flags);

  
  
  void ClientAreaSizeChanged();

  
  
  bool GetClientAreaInsets(gfx::Insets* insets) const;

  
  
  
  void ResetWindowRegion(bool force, bool redraw);

  
  
  
  void UpdateDwmNcRenderingPolicy();

  
  
  
  LRESULT DefWindowProcWithRedrawLock(UINT message,
                                      WPARAM w_param,
                                      LPARAM l_param);

  
  
  class ScopedRedrawLock;
  void LockUpdates(bool force);
  void UnlockUpdates(bool force);

  
  void StopIgnoringPosChanges() { ignore_window_pos_changes_ = false; }

  
  
  void RedrawLayeredWindowContents();

  
  
  void ForceRedrawWindow(int attempts);

  

  BEGIN_SAFE_MSG_MAP_EX(HWNDMessageHandler)
    
    CR_MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseRange)
    CR_MESSAGE_RANGE_HANDLER_EX(WM_NCMOUSEMOVE,
                                WM_NCXBUTTONDBLCLK,
                                OnMouseRange)

    
    CR_MESSAGE_HANDLER_EX(WM_NCUAHDRAWCAPTION, OnNCUAHDrawCaption)
    CR_MESSAGE_HANDLER_EX(WM_NCUAHDRAWFRAME, OnNCUAHDrawFrame)

    
    CR_MESSAGE_HANDLER_EX(WM_DWMCOMPOSITIONCHANGED, OnDwmCompositionChanged)

    
    CR_MESSAGE_HANDLER_EX(WM_GETOBJECT, OnGetObject)

    
    CR_MESSAGE_HANDLER_EX(WM_MOUSEACTIVATE, OnMouseActivate)
    CR_MESSAGE_HANDLER_EX(WM_MOUSELEAVE, OnMouseRange)
    CR_MESSAGE_HANDLER_EX(WM_NCMOUSELEAVE, OnMouseRange)
    CR_MESSAGE_HANDLER_EX(WM_SETCURSOR, OnSetCursor);

    
    CR_MESSAGE_HANDLER_EX(WM_KEYDOWN, OnKeyEvent)
    CR_MESSAGE_HANDLER_EX(WM_KEYUP, OnKeyEvent)
    CR_MESSAGE_HANDLER_EX(WM_SYSKEYDOWN, OnKeyEvent)
    CR_MESSAGE_HANDLER_EX(WM_SYSKEYUP, OnKeyEvent)

    
    CR_MESSAGE_HANDLER_EX(WM_IME_SETCONTEXT, OnImeMessages)
    CR_MESSAGE_HANDLER_EX(WM_IME_STARTCOMPOSITION, OnImeMessages)
    CR_MESSAGE_HANDLER_EX(WM_IME_COMPOSITION, OnImeMessages)
    CR_MESSAGE_HANDLER_EX(WM_IME_ENDCOMPOSITION, OnImeMessages)
    CR_MESSAGE_HANDLER_EX(WM_IME_REQUEST, OnImeMessages)
    CR_MESSAGE_HANDLER_EX(WM_IME_NOTIFY, OnImeMessages)
    CR_MESSAGE_HANDLER_EX(WM_CHAR, OnImeMessages)
    CR_MESSAGE_HANDLER_EX(WM_SYSCHAR, OnImeMessages)

    
    CR_MESSAGE_HANDLER_EX(WM_VSCROLL, OnScrollMessage)
    CR_MESSAGE_HANDLER_EX(WM_HSCROLL, OnScrollMessage)

    
    CR_MESSAGE_HANDLER_EX(WM_TOUCH, OnTouchEvent)

    
    
    
    CR_MESSAGE_HANDLER_EX(WM_NCACTIVATE, OnNCActivate)

    
    CR_MSG_WM_ACTIVATEAPP(OnActivateApp)
    CR_MSG_WM_APPCOMMAND(OnAppCommand)
    CR_MSG_WM_CANCELMODE(OnCancelMode)
    CR_MSG_WM_CAPTURECHANGED(OnCaptureChanged)
    CR_MSG_WM_CLOSE(OnClose)
    CR_MSG_WM_COMMAND(OnCommand)
    CR_MSG_WM_CREATE(OnCreate)
    CR_MSG_WM_DESTROY(OnDestroy)
    CR_MSG_WM_DISPLAYCHANGE(OnDisplayChange)
    CR_MSG_WM_ENTERMENULOOP(OnEnterMenuLoop)
    CR_MSG_WM_EXITMENULOOP(OnExitMenuLoop)
    CR_MSG_WM_ENTERSIZEMOVE(OnEnterSizeMove)
    CR_MSG_WM_ERASEBKGND(OnEraseBkgnd)
    CR_MSG_WM_EXITSIZEMOVE(OnExitSizeMove)
    CR_MSG_WM_GETMINMAXINFO(OnGetMinMaxInfo)
    CR_MSG_WM_INITMENU(OnInitMenu)
    CR_MSG_WM_INPUTLANGCHANGE(OnInputLangChange)
    CR_MSG_WM_KILLFOCUS(OnKillFocus)
    CR_MSG_WM_MOVE(OnMove)
    CR_MSG_WM_MOVING(OnMoving)
    CR_MSG_WM_NCCALCSIZE(OnNCCalcSize)
    CR_MSG_WM_NCHITTEST(OnNCHitTest)
    CR_MSG_WM_NCPAINT(OnNCPaint)
    CR_MSG_WM_NOTIFY(OnNotify)
    CR_MSG_WM_PAINT(OnPaint)
    CR_MSG_WM_SETFOCUS(OnSetFocus)
    CR_MSG_WM_SETICON(OnSetIcon)
    CR_MSG_WM_SETTEXT(OnSetText)
    CR_MSG_WM_SETTINGCHANGE(OnSettingChange)
    CR_MSG_WM_SIZE(OnSize)
    CR_MSG_WM_SYSCOMMAND(OnSysCommand)
    CR_MSG_WM_THEMECHANGED(OnThemeChanged)
    CR_MSG_WM_WINDOWPOSCHANGED(OnWindowPosChanged)
    CR_MSG_WM_WINDOWPOSCHANGING(OnWindowPosChanging)
    CR_MSG_WM_WTSSESSION_CHANGE(OnSessionChange)
  CR_END_MSG_MAP()

  
  
  
  
  void OnActivateApp(BOOL active, DWORD thread_id);
  
  
  BOOL OnAppCommand(HWND window, short command, WORD device, int keystate);
  void OnCancelMode();
  void OnCaptureChanged(HWND window);
  void OnClose();
  void OnCommand(UINT notification_code, int command, HWND window);
  LRESULT OnCreate(CREATESTRUCT* create_struct);
  void OnDestroy();
  void OnDisplayChange(UINT bits_per_pixel, const gfx::Size& screen_size);
  LRESULT OnDwmCompositionChanged(UINT msg, WPARAM w_param, LPARAM l_param);
  void OnEnterMenuLoop(BOOL from_track_popup_menu);
  void OnEnterSizeMove();
  LRESULT OnEraseBkgnd(HDC dc);
  void OnExitMenuLoop(BOOL is_shortcut_menu);
  void OnExitSizeMove();
  void OnGetMinMaxInfo(MINMAXINFO* minmax_info);
  LRESULT OnGetObject(UINT message, WPARAM w_param, LPARAM l_param);
  LRESULT OnImeMessages(UINT message, WPARAM w_param, LPARAM l_param);
  void OnInitMenu(HMENU menu);
  void OnInputLangChange(DWORD character_set, HKL input_language_id);
  LRESULT OnKeyEvent(UINT message, WPARAM w_param, LPARAM l_param);
  void OnKillFocus(HWND focused_window);
  LRESULT OnMouseActivate(UINT message, WPARAM w_param, LPARAM l_param);
  LRESULT OnMouseRange(UINT message, WPARAM w_param, LPARAM l_param);
  void OnMove(const gfx::Point& point);
  void OnMoving(UINT param, const RECT* new_bounds);
  LRESULT OnNCActivate(UINT message, WPARAM w_param, LPARAM l_param);
  LRESULT OnNCCalcSize(BOOL mode, LPARAM l_param);
  LRESULT OnNCHitTest(const gfx::Point& point);
  void OnNCPaint(HRGN rgn);
  LRESULT OnNCUAHDrawCaption(UINT message, WPARAM w_param, LPARAM l_param);
  LRESULT OnNCUAHDrawFrame(UINT message, WPARAM w_param, LPARAM l_param);
  LRESULT OnNotify(int w_param, NMHDR* l_param);
  void OnPaint(HDC dc);
  LRESULT OnReflectedMessage(UINT message, WPARAM w_param, LPARAM l_param);
  LRESULT OnScrollMessage(UINT message, WPARAM w_param, LPARAM l_param);
  void OnSessionChange(WPARAM status_code, PWTSSESSION_NOTIFICATION session_id);
  LRESULT OnSetCursor(UINT message, WPARAM w_param, LPARAM l_param);
  void OnSetFocus(HWND last_focused_window);
  LRESULT OnSetIcon(UINT size_type, HICON new_icon);
  LRESULT OnSetText(const wchar_t* text);
  void OnSettingChange(UINT flags, const wchar_t* section);
  void OnSize(UINT param, const gfx::Size& size);
  void OnSysCommand(UINT notification_code, const gfx::Point& point);
  void OnThemeChanged();
  LRESULT OnTouchEvent(UINT message, WPARAM w_param, LPARAM l_param);
  void OnWindowPosChanging(WINDOWPOS* window_pos);
  void OnWindowPosChanged(WINDOWPOS* window_pos);

  typedef std::vector<ui::TouchEvent> TouchEvents;
  
  
  
  void HandleTouchEvents(const TouchEvents& touch_events);

  
  
  void ResetTouchDownContext();

  
  
  
  
  LRESULT HandleMouseEventInternal(UINT message,
                                   WPARAM w_param,
                                   LPARAM l_param,
                                   bool track_mouse);

  
  
  
  
  
  bool IsSynthesizedMouseMessage(unsigned int message,
                                 int message_time,
                                 LPARAM l_param);

  
  void PerformDwmTransition();

  HWNDMessageHandlerDelegate* delegate_;

  scoped_ptr<FullscreenHandler> fullscreen_handler_;

  
  bool waiting_for_close_now_;

  bool remove_standard_frame_;

  bool use_system_default_icon_;

  
  
  bool restored_enabled_;

  
  HCURSOR current_cursor_;

  
  
  HCURSOR previous_cursor_;

  

  
  
  
  DWORD active_mouse_tracking_flags_;

  
  
  bool is_right_mouse_pressed_on_caption_;

  
  TouchIDs touch_ids_;

  

  
  
  int lock_updates_count_;

  

  
  
  
  bool ignore_window_pos_changes_;

  
  
  HMONITOR last_monitor_;
  gfx::Rect last_monitor_rect_, last_work_area_;

  

  
  
  
  
  
  
  
  
  
  
  bool use_layered_buffer_;

  
  BYTE layered_alpha_;

  
  
  scoped_ptr<gfx::Canvas> layered_window_contents_;

  
  
  
  
  
  
  
  gfx::Rect invalid_rect_;

  
  bool waiting_for_redraw_layered_window_contents_;

  
  bool is_first_nccalc_;

  
  base::win::ScopedRegion custom_window_region_;

  
  int menu_depth_;

  
  base::WeakPtrFactory<HWNDMessageHandler> autohide_factory_;

  
  ui::SequentialIDGenerator id_generator_;

  
  bool needs_scroll_styles_;

  
  bool in_size_loop_;

  
  
  scoped_ptr<ui::ViewProp> prop_window_target_;

  
  
  
  
  
  int touch_down_contexts_;

  
  
  
  
  static long last_touch_message_time_;

  
  
  long last_mouse_hwheel_time_;

  
  
  
  
  
  
  bool dwm_transition_desired_;

  DISALLOW_COPY_AND_ASSIGN(HWNDMessageHandler);
};

}  

#endif  

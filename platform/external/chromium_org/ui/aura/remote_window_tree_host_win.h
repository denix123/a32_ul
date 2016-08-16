// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_REMOTE_WINDOW_TREE_HOST_WIN_H_
#define UI_AURA_REMOTE_WINDOW_TREE_HOST_WIN_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "ui/aura/window_tree_host.h"
#include "ui/base/ime/remote_input_method_delegate_win.h"
#include "ui/events/event.h"
#include "ui/events/event_constants.h"
#include "ui/events/event_source.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/metro_viewer/ime_types.h"

struct MetroViewerHostMsg_MouseButtonParams;

namespace base {
class FilePath;
}

namespace ui {
class RemoteInputMethodPrivateWin;
class ViewProp;
}

namespace IPC {
class Message;
class Sender;
}

namespace aura {

class AURA_EXPORT RemoteWindowTreeHostWin
    : public WindowTreeHost,
      public ui::EventSource,
      public ui::internal::RemoteInputMethodDelegateWin {
 public:
  
  
  static RemoteWindowTreeHostWin* Instance();

  
  
  static bool IsValid();

  
  
  
  void SetRemoteWindowHandle(HWND remote_window);
  HWND remote_window() { return remote_window_; }

  
  void Connected(IPC::Sender* host);
  
  void Disconnected();

  
  bool OnMessageReceived(const IPC::Message& message);

  void HandleOpenURLOnDesktop(const base::FilePath& shortcut,
                              const base::string16& url);

  void HandleWindowSizeChanged(uint32 width, uint32 height);

  
  Window* GetAshWindow();

  
  
  bool IsForegroundWindow();

 protected:
  RemoteWindowTreeHostWin();
  virtual ~RemoteWindowTreeHostWin();

 private:
  
  void OnMouseMoved(int32 x, int32 y, int32 flags);
  void OnMouseButton(const MetroViewerHostMsg_MouseButtonParams& params);
  void OnKeyDown(uint32 vkey,
                 uint32 repeat_count,
                 uint32 scan_code,
                 uint32 flags);
  void OnKeyUp(uint32 vkey,
               uint32 repeat_count,
               uint32 scan_code,
               uint32 flags);
  void OnChar(uint32 key_code,
              uint32 repeat_count,
              uint32 scan_code,
              uint32 flags);
  void OnWindowActivated(bool repaint);
  void OnEdgeGesture();
  void OnTouchDown(int32 x, int32 y, uint64 timestamp, uint32 pointer_id);
  void OnTouchUp(int32 x, int32 y, uint64 timestamp, uint32 pointer_id);
  void OnTouchMoved(int32 x, int32 y, uint64 timestamp, uint32 pointer_id);
  void OnSetCursorPosAck();

  
  ui::RemoteInputMethodPrivateWin* GetRemoteInputMethodPrivate();
  void OnImeCandidatePopupChanged(bool visible);
  void OnImeCompositionChanged(
      const base::string16& text,
      int32 selection_start,
      int32 selection_end,
      const std::vector<metro_viewer::UnderlineInfo>& underlines);
  void OnImeTextCommitted(const base::string16& text);
  void OnImeInputSourceChanged(uint16 language_id, bool is_ime);

  
  virtual ui::EventSource* GetEventSource() OVERRIDE;
  virtual gfx::AcceleratedWidget GetAcceleratedWidget() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual gfx::Rect GetBounds() const OVERRIDE;
  virtual void SetBounds(const gfx::Rect& bounds) OVERRIDE;
  virtual gfx::Point GetLocationOnNativeScreen() const OVERRIDE;
  virtual void SetCapture() OVERRIDE;
  virtual void ReleaseCapture() OVERRIDE;
  virtual void PostNativeEvent(const base::NativeEvent& native_event) OVERRIDE;
  virtual void SetCursorNative(gfx::NativeCursor cursor) OVERRIDE;
  virtual void MoveCursorToNative(const gfx::Point& location) OVERRIDE;
  virtual void OnCursorVisibilityChangedNative(bool show) OVERRIDE;

  
  virtual ui::EventProcessor* GetEventProcessor() OVERRIDE;

  
  virtual void CancelComposition() OVERRIDE;
  virtual void OnTextInputClientUpdated(
      const std::vector<int32>& input_scopes,
      const std::vector<gfx::Rect>& composition_character_bounds) OVERRIDE;

  
  
  
  
  
  void DispatchKeyboardMessage(ui::EventType type,
                               uint32 vkey,
                               uint32 repeat_count,
                               uint32 scan_code,
                               uint32 flags,
                               bool is_character);

  
  
  
  void SetEventFlags(uint32 flags);

  uint32 mouse_event_flags() const {
    return event_flags_ & (ui::EF_LEFT_MOUSE_BUTTON |
                           ui::EF_MIDDLE_MOUSE_BUTTON |
                           ui::EF_RIGHT_MOUSE_BUTTON);
  }

  uint32 key_event_flags() const {
    return event_flags_ & (ui::EF_SHIFT_DOWN | ui::EF_CONTROL_DOWN |
                           ui::EF_ALT_DOWN | ui::EF_CAPS_LOCK_DOWN);
  }

  HWND remote_window_;
  IPC::Sender* host_;
  scoped_ptr<ui::ViewProp> prop_;

  
  
  int ignore_mouse_moves_until_set_cursor_ack_;

  
  scoped_ptr<ui::MouseEvent> last_mouse_click_event_;

  
  
  uint32 event_flags_;

  
  gfx::Size window_size_;

  DISALLOW_COPY_AND_ASSIGN(RemoteWindowTreeHostWin);
};

}  

#endif  

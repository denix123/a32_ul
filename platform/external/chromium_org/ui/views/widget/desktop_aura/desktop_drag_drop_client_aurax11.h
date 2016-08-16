// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_DRAG_DROP_CLIENT_AURAX11_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_DRAG_DROP_CLIENT_AURAX11_H_

#include <set>
#include <vector>
#include <X11/Xlib.h>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "ui/aura/window_observer.h"
#include "ui/base/cursor/cursor.h"
#include "ui/base/dragdrop/drag_drop_types.h"
#include "ui/gfx/point.h"
#include "ui/gfx/x/x11_atom_cache.h"
#include "ui/views/views_export.h"
#include "ui/views/widget/desktop_aura/x11_move_loop_delegate.h"
#include "ui/wm/public/drag_drop_client.h"

namespace aura {
namespace client {
class DragDropDelegate;
}
}

namespace gfx {
class ImageSkia;
class Point;
}

namespace ui {
class DragSource;
class DropTargetEvent;
class OSExchangeData;
class OSExchangeDataProviderAuraX11;
class SelectionFormatMap;
}

namespace views {
class DesktopNativeCursorManager;
class Widget;
class X11MoveLoop;

class VIEWS_EXPORT DesktopDragDropClientAuraX11
    : public aura::client::DragDropClient,
      public aura::WindowObserver,
      public X11MoveLoopDelegate {
 public:
  DesktopDragDropClientAuraX11(
      aura::Window* root_window,
      views::DesktopNativeCursorManager* cursor_manager,
      Display* xdisplay,
      ::Window xwindow);
  virtual ~DesktopDragDropClientAuraX11();

  
  
  
  static DesktopDragDropClientAuraX11* GetForWindow(::Window window);

  void Init();

  
  void OnXdndEnter(const XClientMessageEvent& event);
  void OnXdndLeave(const XClientMessageEvent& event);
  void OnXdndPosition(const XClientMessageEvent& event);
  void OnXdndStatus(const XClientMessageEvent& event);
  void OnXdndFinished(const XClientMessageEvent& event);
  void OnXdndDrop(const XClientMessageEvent& event);

  
  void OnSelectionNotify(const XSelectionEvent& xselection);

  
  virtual int StartDragAndDrop(
      const ui::OSExchangeData& data,
      aura::Window* root_window,
      aura::Window* source_window,
      const gfx::Point& root_location,
      int operation,
      ui::DragDropTypes::DragEventSource source) OVERRIDE;
  virtual void DragUpdate(aura::Window* target,
                          const ui::LocatedEvent& event) OVERRIDE;
  virtual void Drop(aura::Window* target,
                    const ui::LocatedEvent& event) OVERRIDE;
  virtual void DragCancel() OVERRIDE;
  virtual bool IsDragDropInProgress() OVERRIDE;

  
  virtual void OnWindowDestroyed(aura::Window* window) OVERRIDE;

  
  virtual void OnMouseMovement(XMotionEvent* event) OVERRIDE;
  virtual void OnMouseReleased() OVERRIDE;
  virtual void OnMoveLoopEnded() OVERRIDE;

 protected:
  

  
  virtual scoped_ptr<X11MoveLoop> CreateMoveLoop(
      X11MoveLoopDelegate* delegate);

  
  
  virtual ::Window FindWindowFor(const gfx::Point& screen_point);

  
  
  virtual void SendXClientEvent(::Window xid, XEvent* xev);

 private:
  enum SourceState {
    
    
    SOURCE_STATE_PENDING_DROP,

    
    
    
    SOURCE_STATE_DROPPED,

    
    
    SOURCE_STATE_OTHER,
  };

  
  void ProcessMouseMove(const gfx::Point& screen_point,
                        unsigned long event_time);

  
  
  void StartEndMoveLoopTimer();

  
  void EndMoveLoop();

  
  
  
  void DragTranslate(const gfx::Point& root_window_location,
                     scoped_ptr<ui::OSExchangeData>* data,
                     scoped_ptr<ui::DropTargetEvent>* event,
                     aura::client::DragDropDelegate** delegate);

  
  
  void NotifyDragLeave();

  
  
  ::Atom DragOperationToAtom(int drag_operation);

  
  ui::DragDropTypes::DragOperation AtomToDragOperation(::Atom atom);

  
  
  
  std::vector< ::Atom> GetOfferedDragOperations();

  
  
  
  ui::SelectionFormatMap GetFormatMap() const;

  
  
  
  void CompleteXdndPosition(::Window source_window,
                            const gfx::Point& screen_point);

  void SendXdndEnter(::Window dest_window);
  void SendXdndLeave(::Window dest_window);
  void SendXdndPosition(::Window dest_window,
                        const gfx::Point& screen_point,
                        unsigned long event_time);
  void SendXdndDrop(::Window dest_window);

  
  void CreateDragWidget(const gfx::ImageSkia& image);

  
  
  bool IsValidDragImage(const gfx::ImageSkia& image);

  
  
  scoped_ptr<X11MoveLoop> move_loop_;

  aura::Window* root_window_;

  Display* xdisplay_;
  ::Window xwindow_;

  ui::X11AtomCache atom_cache_;

  
  class X11DragContext;
  scoped_ptr<X11DragContext> target_current_context_;

  
  
  
  
  
  aura::Window* target_window_;

  
  
  
  gfx::Point target_window_location_;
  gfx::Point target_window_root_location_;

  
  
  bool waiting_on_status_;

  
  
  scoped_ptr<std::pair<gfx::Point, unsigned long> > next_position_message_;

  
  
  
  base::OneShotTimer<DesktopDragDropClientAuraX11> repeat_mouse_move_timer_;

  
  
  
  bool status_received_since_enter_;

  
  ui::OSExchangeDataProviderAuraX11 const* source_provider_;
  ::Window source_current_window_;
  SourceState source_state_;

  
  
  
  static DesktopDragDropClientAuraX11* g_current_drag_drop_client;

  
  int drag_operation_;

  
  
  
  
  
  ui::DragDropTypes::DragOperation negotiated_operation_;

  
  
  base::OneShotTimer<DesktopDragDropClientAuraX11> end_move_loop_timer_;

  
  scoped_ptr<Widget> drag_widget_;

  
  gfx::Vector2d drag_widget_offset_;

  
  gfx::NativeCursor grab_cursor_;
  gfx::NativeCursor copy_grab_cursor_;
  gfx::NativeCursor move_grab_cursor_;

  base::WeakPtrFactory<DesktopDragDropClientAuraX11> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DesktopDragDropClientAuraX11);
};

}  

#endif  

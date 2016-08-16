// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_WINDOW_TREE_HOST_X11_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_WINDOW_TREE_HOST_X11_H_

#include <X11/extensions/shape.h>
#include <X11/Xlib.h>

#include "base/basictypes.h"
#include "base/cancelable_callback.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "ui/aura/window_tree_host.h"
#include "ui/base/cursor/cursor_loader_x11.h"
#include "ui/events/event_source.h"
#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/gfx/insets.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"
#include "ui/gfx/x/x11_atom_cache.h"
#include "ui/views/views_export.h"
#include "ui/views/widget/desktop_aura/desktop_window_tree_host.h"

namespace gfx {
class ImageSkia;
class ImageSkiaRep;
}

namespace ui {
class EventHandler;
}

namespace views {
class DesktopDragDropClientAuraX11;
class DesktopDispatcherClient;
class DesktopWindowTreeHostObserverX11;
class X11DesktopWindowMoveClient;
class X11WindowEventFilter;

class VIEWS_EXPORT DesktopWindowTreeHostX11
    : public DesktopWindowTreeHost,
      public aura::WindowTreeHost,
      public ui::EventSource,
      public ui::PlatformEventDispatcher {
 public:
  DesktopWindowTreeHostX11(
      internal::NativeWidgetDelegate* native_widget_delegate,
      DesktopNativeWidgetAura* desktop_native_widget_aura);
  virtual ~DesktopWindowTreeHostX11();

  
  static aura::Window* GetContentWindowForXID(XID xid);

  
  static DesktopWindowTreeHostX11* GetHostForXID(XID xid);

  
  
  
  static std::vector<aura::Window*> GetAllOpenWindows();

  
  gfx::Rect GetX11RootWindowBounds() const;

  
  
  gfx::Rect GetX11RootWindowOuterBounds() const;

  
  
  ::Region GetWindowShape() const;

  
  
  void HandleNativeWidgetActivationChanged(bool active);

  void AddObserver(views::DesktopWindowTreeHostObserverX11* observer);
  void RemoveObserver(views::DesktopWindowTreeHostObserverX11* observer);

  
  void SwapNonClientEventHandler(scoped_ptr<ui::EventHandler> handler);

  
  static void CleanUpWindowList();

 protected:
  
  virtual void Init(aura::Window* content_window,
                    const Widget::InitParams& params) OVERRIDE;
  virtual void OnNativeWidgetCreated(const Widget::InitParams& params) OVERRIDE;
  virtual scoped_ptr<corewm::Tooltip> CreateTooltip() OVERRIDE;
  virtual scoped_ptr<aura::client::DragDropClient>
      CreateDragDropClient(DesktopNativeCursorManager* cursor_manager) OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual void CloseNow() OVERRIDE;
  virtual aura::WindowTreeHost* AsWindowTreeHost() OVERRIDE;
  virtual void ShowWindowWithState(ui::WindowShowState show_state) OVERRIDE;
  virtual void ShowMaximizedWithBounds(
      const gfx::Rect& restored_bounds) OVERRIDE;
  virtual bool IsVisible() const OVERRIDE;
  virtual void SetSize(const gfx::Size& requested_size) OVERRIDE;
  virtual void StackAtTop() OVERRIDE;
  virtual void CenterWindow(const gfx::Size& size) OVERRIDE;
  virtual void GetWindowPlacement(
      gfx::Rect* bounds,
      ui::WindowShowState* show_state) const OVERRIDE;
  virtual gfx::Rect GetWindowBoundsInScreen() const OVERRIDE;
  virtual gfx::Rect GetClientAreaBoundsInScreen() const OVERRIDE;
  virtual gfx::Rect GetRestoredBounds() const OVERRIDE;
  virtual gfx::Rect GetWorkAreaBoundsInScreen() const OVERRIDE;
  virtual void SetShape(gfx::NativeRegion native_region) OVERRIDE;
  virtual void Activate() OVERRIDE;
  virtual void Deactivate() OVERRIDE;
  virtual bool IsActive() const OVERRIDE;
  virtual void Maximize() OVERRIDE;
  virtual void Minimize() OVERRIDE;
  virtual void Restore() OVERRIDE;
  virtual bool IsMaximized() const OVERRIDE;
  virtual bool IsMinimized() const OVERRIDE;
  virtual bool HasCapture() const OVERRIDE;
  virtual void SetAlwaysOnTop(bool always_on_top) OVERRIDE;
  virtual bool IsAlwaysOnTop() const OVERRIDE;
  virtual void SetVisibleOnAllWorkspaces(bool always_visible) OVERRIDE;
  virtual bool SetWindowTitle(const base::string16& title) OVERRIDE;
  virtual void ClearNativeFocus() OVERRIDE;
  virtual Widget::MoveLoopResult RunMoveLoop(
      const gfx::Vector2d& drag_offset,
      Widget::MoveLoopSource source,
      Widget::MoveLoopEscapeBehavior escape_behavior) OVERRIDE;
  virtual void EndMoveLoop() OVERRIDE;
  virtual void SetVisibilityChangedAnimationsEnabled(bool value) OVERRIDE;
  virtual bool ShouldUseNativeFrame() const OVERRIDE;
  virtual bool ShouldWindowContentsBeTransparent() const OVERRIDE;
  virtual void FrameTypeChanged() OVERRIDE;
  virtual void SetFullscreen(bool fullscreen) OVERRIDE;
  virtual bool IsFullscreen() const OVERRIDE;
  virtual void SetOpacity(unsigned char opacity) OVERRIDE;
  virtual void SetWindowIcons(const gfx::ImageSkia& window_icon,
                              const gfx::ImageSkia& app_icon) OVERRIDE;
  virtual void InitModalType(ui::ModalType modal_type) OVERRIDE;
  virtual void FlashFrame(bool flash_frame) OVERRIDE;
  virtual void OnRootViewLayout() OVERRIDE;
  virtual void OnNativeWidgetFocus() OVERRIDE;
  virtual void OnNativeWidgetBlur() OVERRIDE;
  virtual bool IsAnimatingClosed() const OVERRIDE;
  virtual bool IsTranslucentWindowOpacitySupported() const OVERRIDE;
  virtual void SizeConstraintsChanged() OVERRIDE;

  
  virtual ui::EventSource* GetEventSource() OVERRIDE;
  virtual gfx::AcceleratedWidget GetAcceleratedWidget() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual gfx::Rect GetBounds() const OVERRIDE;
  virtual void SetBounds(const gfx::Rect& requested_bounds) OVERRIDE;
  virtual gfx::Point GetLocationOnNativeScreen() const OVERRIDE;
  virtual void SetCapture() OVERRIDE;
  virtual void ReleaseCapture() OVERRIDE;
  virtual void PostNativeEvent(const base::NativeEvent& native_event) OVERRIDE;
  virtual void SetCursorNative(gfx::NativeCursor cursor) OVERRIDE;
  virtual void MoveCursorToNative(const gfx::Point& location) OVERRIDE;
  virtual void OnCursorVisibilityChangedNative(bool show) OVERRIDE;

  
  virtual ui::EventProcessor* GetEventProcessor() OVERRIDE;

 private:
  
  
  void InitX11Window(const Widget::InitParams& params);

  
  
  aura::WindowEventDispatcher* InitDispatcher(const Widget::InitParams& params);

  
  
  
  gfx::Size AdjustSize(const gfx::Size& requested_size);

  
  void OnWMStateUpdated();

  
  void OnFrameExtentsUpdated();

  
  void UpdateMinAndMaxSize();

  
  void UpdateWMUserTime(const ui::PlatformEvent& event);

  
  
  void SetWMSpecState(bool enabled, ::Atom state1, ::Atom state2);

  
  bool HasWMSpecProperty(const char* property) const;

  
  void SetUseNativeFrame(bool use_native_frame);

  
  
  
  void DispatchMouseEvent(ui::MouseEvent* event);

  
  
  
  void DispatchTouchEvent(ui::TouchEvent* event);

  
  void ResetWindowRegion();

  
  void SerializeImageRepresentation(const gfx::ImageSkiaRep& rep,
                                    std::vector<unsigned long>* data);

  
  
  Visual* GetARGBVisual();

  
  static std::list<XID>& open_windows();

  
  void MapWindow(ui::WindowShowState show_state);

  void SetWindowTransparency();

  
  void Relayout();

  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

  void DelayedResize(const gfx::Size& size);

  
  
  XDisplay* xdisplay_;
  ::Window xwindow_;

  
  ::Window x_root_window_;

  ui::X11AtomCache atom_cache_;

  
  bool window_mapped_;

  
  gfx::Rect bounds_;

  
  
  
  
  
  
  gfx::Rect previous_bounds_;

  
  gfx::Rect restored_bounds_;

  
  gfx::Size min_size_;

  
  gfx::Size max_size_;

  
  std::set< ::Atom> window_properties_;

  
  bool is_fullscreen_;

  
  bool is_always_on_top_;

  
  bool use_native_frame_;

  
  bool should_maximize_after_map_;

  
  bool use_argb_visual_;

  DesktopDragDropClientAuraX11* drag_drop_client_;

  scoped_ptr<ui::EventHandler> x11_non_client_event_filter_;
  scoped_ptr<X11DesktopWindowMoveClient> x11_window_move_client_;

  
  
  internal::NativeWidgetDelegate* native_widget_delegate_;

  DesktopNativeWidgetAura* desktop_native_widget_aura_;

  aura::Window* content_window_;

  
  
  DesktopWindowTreeHostX11* window_parent_;
  std::set<DesktopWindowTreeHostX11*> window_children_;

  ObserverList<DesktopWindowTreeHostObserverX11> observer_list_;

  
  ::Region window_shape_;

  
  bool custom_window_shape_;

  
  gfx::Insets native_window_frame_borders_;

  
  
  static DesktopWindowTreeHostX11* g_current_capture;

  
  
  static std::list<XID>* open_windows_;

  base::string16 window_title_;

  
  
  
  
  bool urgency_hint_set_;

  base::CancelableCallback<void()> delayed_resize_task_;

  base::WeakPtrFactory<DesktopWindowTreeHostX11> close_widget_factory_;

  DISALLOW_COPY_AND_ASSIGN(DesktopWindowTreeHostX11);
};

}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_APPS_NATIVE_APP_WINDOW_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_APPS_NATIVE_APP_WINDOW_COCOA_H_

#import <Cocoa/Cocoa.h>
#include <vector>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#import "chrome/browser/ui/cocoa/browser_command_executor.h"
#include "content/public/browser/web_contents_observer.h"
#include "extensions/browser/app_window/app_window.h"
#include "extensions/browser/app_window/native_app_window.h"
#include "extensions/browser/app_window/size_constraints.h"
#include "extensions/common/draggable_region.h"
#include "ui/base/accelerators/accelerator_manager.h"
#include "ui/gfx/rect.h"

class ExtensionKeybindingRegistryCocoa;
class NativeAppWindowCocoa;
@class ShellNSWindow;
class SkRegion;

@interface NativeAppWindowController : NSWindowController
                                      <NSWindowDelegate,
                                       BrowserCommandExecutor> {
 @private
  NativeAppWindowCocoa* appWindow_;  
}

@property(assign, nonatomic) NativeAppWindowCocoa* appWindow;

- (BOOL)handledByExtensionCommand:(NSEvent*)event
    priority:(ui::AcceleratorManager::HandlerPriority)priority;

@end

class NativeAppWindowCocoa : public extensions::NativeAppWindow,
                             public content::WebContentsObserver {
 public:
  NativeAppWindowCocoa(extensions::AppWindow* app_window,
                       const extensions::AppWindow::CreateParams& params);

  
  virtual bool IsActive() const OVERRIDE;
  virtual bool IsMaximized() const OVERRIDE;
  virtual bool IsMinimized() const OVERRIDE;
  virtual bool IsFullscreen() const OVERRIDE;
  virtual gfx::NativeWindow GetNativeWindow() OVERRIDE;
  virtual gfx::Rect GetRestoredBounds() const OVERRIDE;
  virtual ui::WindowShowState GetRestoredState() const OVERRIDE;
  virtual gfx::Rect GetBounds() const OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void ShowInactive() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual void Activate() OVERRIDE;
  virtual void Deactivate() OVERRIDE;
  virtual void Maximize() OVERRIDE;
  virtual void Minimize() OVERRIDE;
  virtual void Restore() OVERRIDE;
  virtual void SetBounds(const gfx::Rect& bounds) OVERRIDE;
  virtual void FlashFrame(bool flash) OVERRIDE;
  virtual bool IsAlwaysOnTop() const OVERRIDE;

  
  void WindowWillClose();

  
  void WindowDidBecomeKey();

  
  void WindowDidResignKey();

  
  
  void WindowDidFinishResize();

  
  
  void WindowDidResize();

  
  void WindowDidMove();

  
  void WindowDidMiniaturize();

  
  void WindowDidDeminiaturize();

  
  void WindowWillZoom();

  
  void WindowDidEnterFullscreen();

  
  void WindowDidExitFullscreen();

  
  bool HandledByExtensionCommand(
      NSEvent* event,
      ui::AcceleratorManager::HandlerPriority priority);

  
  
  bool IsWithinDraggableRegion(NSPoint point) const;

  NSRect restored_bounds() const { return restored_bounds_; }

 protected:
  
  virtual void SetFullscreen(int fullscreen_types) OVERRIDE;
  virtual bool IsFullscreenOrPending() const OVERRIDE;
  virtual void UpdateWindowIcon() OVERRIDE;
  virtual void UpdateWindowTitle() OVERRIDE;
  virtual void UpdateBadgeIcon() OVERRIDE;
  virtual void UpdateShape(scoped_ptr<SkRegion> region) OVERRIDE;
  virtual void UpdateDraggableRegions(
      const std::vector<extensions::DraggableRegion>& regions) OVERRIDE;
  virtual SkRegion* GetDraggableRegion() OVERRIDE;
  virtual void HandleKeyboardEvent(
      const content::NativeWebKeyboardEvent& event) OVERRIDE;
  virtual bool IsFrameless() const OVERRIDE;
  virtual bool HasFrameColor() const OVERRIDE;
  virtual SkColor ActiveFrameColor() const OVERRIDE;
  virtual SkColor InactiveFrameColor() const OVERRIDE;
  virtual gfx::Insets GetFrameInsets() const OVERRIDE;
  virtual bool CanHaveAlphaEnabled() const OVERRIDE;

  
  
  
  virtual void ShowWithApp() OVERRIDE;
  virtual void HideWithApp() OVERRIDE;
  virtual void UpdateShelfMenu() OVERRIDE;
  virtual gfx::Size GetContentMinimumSize() const OVERRIDE;
  virtual gfx::Size GetContentMaximumSize() const OVERRIDE;
  virtual void SetContentSizeConstraints(const gfx::Size& min_size,
                                         const gfx::Size& max_size) OVERRIDE;
  virtual void SetVisibleOnAllWorkspaces(bool always_visible) OVERRIDE;

  
  virtual void RenderViewCreated(content::RenderViewHost* rvh) OVERRIDE;

  virtual void SetAlwaysOnTop(bool always_on_top) OVERRIDE;

  
  virtual gfx::NativeView GetHostView() const OVERRIDE;
  virtual gfx::Point GetDialogPosition(const gfx::Size& size) OVERRIDE;
  virtual gfx::Size GetMaximumDialogSize() OVERRIDE;
  virtual void AddObserver(
      web_modal::ModalDialogHostObserver* observer) OVERRIDE;
  virtual void RemoveObserver(
      web_modal::ModalDialogHostObserver* observer) OVERRIDE;

 private:
  virtual ~NativeAppWindowCocoa();

  ShellNSWindow* window() const;
  content::WebContents* WebContents() const;

  
  
  NSUInteger GetWindowStyleMask() const;

  void InstallView();
  void UninstallView();
  void UpdateDraggableRegionViews();

  
  void UpdateRestoredBounds();

  
  void HideWithoutMarkingHidden();

  extensions::AppWindow* app_window_;  

  bool has_frame_;

  
  
  bool is_hidden_with_app_;

  bool is_maximized_;
  bool is_fullscreen_;
  NSRect restored_bounds_;

  bool is_resizable_;
  bool shows_resize_controls_;
  bool shows_fullscreen_controls_;

  extensions::SizeConstraints size_constraints_;

  bool has_frame_color_;
  SkColor active_frame_color_;
  SkColor inactive_frame_color_;

  base::scoped_nsobject<NativeAppWindowController> window_controller_;

  
  
  std::vector<extensions::DraggableRegion> draggable_regions_;

  
  
  scoped_ptr<ExtensionKeybindingRegistryCocoa> extension_keybinding_registry_;

  DISALLOW_COPY_AND_ASSIGN(NativeAppWindowCocoa);
};

#endif  

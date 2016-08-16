// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_APP_WINDOW_NATIVE_APP_WINDOW_H_
#define EXTENSIONS_BROWSER_APP_WINDOW_NATIVE_APP_WINDOW_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "components/web_modal/web_contents_modal_dialog_host.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/base/base_window.h"
#include "ui/gfx/insets.h"

namespace content {
struct NativeWebKeyboardEvent;
}

namespace extensions {

struct DraggableRegion;

class NativeAppWindow : public ui::BaseWindow,
                        public web_modal::WebContentsModalDialogHost {
 public:
  
  
  virtual void SetFullscreen(int fullscreen_types) = 0;

  
  virtual bool IsFullscreenOrPending() const = 0;

  
  virtual void UpdateWindowIcon() = 0;

  
  virtual void UpdateWindowTitle() = 0;

  
  virtual void UpdateBadgeIcon() = 0;

  
  virtual void UpdateDraggableRegions(
      const std::vector<DraggableRegion>& regions) = 0;

  
  virtual SkRegion* GetDraggableRegion() = 0;

  
  
  virtual void UpdateShape(scoped_ptr<SkRegion> region) = 0;

  
  
  virtual void HandleKeyboardEvent(
      const content::NativeWebKeyboardEvent& event) = 0;

  
  
  virtual bool IsFrameless() const = 0;

  
  virtual bool HasFrameColor() const = 0;
  virtual SkColor ActiveFrameColor() const = 0;
  virtual SkColor InactiveFrameColor() const = 0;

  
  
  virtual gfx::Insets GetFrameInsets() const = 0;

  
  
  
  virtual void ShowWithApp() = 0;
  virtual void HideWithApp() = 0;

  
  
  virtual void UpdateShelfMenu() = 0;

  
  virtual gfx::Size GetContentMinimumSize() const = 0;

  
  virtual gfx::Size GetContentMaximumSize() const = 0;

  
  virtual void SetContentSizeConstraints(const gfx::Size& min_size,
                                         const gfx::Size& max_size) = 0;

  
  virtual void SetVisibleOnAllWorkspaces(bool always_visible) = 0;

  
  
  virtual bool CanHaveAlphaEnabled() const = 0;

  virtual ~NativeAppWindow() {}
};

}  

#endif  

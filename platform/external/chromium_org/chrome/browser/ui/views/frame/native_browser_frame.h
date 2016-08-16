// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_NATIVE_BROWSER_FRAME_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_NATIVE_BROWSER_FRAME_H_

#include "ui/base/ui_base_types.h"
#include "ui/gfx/rect.h"

class BrowserFrame;
class BrowserView;

namespace views {
class NativeWidget;
}

class NativeBrowserFrame {
 public:
  virtual ~NativeBrowserFrame() {}

  virtual views::NativeWidget* AsNativeWidget() = 0;
  virtual const views::NativeWidget* AsNativeWidget() const = 0;

  
  
  virtual bool UsesNativeSystemMenu() const = 0;

  
  virtual bool ShouldSaveWindowPlacement() const = 0;

  
  virtual void GetWindowPlacement(gfx::Rect* bounds,
                                  ui::WindowShowState* show_state) const = 0;

 protected:
  friend class BrowserFrame;

  
  
  virtual int GetMinimizeButtonOffset() const = 0;
};

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_VIEW_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_VIEW_H_

#include "ui/gfx/native_widget_types.h"

class Browser;

namespace content {
struct NativeWebKeyboardEvent;
class WebContents;
}

namespace gfx {
class Size;
}

namespace extensions {

class ExtensionView {
 public:
  virtual ~ExtensionView() {}

  
  virtual void Init() = 0;

  
  virtual Browser* GetBrowser() = 0;

  
  virtual gfx::NativeView GetNativeView() = 0;

  
  
  virtual void ResizeDueToAutoResize(const gfx::Size& new_size) = 0;

  
  
  virtual void RenderViewCreated() = 0;

  
  virtual void HandleKeyboardEvent(
      content::WebContents* source,
      const content::NativeWebKeyboardEvent& event) = 0;

  
  virtual void DidStopLoading() = 0;
};

}  

#endif  

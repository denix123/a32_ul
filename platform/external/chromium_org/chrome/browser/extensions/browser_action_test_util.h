// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_BROWSER_ACTION_TEST_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_BROWSER_ACTION_TEST_UTIL_H_

#include <string>

#include "build/build_config.h"
#include "ui/gfx/native_widget_types.h"

class Browser;
class ExtensionAction;

namespace gfx {
class Image;
class Rect;
class Size;
}  

class BrowserActionTestUtil {
 public:
  explicit BrowserActionTestUtil(Browser* browser) : browser_(browser) {}

  
  int NumberOfBrowserActions();

  
  int VisibleBrowserActions();

  
  ExtensionAction* GetExtensionAction(int index);

  
  void InspectPopup(int index);

  
  
  
  bool HasIcon(int index);

  
  gfx::Image GetIcon(int index);

  
  void Press(int index);

  
  std::string GetExtensionId(int index);

  
  std::string GetTooltip(int index);

  gfx::NativeView GetPopupNativeView();

  
  bool HasPopup();

  
  gfx::Rect GetPopupBounds();

  
  bool HidePopup();

  
  void SetIconVisibilityCount(size_t icons);

  
  static gfx::Size GetMinPopupSize();

  
  static gfx::Size GetMaxPopupSize();

 private:
  Browser* browser_;  
};

#endif  

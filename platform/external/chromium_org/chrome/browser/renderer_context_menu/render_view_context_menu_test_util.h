// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_TEST_UTIL_H_
#define CHROME_BROWSER_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_TEST_UTIL_H_

#include "base/basictypes.h"
#include "chrome/browser/extensions/context_menu_matcher.h"
#include "chrome/browser/renderer_context_menu/render_view_context_menu.h"
#include "url/gurl.h"

class Browser;

namespace content {
class WebContents;
}
namespace ui {
class MenuModel;
}

class TestRenderViewContextMenu : public RenderViewContextMenu {
 public:
  TestRenderViewContextMenu(content::RenderFrameHost* render_frame_host,
                            content::ContextMenuParams params);
  virtual ~TestRenderViewContextMenu();

  
  
  
  
  static TestRenderViewContextMenu* Create(content::WebContents* web_contents,
                                           const GURL& page_url,
                                           const GURL& link_url,
                                           const GURL& frame_url);

  
  virtual bool GetAcceleratorForCommandId(
      int command_id,
      ui::Accelerator* accelerator) OVERRIDE;

  
  
  
  bool IsItemPresent(int command_id);

  
  
  
  bool GetMenuModelAndItemIndex(int command_id,
                                ui::MenuModel** found_model,
                                int* found_index);

  extensions::ContextMenuMatcher& extension_items() { return extension_items_; }

 private:
  DISALLOW_COPY_AND_ASSIGN(TestRenderViewContextMenu);
};

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RENDERER_CONTEXT_MENU_CONTEXT_MENU_DELEGATE_H_
#define COMPONENTS_RENDERER_CONTEXT_MENU_CONTEXT_MENU_DELEGATE_H_

#include "base/memory/scoped_ptr.h"

class RenderViewContextMenu;

namespace content {
class WebContents;
struct ContextMenuParams;
}

class ContextMenuDelegate {
 public:
  explicit ContextMenuDelegate(content::WebContents* web_contents);
  virtual ~ContextMenuDelegate();

  static ContextMenuDelegate* FromWebContents(
      content::WebContents* web_contents);

  
  
  virtual scoped_ptr<RenderViewContextMenu> BuildMenu(
      content::WebContents* web_contents,
      const content::ContextMenuParams& params) = 0;

  
  virtual void ShowMenu(scoped_ptr<RenderViewContextMenu> menu) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(ContextMenuDelegate);
};

#endif  

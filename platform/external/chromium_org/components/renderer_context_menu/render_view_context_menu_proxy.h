// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_PROXY_H_
#define COMPONENTS_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_PROXY_H_

#include "base/strings/string16.h"

namespace content {
class BrowserContext;
class RenderViewHost;
class WebContents;
}

class RenderViewContextMenuProxy {
 public:
  
  virtual void AddMenuItem(int command_id, const base::string16& title) = 0;
  virtual void AddCheckItem(int command_id, const base::string16& title) = 0;
  virtual void AddSeparator() = 0;

  
  virtual void AddSubMenu(int command_id,
                          const base::string16& label,
                          ui::MenuModel* model) = 0;

  
  virtual void UpdateMenuItem(int command_id,
                              bool enabled,
                              bool hidden,
                              const base::string16& title) = 0;

  
  virtual content::RenderViewHost* GetRenderViewHost() const = 0;
  virtual content::WebContents* GetWebContents() const = 0;
  virtual content::BrowserContext* GetBrowserContext() const = 0;
};

#endif  

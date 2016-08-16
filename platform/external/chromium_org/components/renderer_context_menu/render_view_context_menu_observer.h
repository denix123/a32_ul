// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_OBSERVER_H_
#define COMPONENTS_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_OBSERVER_H_

namespace content {
struct ContextMenuParams;
}

class RenderViewContextMenuObserver {
 public:
  virtual ~RenderViewContextMenuObserver() {}

  
  
  
  virtual void InitMenu(const content::ContextMenuParams& params) {}

  
  
  
  virtual bool IsCommandIdSupported(int command_id);

  
  
  
  virtual bool IsCommandIdChecked(int command_id);
  virtual bool IsCommandIdEnabled(int command_id);

  
  virtual void ExecuteCommand(int command_id) {}

  
  virtual void OnMenuCancel() {}
};

#endif  

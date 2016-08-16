// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_MAC_H_
#define CHROME_BROWSER_UI_COCOA_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_MAC_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "chrome/browser/renderer_context_menu/render_view_context_menu.h"

@class MenuController;

class RenderViewContextMenuMac : public RenderViewContextMenu {
 public:
  RenderViewContextMenuMac(content::RenderFrameHost* render_frame_host,
                           const content::ContextMenuParams& params,
                           NSView* parent_view);
  virtual ~RenderViewContextMenuMac();

  
  virtual void ExecuteCommand(int command_id, int event_flags) OVERRIDE;
  virtual bool IsCommandIdChecked(int command_id) const OVERRIDE;
  virtual bool IsCommandIdEnabled(int command_id) const OVERRIDE;

  void Show();

 protected:
  
  virtual bool GetAcceleratorForCommandId(
      int command_id,
      ui::Accelerator* accelerator) OVERRIDE;
  virtual void AppendPlatformEditableItems() OVERRIDE;

 private:
  friend class ToolkitDelegateMac;

  
  void InitToolkitMenu();

  
  void CancelToolkitMenu();

  
  void UpdateToolkitMenuItem(int command_id,
                             bool enabled,
                             bool hidden,
                             const base::string16& title);

  
  void AppendBidiSubMenu();

  
  void LookUpInDictionary();

  
  void StartSpeaking();

  
  void StopSpeaking();

  
  base::scoped_nsobject<MenuController> menu_controller_;

  
  ui::SimpleMenuModel speech_submenu_model_;

  
  ui::SimpleMenuModel bidi_submenu_model_;

  
  NSView* parent_view_;

  DISALLOW_COPY_AND_ASSIGN(RenderViewContextMenuMac);
};

#endif  

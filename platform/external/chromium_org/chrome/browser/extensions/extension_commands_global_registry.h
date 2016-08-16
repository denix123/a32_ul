// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_COMMANDS_GLOBAL_REGISTRY_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_COMMANDS_GLOBAL_REGISTRY_H_

#include <map>
#include <string>

#include "base/compiler_specific.h"
#include "chrome/browser/extensions/extension_keybinding_registry.h"
#include "chrome/browser/extensions/global_shortcut_listener.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "ui/base/accelerators/accelerator.h"

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;

class ExtensionCommandsGlobalRegistry
    : public BrowserContextKeyedAPI,
      public ExtensionKeybindingRegistry,
      public GlobalShortcutListener::Observer {
 public:
  
  static BrowserContextKeyedAPIFactory<ExtensionCommandsGlobalRegistry>*
      GetFactoryInstance();

  
  
  static ExtensionCommandsGlobalRegistry* Get(content::BrowserContext* context);

  
  static void SetShortcutHandlingSuspended(bool suspended);

  explicit ExtensionCommandsGlobalRegistry(content::BrowserContext* context);
  virtual ~ExtensionCommandsGlobalRegistry();

  
  
  ExtensionKeybindingRegistry* registry_for_active_window() {
    return registry_for_active_window_;
  }

  void set_registry_for_active_window(ExtensionKeybindingRegistry* registry) {
    registry_for_active_window_ = registry;
  }

  
  
  bool IsRegistered(const ui::Accelerator& accelerator);

 private:
  friend class BrowserContextKeyedAPIFactory<ExtensionCommandsGlobalRegistry>;

  
  static const char* service_name() {
    return "ExtensionCommandsGlobalRegistry";
  }

  
  virtual void AddExtensionKeybinding(
      const Extension* extension,
      const std::string& command_name) OVERRIDE;
  virtual void RemoveExtensionKeybindingImpl(
      const ui::Accelerator& accelerator,
      const std::string& command_name) OVERRIDE;

  
  
  virtual void OnKeyPressed(const ui::Accelerator& accelerator) OVERRIDE;

  
  content::BrowserContext* browser_context_;

  
  
  
  
  
  ExtensionKeybindingRegistry* registry_for_active_window_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionCommandsGlobalRegistry);
};

}  

#endif  

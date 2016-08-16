// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_KEYBINDING_REGISTRY_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_KEYBINDING_REGISTRY_H_

#include <list>
#include <map>
#include <string>

#include "base/compiler_specific.h"
#include "base/scoped_observer.h"
#include "content/public/browser/notification_details.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/notification_source.h"
#include "extensions/browser/extension_registry_observer.h"

namespace content {
class BrowserContext;
}

namespace ui {
class Accelerator;
}

namespace extensions {

class ActiveTabPermissionGranter;
class Extension;
class ExtensionRegistry;

class ExtensionKeybindingRegistry : public content::NotificationObserver,
                                    public ExtensionRegistryObserver {
 public:
  enum ExtensionFilter {
    ALL_EXTENSIONS,
    PLATFORM_APPS_ONLY
  };

  class Delegate {
   public:
    
    
    virtual ActiveTabPermissionGranter* GetActiveTabPermissionGranter() = 0;
  };

  
  
  ExtensionKeybindingRegistry(content::BrowserContext* context,
                              ExtensionFilter extension_filter,
                              Delegate* delegate);

  virtual ~ExtensionKeybindingRegistry();

  
  
  static void SetShortcutHandlingSuspended(bool suspended);

  
  
  void ExecuteCommand(const std::string& extension_id,
                      const ui::Accelerator& accelerator);

  
  bool IsAcceleratorRegistered(const ui::Accelerator& accelerator) const;

 protected:
  
  
  
  virtual void AddExtensionKeybinding(
      const Extension* extension,
      const std::string& command_name) = 0;
  
  
  void RemoveExtensionKeybinding(
      const Extension* extension,
      const std::string& command_name);
  
  
  virtual void RemoveExtensionKeybindingImpl(
      const ui::Accelerator& accelerator,
      const std::string& command_name) = 0;

  
  void Init();

  
  
  bool ShouldIgnoreCommand(const std::string& command) const;

  
  
  bool NotifyEventTargets(const ui::Accelerator& accelerator);

  
  void CommandExecuted(const std::string& extension_id,
                       const std::string& command);

  
  
  
  void AddEventTarget(const ui::Accelerator& accelerator,
                      const std::string& extension_id,
                      const std::string& command_name);

  
  
  
  
  
  bool GetFirstTarget(const ui::Accelerator& accelerator,
                      std::string* extension_id,
                      std::string* command_name) const;

  
  bool IsEventTargetsEmpty() const;

  
  content::BrowserContext* browser_context() const { return browser_context_; }

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  bool ExtensionMatchesFilter(const extensions::Extension* extension);

  
  
  
  
  bool ExecuteCommands(const ui::Accelerator& accelerator,
                       const std::string& extension_id);

  
  content::NotificationRegistrar registrar_;

  content::BrowserContext* browser_context_;

  
  ExtensionFilter extension_filter_;

  
  Delegate* delegate_;

  
  
  
  
  
  
  
  typedef std::list<std::pair<std::string, std::string> > TargetList;
  typedef std::map<ui::Accelerator, TargetList> EventTargets;
  EventTargets event_targets_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionKeybindingRegistry);
};

}  

#endif  

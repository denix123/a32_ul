// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_COMMANDS_COMMAND_SERVICE_H_
#define CHROME_BROWSER_EXTENSIONS_API_COMMANDS_COMMAND_SERVICE_H_

#include <string>

#include "base/basictypes.h"
#include "base/scoped_observer.h"
#include "chrome/common/extensions/command.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/extension.h"

class Profile;

namespace base {
class DictionaryValue;
}

namespace content {
class BrowserContext;
}

namespace ui {
class Accelerator;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace extensions {
class ExtensionRegistry;

class CommandService : public BrowserContextKeyedAPI,
                       public ExtensionRegistryObserver {
 public:
  
  
  enum QueryType {
    ALL,
    ACTIVE_ONLY,
  };

  
  
  
  enum CommandScope {
    REGULAR,    
    GLOBAL,     
    ANY_SCOPE,  
  };

  
  enum ExtensionCommandType {
    NAMED,
    BROWSER_ACTION,
    PAGE_ACTION
  };

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  explicit CommandService(content::BrowserContext* context);
  virtual ~CommandService();

  
  static BrowserContextKeyedAPIFactory<CommandService>* GetFactoryInstance();

  
  static CommandService* Get(content::BrowserContext* context);

  
  
  static bool RemovesBookmarkShortcut(const Extension* extension);

  
  
  static bool RemovesBookmarkOpenPagesShortcut(const Extension* extension);

  
  
  
  
  
  
  bool GetBrowserActionCommand(const std::string& extension_id,
                               QueryType type,
                               Command* command,
                               bool* active) const;

  
  
  
  
  
  
  bool GetPageActionCommand(const std::string& extension_id,
                            QueryType type,
                            Command* command,
                            bool* active) const;

  
  
  
  
  
  bool GetNamedCommands(const std::string& extension_id,
                        QueryType type,
                        CommandScope scope,
                        CommandMap* command_map) const;

  
  
  
  
  
  // |accelerator| will be overwritten. If |global| is true, the command will
  
  
  bool AddKeybindingPref(const ui::Accelerator& accelerator,
                         std::string extension_id,
                         std::string command_name,
                         bool allow_overrides,
                         bool global);

  
  
  
  void RemoveKeybindingPrefs(const std::string& extension_id,
                             const std::string& command_name);

  
  
  
  void UpdateKeybindingPrefs(const std::string& extension_id,
                             const std::string& command_name,
                             const std::string& keystroke);

  
  
  
  bool SetScope(const std::string& extension_id,
                const std::string& command_name,
                bool global);

  
  
  
  Command FindCommandByName(const std::string& extension_id,
                            const std::string& command) const;

  
  
  
  bool GetBoundExtensionCommand(const std::string& extension_id,
                                const ui::Accelerator& accelerator,
                                Command* command,
                                ExtensionCommandType* command_type) const;

  
  
  bool OverridesBookmarkShortcut(const Extension* extension) const;

 private:
  friend class BrowserContextKeyedAPIFactory<CommandService>;

  
  static const char* service_name() {
    return "CommandService";
  }
  static const bool kServiceRedirectedInIncognito = true;

  
  virtual void OnExtensionWillBeInstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      bool is_update,
      bool from_ephemeral,
      const std::string& old_name) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  
  
  
  
  void UpdateKeybindings(const Extension* extension);

  
  
  void RemoveRelinquishedKeybindings(const Extension* extension);

  
  
  void AssignKeybindings(const Extension* extension);

  
  
  bool CanAutoAssign(const Command &command,
                     const Extension* extension);

  
  
  void UpdateExtensionSuggestedCommandPrefs(const Extension* extension);

  
  
  void RemoveDefunctExtensionSuggestedCommandPrefs(const Extension* extension);

  
  
  bool IsCommandShortcutUserModified(const Extension* extension,
                                     const std::string& command_name);

  
  
  bool IsKeybindingChanging(const Extension* extension,
                            const std::string& command_name);

  
  
  std::string GetSuggestedKeyPref(const Extension* extension,
                                  const std::string& command_name);

  bool GetExtensionActionCommand(const std::string& extension_id,
                                 QueryType query_type,
                                 Command* command,
                                 bool* active,
                                 ExtensionCommandType action_type) const;

  
  Profile* profile_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(CommandService);
};

template <>
void
    BrowserContextKeyedAPIFactory<CommandService>::DeclareFactoryDependencies();

}  

#endif  

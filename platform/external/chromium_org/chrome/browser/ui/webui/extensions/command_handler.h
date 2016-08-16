// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_EXTENSIONS_COMMAND_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_EXTENSIONS_COMMAND_HANDLER_H_

#include "base/compiler_specific.h"
#include "base/scoped_observer.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "extensions/browser/extension_registry_observer.h"

class Profile;

namespace base {
class DictionaryValue;
class ListValue;
}

namespace content {
class WebUIDataSource;
}

namespace extensions {
class Command;
class CommandService;
class Extension;
class ExtensionRegistry;

class CommandHandler : public content::WebUIMessageHandler,
                       public ExtensionRegistryObserver {
 public:
  explicit CommandHandler(Profile* profile);
  virtual ~CommandHandler();

  
  void GetLocalizedValues(content::WebUIDataSource* source);

  
  virtual void RegisterMessages() OVERRIDE;

 private:
  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

   
  void UpdateCommandDataOnPage();

  
  
  
  void HandleRequestExtensionsData(const base::ListValue* args);

  
  
  void HandleSetExtensionCommandShortcut(const base::ListValue* args);

  
  
  void HandleSetCommandScope(const base::ListValue* args);

  
  
  void HandleSetShortcutHandlingSuspended(const base::ListValue* args);

  
  
  void GetAllCommands(base::DictionaryValue* commands);

  Profile* profile_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(CommandHandler);
};

}  

#endif  

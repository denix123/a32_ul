// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSIONS_BROWSER_CLIENT_H_
#define EXTENSIONS_BROWSER_EXTENSIONS_BROWSER_CLIENT_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "extensions/browser/extension_prefs_observer.h"

class ExtensionFunctionRegistry;
class PrefService;

namespace base {
class CommandLine;
class FilePath;
class ListValue;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace net {
class NetLog;
class NetworkDelegate;
class URLRequest;
class URLRequestJob;
}

namespace extensions {

class ApiActivityMonitor;
class AppSorting;
class ComponentExtensionResourceManager;
class Extension;
class ExtensionHostDelegate;
class ExtensionPrefsObserver;
class ExtensionSystem;
class ExtensionSystemProvider;
class InfoMap;
class ProcessManagerDelegate;
class RuntimeAPIDelegate;

class ExtensionsBrowserClient {
 public:
  virtual ~ExtensionsBrowserClient() {}

  
  virtual bool IsShuttingDown() = 0;

  
  
  virtual bool AreExtensionsDisabled(const base::CommandLine& command_line,
                                     content::BrowserContext* context) = 0;

  
  virtual bool IsValidContext(content::BrowserContext* context) = 0;

  
  
  virtual bool IsSameContext(content::BrowserContext* first,
                             content::BrowserContext* second) = 0;

  
  virtual bool HasOffTheRecordContext(content::BrowserContext* context) = 0;

  
  
  
  
  virtual content::BrowserContext* GetOffTheRecordContext(
      content::BrowserContext* context) = 0;

  
  
  virtual content::BrowserContext* GetOriginalContext(
      content::BrowserContext* context) = 0;

  
  virtual bool IsGuestSession(content::BrowserContext* context) const = 0;

  
  virtual bool IsExtensionIncognitoEnabled(
      const std::string& extension_id,
      content::BrowserContext* context) const = 0;

  
  
  virtual bool CanExtensionCrossIncognito(
      const extensions::Extension* extension,
      content::BrowserContext* context) const = 0;

  
  
  
  
  virtual net::URLRequestJob* MaybeCreateResourceBundleRequestJob(
      net::URLRequest* request,
      net::NetworkDelegate* network_delegate,
      const base::FilePath& directory_path,
      const std::string& content_security_policy,
      bool send_cors_header) = 0;

  
  
  
  
  virtual bool AllowCrossRendererResourceLoad(net::URLRequest* request,
                                              bool is_incognito,
                                              const Extension* extension,
                                              InfoMap* extension_info_map) = 0;

  
  virtual PrefService* GetPrefServiceForContext(
      content::BrowserContext* context) = 0;

  
  
  
  virtual void GetEarlyExtensionPrefsObservers(
      content::BrowserContext* context,
      std::vector<ExtensionPrefsObserver*>* observers) const = 0;

  
  
  virtual ProcessManagerDelegate* GetProcessManagerDelegate() const = 0;

  
  virtual scoped_ptr<ExtensionHostDelegate> CreateExtensionHostDelegate() = 0;

  
  
  
  
  virtual bool DidVersionUpdate(content::BrowserContext* context) = 0;

  
  
  virtual void PermitExternalProtocolHandler() = 0;

  
  virtual scoped_ptr<AppSorting> CreateAppSorting() = 0;

  
  virtual bool IsRunningInForcedAppMode() = 0;

  
  
  virtual ApiActivityMonitor* GetApiActivityMonitor(
      content::BrowserContext* context) = 0;

  
  
  virtual ExtensionSystemProvider* GetExtensionSystemFactory() = 0;

  
  virtual void RegisterExtensionFunctions(
      ExtensionFunctionRegistry* registry) const = 0;

  
  
  
  virtual scoped_ptr<RuntimeAPIDelegate> CreateRuntimeAPIDelegate(
      content::BrowserContext* context) const = 0;

  
  
  virtual ComponentExtensionResourceManager*
  GetComponentExtensionResourceManager() = 0;

  
  
  virtual void BroadcastEventToRenderers(const std::string& event_name,
                                         scoped_ptr<base::ListValue> args) = 0;

  
  virtual net::NetLog* GetNetLog() = 0;

  
  static ExtensionsBrowserClient* Get();

  
  static void Set(ExtensionsBrowserClient* client);
};

}  

#endif  

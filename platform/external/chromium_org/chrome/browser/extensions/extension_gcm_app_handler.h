// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_GCM_APP_HANDLER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_GCM_APP_HANDLER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "components/gcm_driver/gcm_app_handler.h"
#include "components/gcm_driver/gcm_client.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"

class Profile;

namespace content {
class BrowserContext;
}

namespace gcm {
class GCMDriver;
class GCMProfileService;
}

namespace extensions {

class ExtensionRegistry;
class GcmJsEventRouter;

class ExtensionGCMAppHandler : public gcm::GCMAppHandler,
                               public BrowserContextKeyedAPI,
                               public ExtensionRegistryObserver {
 public:
  explicit ExtensionGCMAppHandler(content::BrowserContext* context);
  virtual ~ExtensionGCMAppHandler();

  
  static BrowserContextKeyedAPIFactory<ExtensionGCMAppHandler>*
  GetFactoryInstance();

  
  virtual void ShutdownHandler() OVERRIDE;
  virtual void OnMessage(
      const std::string& app_id,
      const gcm::GCMClient::IncomingMessage& message) OVERRIDE;
  virtual void OnMessagesDeleted(const std::string& app_id) OVERRIDE;
  virtual void OnSendError(
      const std::string& app_id,
      const gcm::GCMClient::SendErrorDetails& send_error_details) OVERRIDE;
  virtual void OnSendAcknowledged(const std::string& app_id,
                                  const std::string& message_id) OVERRIDE;

 protected:
  
  virtual void OnUnregisterCompleted(const std::string& app_id,
                                     gcm::GCMClient::Result result);
  virtual void AddAppHandler(const std::string& app_id);
  virtual void RemoveAppHandler(const std::string& app_id);

  gcm::GCMDriver* GetGCMDriver() const;

private:
  friend class BrowserContextKeyedAPIFactory<ExtensionGCMAppHandler>;

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  void AddDummyAppHandler();
  void RemoveDummyAppHandler();

  
  static const char* service_name() { return "ExtensionGCMAppHandler"; }
  static const bool kServiceIsNULLWhileTesting = true;

  Profile* profile_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  scoped_ptr<extensions::GcmJsEventRouter> js_event_router_;

  base::WeakPtrFactory<ExtensionGCMAppHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionGCMAppHandler);
};

}  

#endif  

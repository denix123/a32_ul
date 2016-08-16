// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_COPRESENCE_COPRESENCE_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_COPRESENCE_COPRESENCE_API_H_

#include <map>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/extensions/api/copresence/copresence_translations.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/common/extensions/api/copresence.h"
#include "components/copresence/public/copresence_delegate.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"

namespace copresence {
class CopresenceManager;
class WhispernetClient;
}

namespace extensions {

class CopresenceService : public BrowserContextKeyedAPI,
                          public copresence::CopresenceDelegate {
 public:
  explicit CopresenceService(content::BrowserContext* context);
  virtual ~CopresenceService();

  
  virtual void Shutdown() OVERRIDE;

  
  
  copresence::CopresenceManager* manager();
  copresence::WhispernetClient* whispernet_client();

  
  SubscriptionToAppMap& apps_by_subscription_id() {
    return apps_by_subscription_id_;
  }

  void set_api_key(const std::string& api_key) { api_key_ = api_key; }

  
  void set_manager_for_testing(
      scoped_ptr<copresence::CopresenceManager> manager);

  
  static BrowserContextKeyedAPIFactory<CopresenceService>* GetFactoryInstance();

 private:
  friend class BrowserContextKeyedAPIFactory<CopresenceService>;

  
  virtual void HandleMessages(
      const std::string& app_id,
      const std::string& subscription_id,
      const std::vector<copresence::Message>& message) OVERRIDE;
  virtual net::URLRequestContextGetter* GetRequestContext() const OVERRIDE;
  virtual const std::string GetPlatformVersionString() const OVERRIDE;
  virtual const std::string GetAPIKey() const OVERRIDE;
  virtual copresence::WhispernetClient* GetWhispernetClient() OVERRIDE;

  
  static const char* service_name() { return "CopresenceService"; }

  bool is_shutting_down_;
  std::map<std::string, std::string> apps_by_subscription_id_;

  content::BrowserContext* const browser_context_;
  std::string api_key_;

  scoped_ptr<copresence::CopresenceManager> manager_;
  scoped_ptr<copresence::WhispernetClient> whispernet_client_;

  DISALLOW_COPY_AND_ASSIGN(CopresenceService);
};

template <>
void BrowserContextKeyedAPIFactory<
    CopresenceService>::DeclareFactoryDependencies();

class CopresenceExecuteFunction : public ChromeUIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("copresence.execute", COPRESENCE_EXECUTE);

 protected:
  virtual ~CopresenceExecuteFunction() {}
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;

 private:
  void SendResult(copresence::CopresenceStatus status);
};

class CopresenceSetApiKeyFunction : public ChromeUIThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("copresence.setApiKey", COPRESENCE_SETAPIKEY);

 protected:
  virtual ~CopresenceSetApiKeyFunction() {}
  virtual ExtensionFunction::ResponseAction Run() OVERRIDE;
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_EXTENSIONS_API_CLIENT_H_
#define EXTENSIONS_BROWSER_API_EXTENSIONS_API_CLIENT_H_

#include <map>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/browser/api/declarative_content/content_rules_registry.h"
#include "extensions/browser/api/storage/settings_namespace.h"

class GURL;

template <class T>
class ObserverListThreadSafe;

namespace content {
class BrowserContext;
}

namespace extensions {

class AppViewGuestDelegate;
class ContentRulesRegistry;
class ExtensionOptionsGuest;
class ExtensionOptionsGuestDelegate;
class MimeHandlerViewGuest;
class MimeHandlerViewGuestDelegate;
class WebViewGuest;
class WebViewGuestDelegate;
class WebViewPermissionHelper;
class WebViewPermissionHelperDelegate;
class WebRequestEventRouterDelegate;
class RulesCacheDelegate;
class SettingsObserver;
class SettingsStorageFactory;
class ValueStoreCache;

class ExtensionsAPIClient {
 public:
  
  ExtensionsAPIClient();

  
  virtual ~ExtensionsAPIClient();

  
  static ExtensionsAPIClient* Get();

  

  
  
  virtual void AddAdditionalValueStoreCaches(
      content::BrowserContext* context,
      const scoped_refptr<SettingsStorageFactory>& factory,
      const scoped_refptr<ObserverListThreadSafe<SettingsObserver> >& observers,
      std::map<settings_namespace::Namespace, ValueStoreCache*>* caches);

  
  virtual AppViewGuestDelegate* CreateAppViewGuestDelegate() const;

  
  
  virtual ExtensionOptionsGuestDelegate* CreateExtensionOptionsGuestDelegate(
      ExtensionOptionsGuest* guest) const;

  
  virtual scoped_ptr<MimeHandlerViewGuestDelegate>
      CreateMimeHandlerViewGuestDelegate(MimeHandlerViewGuest* guest) const;

  
  
  virtual WebViewGuestDelegate* CreateWebViewGuestDelegate (
      WebViewGuest* web_view_guest) const;

  
  
  virtual WebViewPermissionHelperDelegate*
      CreateWebViewPermissionHelperDelegate (
          WebViewPermissionHelper* web_view_permission_helper) const;

  
  
  virtual scoped_refptr<RulesRegistry> GetRulesRegistry(
      content::BrowserContext* browser_context,
      const RulesRegistry::WebViewKey& webview_key,
      const std::string& event_name);

  
  virtual WebRequestEventRouterDelegate* CreateWebRequestEventRouterDelegate()
      const;

  
  
  virtual scoped_refptr<ContentRulesRegistry> CreateContentRulesRegistry(
      content::BrowserContext* browser_context,
      RulesCacheDelegate* cache_delegate) const;

  
  
};

}  

#endif  

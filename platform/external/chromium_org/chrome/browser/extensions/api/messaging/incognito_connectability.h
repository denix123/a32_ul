// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_MESSAGING_INCOGNITO_CONNECTABILITY_H_
#define CHROME_BROWSER_EXTENSIONS_API_MESSAGING_INCOGNITO_CONNECTABILITY_H_

#include <set>

#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "url/gurl.h"

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {
class Extension;

class IncognitoConnectability : public BrowserContextKeyedAPI {
 public:
  
  
  class ScopedAlertTracker {
   public:
    enum Mode {
      INTERACTIVE,
      ALWAYS_ALLOW,
      ALWAYS_DENY,
    };

    explicit ScopedAlertTracker(Mode mode);

    ~ScopedAlertTracker();

    
    
    int GetAndResetAlertCount();

   private:
    int last_checked_invocation_count_;
  };

  
  
  static IncognitoConnectability* Get(content::BrowserContext* context);

  
  
  bool Query(const Extension* extension,
             content::WebContents* web_contents,
             const GURL& url);

 private:
  friend class BrowserContextKeyedAPIFactory<IncognitoConnectability>;

  explicit IncognitoConnectability(content::BrowserContext* context);
  virtual ~IncognitoConnectability();

  typedef std::map<std::string, std::set<GURL> > ExtensionToOriginsMap;

  
  bool IsInMap(const Extension* extension,
               const GURL& origin,
               const ExtensionToOriginsMap& map);

  
  static BrowserContextKeyedAPIFactory<IncognitoConnectability>*
      GetFactoryInstance();
  static const char* service_name() {
    return "Messaging.IncognitoConnectability";
  }
  static const bool kServiceHasOwnInstanceInIncognito = true;
  static const bool kServiceIsCreatedWithBrowserContext = false;

  
  
  
  ExtensionToOriginsMap allowed_origins_;
  ExtensionToOriginsMap disallowed_origins_;
};

}  

#endif  

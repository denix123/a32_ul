// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_SIGNIN_GAIA_AUTH_EXTENSION_LOADER_H_
#define CHROME_BROWSER_EXTENSIONS_SIGNIN_GAIA_AUTH_EXTENSION_LOADER_H_

#include "base/memory/scoped_ptr.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"

namespace content {
class BrowserContext;
}

namespace extensions {

const char kGaiaAuthExtensionId[] = "mfffpogegjflfpflabcdkioaeobkgjik";
const char kGaiaAuthExtensionOrigin[] =
      "chrome-extension://mfffpogegjflfpflabcdkioaeobkgjik";

class GaiaAuthExtensionLoader : public BrowserContextKeyedAPI {
 public:
  explicit GaiaAuthExtensionLoader(content::BrowserContext* context);
  virtual ~GaiaAuthExtensionLoader();

  
  void LoadIfNeeded();
  
  void UnloadIfNeeded();

  static GaiaAuthExtensionLoader* Get(content::BrowserContext* context);

  
  static BrowserContextKeyedAPIFactory<GaiaAuthExtensionLoader>*
      GetFactoryInstance();

 private:
  friend class BrowserContextKeyedAPIFactory<GaiaAuthExtensionLoader>;

  
  virtual void Shutdown() OVERRIDE;

  
  static const char* service_name() {
    return "GaiaAuthExtensionLoader";
  }
  static const bool kServiceRedirectedInIncognito = true;

  content::BrowserContext* browser_context_;
  int load_count_;

  DISALLOW_COPY_AND_ASSIGN(GaiaAuthExtensionLoader);
};

} 

#endif  

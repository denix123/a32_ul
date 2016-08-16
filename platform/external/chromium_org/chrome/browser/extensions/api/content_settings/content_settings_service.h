// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_CONTENT_SETTINGS_CONTENT_SETTINGS_SERVICE_H_
#define CHROME_BROWSER_EXTENSIONS_API_CONTENT_SETTINGS_CONTENT_SETTINGS_SERVICE_H_

#include "base/memory/ref_counted.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_prefs_observer.h"

namespace extensions {

class ContentSettingsStore;
class ExtensionPrefs;

class ContentSettingsService : public BrowserContextKeyedAPI,
                               public ExtensionPrefsObserver {
 public:
  explicit ContentSettingsService(content::BrowserContext* context);
  virtual ~ContentSettingsService();

  scoped_refptr<ContentSettingsStore> content_settings_store() const {
    return content_settings_store_;
  }

  
  static ContentSettingsService* Get(content::BrowserContext* context);

  
  static BrowserContextKeyedAPIFactory<ContentSettingsService>*
      GetFactoryInstance();

  
  virtual void OnExtensionRegistered(const std::string& extension_id,
                                     const base::Time& install_time,
                                     bool is_enabled) OVERRIDE;
  virtual void OnExtensionPrefsLoaded(const std::string& extension_id,
                                      const ExtensionPrefs* prefs) OVERRIDE;
  virtual void OnExtensionPrefsDeleted(const std::string& extension_id)
      OVERRIDE;
  virtual void OnExtensionStateChanged(const std::string& extension_id,
                                       bool state) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<ContentSettingsService>;

  
  static const char* service_name() { return "ContentSettingsService"; }

  scoped_refptr<ContentSettingsStore> content_settings_store_;

  DISALLOW_COPY_AND_ASSIGN(ContentSettingsService);
};

}  

#endif  

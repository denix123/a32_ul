// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_MANAGEMENT_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_MANAGEMENT_H_

#include <map>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/values.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/management_policy.h"
#include "extensions/common/extension.h"
#include "extensions/common/manifest.h"
#include "extensions/common/url_pattern_set.h"

class GURL;
class PrefService;

namespace content {
class BrowserContext;
}  

namespace extensions {

class ExtensionManagement : public KeyedService {
 public:
  
  class Observer {
   public:
    virtual ~Observer() {}

    
    virtual void OnExtensionManagementSettingsChanged() = 0;
  };

  
  
  
  
  
  
  
  enum InstallationMode {
    INSTALLATION_ALLOWED = 0,
    INSTALLATION_BLOCKED,
    INSTALLATION_FORCED,
    INSTALLATION_RECOMMENDED,
  };

  
  
  
  
  struct IndividualSettings {
    IndividualSettings();
    ~IndividualSettings();

    void Reset();

    
    
    
    
    
    
    
    
    InstallationMode installation_mode;
    std::string update_url;
  };

  
  struct GlobalSettings {
    GlobalSettings();
    ~GlobalSettings();

    void Reset();

    
    
    URLPatternSet install_sources;
    bool has_restricted_install_sources;

    
    
    std::vector<Manifest::Type> allowed_types;
    bool has_restricted_allowed_types;
  };

  typedef std::map<ExtensionId, IndividualSettings> SettingsIdMap;

  explicit ExtensionManagement(PrefService* pref_service);
  virtual ~ExtensionManagement();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  ManagementPolicy::Provider* GetProvider();

  
  
  
  bool BlacklistedByDefault();

  
  
  scoped_ptr<base::DictionaryValue> GetForceInstallList() const;

  
  
  bool IsInstallationExplicitlyAllowed(const ExtensionId& id) const;

  
  bool IsOffstoreInstallAllowed(const GURL& url, const GURL& referrer_url);

  
  
  const IndividualSettings& ReadById(const ExtensionId& id) const;

  
  const GlobalSettings& ReadGlobalSettings() const;

 private:
  
  
  void Refresh();

  
  
  
  
  const base::Value* LoadPreference(const char* pref_name,
                                    bool force_managed,
                                    base::Value::Type expected_type);

  void OnExtensionPrefChanged();
  void NotifyExtensionManagementPrefChanged();

  
  
  
  IndividualSettings* AccessById(const ExtensionId& id);

  
  
  
  
  
  SettingsIdMap settings_by_id_;

  
  
  
  
  
  
  IndividualSettings default_settings_;

  
  GlobalSettings global_settings_;

  PrefService* pref_service_;

  ObserverList<Observer, true> observer_list_;
  PrefChangeRegistrar pref_change_registrar_;
  scoped_ptr<ManagementPolicy::Provider> provider_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionManagement);
};

class ExtensionManagementFactory : public BrowserContextKeyedServiceFactory {
 public:
  static ExtensionManagement* GetForBrowserContext(
      content::BrowserContext* context);
  static ExtensionManagementFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<ExtensionManagementFactory>;

  ExtensionManagementFactory();
  virtual ~ExtensionManagementFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const OVERRIDE;
  virtual void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(ExtensionManagementFactory);
};

}  

#endif  

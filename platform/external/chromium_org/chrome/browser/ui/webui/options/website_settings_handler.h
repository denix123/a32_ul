// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_WEBSITE_SETTINGS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_WEBSITE_SETTINGS_HANDLER_H_

#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/scoped_observer.h"
#include "chrome/browser/browsing_data/browsing_data_local_storage_helper.h"
#include "chrome/browser/content_settings/host_content_settings_map.h"
#include "chrome/browser/content_settings/local_shared_objects_container.h"
#include "chrome/browser/ui/webui/options/options_ui.h"
#include "components/content_settings/core/browser/content_settings_observer.h"
#include "components/power/origin_power_map.h"

namespace options {

class WebsiteSettingsHandler : public content_settings::Observer,
                               public OptionsPageUIHandler {
 public:
  WebsiteSettingsHandler();
  virtual ~WebsiteSettingsHandler();

  typedef std::list<BrowsingDataLocalStorageHelper::LocalStorageInfo>
      LocalStorageList;

  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;
  virtual void InitializeHandler() OVERRIDE;
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void OnContentSettingChanged(
      const ContentSettingsPattern& primary_pattern,
      const ContentSettingsPattern& secondary_pattern,
      ContentSettingsType content_type,
      std::string resource_identifier) OVERRIDE;
  virtual void OnContentSettingUsed(
      const ContentSettingsPattern& primary_pattern,
      const ContentSettingsPattern& secondary_pattern,
      ContentSettingsType content_type) OVERRIDE;

 private:
  
  
  void HandleUpdateOrigins(const base::ListValue* args);

  
  
  void HandleUpdateSearchResults(const base::ListValue* args);

  
  
  
  void HandleGetOriginInfo(const base::ListValue* args);

  
  
  
  void HandleSetOriginPermission(const base::ListValue* args);

  
  void HandleUpdateLocalStorage(const base::ListValue* args);

  
  
  void HandleMaybeShowEditPage(const base::ListValue* args);

  
  
  void HandleUpdateBatteryUsage(const base::ListValue* args);

  
  void HandleDeleteLocalStorage(const base::ListValue* args);

  
  void HandleUpdateDefaultSetting(const base::ListValue* args);

  
  void HandleSetDefaultSetting(const base::ListValue* args);

  
  void HandleSetGlobalToggle(const base::ListValue* args);

  
  
  void HandleStopOrigin(const base::ListValue* args);

  
  void OnLocalStorageFetched(const LocalStorageList& storage);

  
  
  void UpdateOrigins();

  
  
  void UpdateLocalStorage();

  
  
  void UpdateBatteryUsage();

  
  void StopOrigin(const GURL& site_url);

  
  void DeleteLocalStorage(const GURL& site_url);

  
  
  
  void GetInfoForOrigin(const GURL& site_url, bool show_page);

  
  void Update();

  
  
  std::string GetSettingDefaultFromModel(ContentSettingsType type,
                                         std::string* provider_id);

  
  const std::string& GetReadableName(const GURL& site_url);

  Profile* GetProfile();

  std::string last_setting_;
  std::string last_filter_;
  GURL last_site_;
  scoped_refptr<BrowsingDataLocalStorageHelper> local_storage_;
  LocalStorageList local_storage_list_;

  
  ScopedObserver<HostContentSettingsMap, content_settings::Observer> observer_;

  
  scoped_ptr<power::OriginPowerMap::Subscription> subscription_;

  base::WeakPtrFactory<WebsiteSettingsHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebsiteSettingsHandler);
};

}  

#endif  

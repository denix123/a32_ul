// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CONTENT_SETTINGS_CONTENT_SETTINGS_OVERRIDE_PROVIDER_H_
#define CHROME_BROWSER_CONTENT_SETTINGS_CONTENT_SETTINGS_OVERRIDE_PROVIDER_H_

#include "base/macros.h"
#include "base/synchronization/lock.h"
#include "components/content_settings/core/browser/content_settings_provider.h"
#include "components/content_settings/core/common/content_settings_types.h"

class ContentSettingsPattern;
class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace content_settings {

// globally disabled. It may only be written to using the UI thread, but may be
class OverrideProvider : public ProviderInterface {
 public:
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  OverrideProvider(PrefService* prefs, bool incognito);
  virtual ~OverrideProvider();

  
  virtual RuleIterator* GetRuleIterator(
      ContentSettingsType content_type,
      const ResourceIdentifier& resource_identifier,
      bool incognito) const OVERRIDE;

  virtual void ClearAllContentSettingsRules(
      ContentSettingsType content_type) OVERRIDE;

  virtual bool SetWebsiteSetting(
      const ContentSettingsPattern& primary_pattern,
      const ContentSettingsPattern& secondary_pattern,
      ContentSettingsType content_type,
      const ResourceIdentifier& resource_identifier,
      base::Value* value) OVERRIDE;

  virtual void ShutdownOnUIThread() OVERRIDE;

  
  void SetOverrideSetting(ContentSettingsType content_type, bool enabled);

  
  
  
  
  bool IsEnabled(ContentSettingsType content_type) const;

 private:
  
  void ReadOverrideSettings();

  
  bool allowed_settings_[CONTENT_SETTINGS_NUM_TYPES];

  PrefService* prefs_;

  bool is_incognito_;

  
  
  mutable base::Lock lock_;

  DISALLOW_COPY_AND_ASSIGN(OverrideProvider);
};

}  

#endif  

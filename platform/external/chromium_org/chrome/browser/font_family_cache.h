// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_FONT_FAMILY_CACHE_H_
#define CHROME_BROWSER_FONT_FAMILY_CACHE_H_

#include "base/containers/hash_tables.h"
#include "base/gtest_prod_util.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/strings/string16.h"
#include "base/supports_user_data.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/common/web_preferences.h"

class PrefService;
class Profile;

FORWARD_DECLARE_TEST(FontFamilyCacheTest, Caching);

class FontFamilyCache : public base::SupportsUserData::Data,
                        public content::NotificationObserver {
 public:
  explicit FontFamilyCache(Profile* profile);
  virtual ~FontFamilyCache();

  
  static void FillFontFamilyMap(Profile* profile,
                                const char* map_name,
                                content::ScriptFontFamilyMap* map);

  
  void FillFontFamilyMap(const char* map_name,
                         content::ScriptFontFamilyMap* map);

 protected:
  
  
  virtual base::string16 FetchFont(const char* script, const char* map_name);

 private:
  FRIEND_TEST_ALL_PREFIXES(::FontFamilyCacheTest, Caching);

  
  
  typedef base::hash_map<const char*, base::string16> ScriptFontMap;

  
  
  typedef base::hash_map<const char*, ScriptFontMap> FontFamilyMap;

  
  
  
  
  
  
  
  
  
  base::string16 FetchAndCacheFont(const char* script, const char* map_name);

  
  
  
  void OnPrefsChanged(const std::string& pref_name);

  
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  FontFamilyMap font_family_map_;

  
  
  
  const PrefService* prefs_;

  
  PrefChangeRegistrar profile_pref_registrar_;

  
  content::NotificationRegistrar notification_registrar_;

  DISALLOW_COPY_AND_ASSIGN(FontFamilyCache);
};

#endif  

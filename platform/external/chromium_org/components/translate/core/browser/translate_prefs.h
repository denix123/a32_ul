// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_PREFS_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_PREFS_H_

#include <string>
#include <vector>

#include "base/gtest_prod_util.h"
#include "url/gurl.h"

class PrefService;
class Profile;

namespace base {
class DictionaryValue;
class ListValue;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace translate {

class TranslateAcceptLanguages;

class TranslatePrefs {
 public:
  static const char kPrefTranslateLanguageBlacklist[];
  static const char kPrefTranslateSiteBlacklist[];
  static const char kPrefTranslateWhitelists[];
  static const char kPrefTranslateDeniedCount[];
  static const char kPrefTranslateAcceptedCount[];
  static const char kPrefTranslateBlockedLanguages[];
  static const char kPrefTranslateLastDeniedTime[];
  static const char kPrefTranslateTooOftenDenied[];

  
  
  TranslatePrefs(PrefService* user_prefs,
                 const char* accept_languages_pref,
                 const char* preferred_languages_pref);

  
  
  void ResetToDefaults();

  bool IsBlockedLanguage(const std::string& original_language) const;
  void BlockLanguage(const std::string& original_language);
  void UnblockLanguage(const std::string& original_language);

  
  
  void RemoveLanguageFromLegacyBlacklist(const std::string& original_language);

  bool IsSiteBlacklisted(const std::string& site) const;
  void BlacklistSite(const std::string& site);
  void RemoveSiteFromBlacklist(const std::string& site);

  bool HasWhitelistedLanguagePairs() const;

  bool IsLanguagePairWhitelisted(const std::string& original_language,
                                 const std::string& target_language);
  void WhitelistLanguagePair(const std::string& original_language,
                             const std::string& target_language);
  void RemoveLanguagePairFromWhitelist(const std::string& original_language,
                                       const std::string& target_language);

  
  bool HasBlockedLanguages() const;

  
  bool HasBlacklistedSites() const;

  
  
  
  int GetTranslationDeniedCount(const std::string& language) const;
  void IncrementTranslationDeniedCount(const std::string& language);
  void ResetTranslationDeniedCount(const std::string& language);

  
  
  
  int GetTranslationAcceptedCount(const std::string& language);
  void IncrementTranslationAcceptedCount(const std::string& language);
  void ResetTranslationAcceptedCount(const std::string& language);

  
  void UpdateLastDeniedTime();

  
  bool IsTooOftenDenied() const;

  
  void ResetDenialState();

  
  void GetLanguageList(std::vector<std::string>* languages);

  
  void UpdateLanguageList(const std::vector<std::string>& languages);

  bool CanTranslateLanguage(TranslateAcceptLanguages* accept_languages,
                            const std::string& language);
  bool ShouldAutoTranslate(const std::string& original_language,
                           std::string* target_language);
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);
  static void MigrateUserPrefs(PrefService* user_prefs,
                               const char* accept_languages_pref);

  
  
  
  
  static std::string ConvertLangCodeForTranslation(const std::string& lang);

 private:
  friend class TranslatePrefsTest;
  FRIEND_TEST_ALL_PREFIXES(TranslatePrefsTest, CreateBlockedLanguages);
  FRIEND_TEST_ALL_PREFIXES(TranslatePrefsTest,
                           CreateBlockedLanguagesNonEnglishUI);

  
  static void CreateBlockedLanguages(
      std::vector<std::string>* blocked_languages,
      const std::vector<std::string>& blacklisted_languages,
      const std::vector<std::string>& accept_languages);

  void ClearBlockedLanguages();
  void ClearBlacklistedSites();
  void ClearWhitelistedLanguagePairs();
  bool IsValueBlacklisted(const char* pref_id, const std::string& value) const;
  void BlacklistValue(const char* pref_id, const std::string& value);
  void RemoveValueFromBlacklist(const char* pref_id, const std::string& value);
  bool IsValueInList(const base::ListValue* list,
                     const std::string& value) const;
  bool IsListEmpty(const char* pref_id) const;
  bool IsDictionaryEmpty(const char* pref_id) const;

  
  const std::string accept_languages_pref_;
#if defined(OS_CHROMEOS)
  
  
  std::string preferred_languages_pref_;
#endif

  
  
  base::DictionaryValue* GetTranslationDeniedCountDictionary();

  
  
  base::DictionaryValue* GetTranslationAcceptedCountDictionary() const;

  PrefService* prefs_;  

  DISALLOW_COPY_AND_ASSIGN(TranslatePrefs);
};

}  

#endif  

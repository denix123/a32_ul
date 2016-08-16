// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_PREFS_H_
#define EXTENSIONS_BROWSER_EXTENSION_PREFS_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/scoped_user_pref_update.h"
#include "base/time/time.h"
#include "base/values.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/app_sorting.h"
#include "extensions/browser/blacklist_state.h"
#include "extensions/browser/extension_scoped_prefs.h"
#include "extensions/browser/install_flag.h"
#include "extensions/common/constants.h"
#include "extensions/common/extension.h"
#include "extensions/common/url_pattern_set.h"
#include "sync/api/string_ordinal.h"

class ExtensionPrefValueMap;
class PrefService;

namespace content {
class BrowserContext;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace extensions {

class AppSorting;
class ExtensionPrefsObserver;
class ExtensionPrefsUninstallExtension;
class URLPatternSet;

class ExtensionPrefs : public ExtensionScopedPrefs, public KeyedService {
 public:
  typedef std::vector<linked_ptr<ExtensionInfo> > ExtensionsInfo;

  
  typedef std::set<std::string> PrefKeySet;

  
  
  
  enum DelayReason {
    DELAY_REASON_NONE = 0,
    DELAY_REASON_GC = 1,
    DELAY_REASON_WAIT_FOR_IDLE = 2,
    DELAY_REASON_WAIT_FOR_IMPORTS = 3,
  };


  
  
  class TimeProvider {
   public:
    TimeProvider();

    virtual ~TimeProvider();

    
    virtual base::Time GetCurrentTime() const;

   private:
    DISALLOW_COPY_AND_ASSIGN(TimeProvider);
  };

  
  
  
  
  template <typename T, base::Value::Type type_enum_value>
  class ScopedUpdate {
   public:
    ScopedUpdate(ExtensionPrefs* prefs,
                 const std::string& extension_id,
                 const std::string& key);
    virtual ~ScopedUpdate();

    
    
    virtual T* Get();

    
    
    
    virtual T* Create();

   private:
    DictionaryPrefUpdate update_;
    const std::string extension_id_;
    const std::string key_;

    DISALLOW_COPY_AND_ASSIGN(ScopedUpdate);
  };
  typedef ScopedUpdate<base::DictionaryValue, base::Value::TYPE_DICTIONARY>
      ScopedDictionaryUpdate;
  typedef ScopedUpdate<base::ListValue, base::Value::TYPE_LIST>
      ScopedListUpdate;

  
  
  
  
  
  
  static ExtensionPrefs* Create(
      PrefService* prefs,
      const base::FilePath& root_dir,
      ExtensionPrefValueMap* extension_pref_value_map,
      scoped_ptr<AppSorting> app_sorting,
      bool extensions_disabled,
      const std::vector<ExtensionPrefsObserver*>& early_observers);

  
  
  static ExtensionPrefs* Create(
      PrefService* prefs,
      const base::FilePath& root_dir,
      ExtensionPrefValueMap* extension_pref_value_map,
      scoped_ptr<AppSorting> app_sorting,
      bool extensions_disabled,
      const std::vector<ExtensionPrefsObserver*>& early_observers,
      scoped_ptr<TimeProvider> time_provider);

  virtual ~ExtensionPrefs();

  
  static ExtensionPrefs* Get(content::BrowserContext* context);

  
  
  
  static ExtensionIdList GetExtensionsFrom(const PrefService* pref_service);

  
  void AddObserver(ExtensionPrefsObserver* observer);
  void RemoveObserver(ExtensionPrefsObserver* observer);

  
  
  bool IsExternalExtensionUninstalled(const std::string& id) const;

  
  
  
  bool IsExtensionDisabled(const std::string& id) const;

  
  ExtensionIdList GetToolbarOrder();
  void SetToolbarOrder(const ExtensionIdList& extension_ids);

  
  
  
  void OnExtensionInstalled(const Extension* extension,
                            Extension::State initial_state,
                            const syncer::StringOrdinal& page_ordinal,
                            int install_flags,
                            const std::string& install_parameter);
  
  void OnExtensionInstalled(const Extension* extension,
                            Extension::State initial_state,
                            const syncer::StringOrdinal& page_ordinal,
                            const std::string& install_parameter) {
    OnExtensionInstalled(extension,
                         initial_state,
                         page_ordinal,
                         kInstallFlagNone,
                         install_parameter);
  }

  
  void OnExtensionUninstalled(const std::string& extension_id,
                              const Manifest::Location& location,
                              bool external_uninstall);

  
  void SetExtensionState(const std::string& extension_id, Extension::State);

  
  
  
  void SetExtensionBlacklistState(const std::string& extension_id,
                                  BlacklistState state);

  
  
  BlacklistState GetExtensionBlacklistState(const std::string& extension_id);

  
  void GetExtensions(ExtensionIdList* out);

  
  virtual void UpdateExtensionPref(const std::string& id,
                                   const std::string& key,
                                   base::Value* value) OVERRIDE;

  virtual void DeleteExtensionPrefs(const std::string& id) OVERRIDE;

  virtual bool ReadPrefAsBoolean(const std::string& extension_id,
                                 const std::string& pref_key,
                                 bool* out_value) const OVERRIDE;

  virtual bool ReadPrefAsInteger(const std::string& extension_id,
                                 const std::string& pref_key,
                                 int* out_value) const OVERRIDE;

  virtual bool ReadPrefAsString(const std::string& extension_id,
                                const std::string& pref_key,
                                std::string* out_value) const OVERRIDE;

  virtual bool ReadPrefAsList(const std::string& extension_id,
                              const std::string& pref_key,
                              const base::ListValue** out_value) const OVERRIDE;

  virtual bool ReadPrefAsDictionary(
      const std::string& extension_id,
      const std::string& pref_key,
      const base::DictionaryValue** out_value) const OVERRIDE;

  virtual bool HasPrefForExtension(const std::string& extension_id) const
      OVERRIDE;

  
  bool DidExtensionEscalatePermissions(const std::string& id);

  
  
  void SetDidExtensionEscalatePermissions(
      const Extension* extension,
      bool did_escalate);

  
  int GetDisableReasons(const std::string& extension_id) const;
  bool HasDisableReason(const std::string& extension_id,
                        Extension::DisableReason disable_reason) const;
  void AddDisableReason(const std::string& extension_id,
                        Extension::DisableReason disable_reason);
  void RemoveDisableReason(const std::string& extension_id,
                           Extension::DisableReason disable_reason);
  void ClearDisableReasons(const std::string& extension_id);

  
  
  
  
  std::set<std::string> GetBlacklistedExtensions();

  
  void SetExtensionBlacklisted(const std::string& extension_id,
                               bool is_blacklisted);

  
  
  std::string GetVersionString(const std::string& extension_id);

  
  
  void UpdateManifest(const Extension* extension);

  
  const base::FilePath& install_directory() const { return install_directory_; }

  
  
  
  
  
  
  bool IsExtensionBlacklisted(const std::string& id) const;

  
  
  int IncrementAcknowledgePromptCount(const std::string& extension_id);

  
  bool IsExternalExtensionAcknowledged(const std::string& extension_id);
  void AcknowledgeExternalExtension(const std::string& extension_id);

  
  bool IsBlacklistedExtensionAcknowledged(const std::string& extension_id);
  void AcknowledgeBlacklistedExtension(const std::string& extension_id);

  
  
  bool IsExternalInstallFirstRun(const std::string& extension_id);
  void SetExternalInstallFirstRun(const std::string& extension_id);

  
  
  bool HasWipeoutBeenAcknowledged(const std::string& extension_id);
  void SetWipeoutAcknowledged(const std::string& extension_id, bool value);

  
  
  
  bool HasSettingsApiBubbleBeenAcknowledged(const std::string& extension_id);
  void SetSettingsApiBubbleBeenAcknowledged(const std::string& extension_id,
                                            bool value);

  
  
  bool HasNtpOverriddenBubbleBeenAcknowledged(const std::string& extension_id);
  void SetNtpOverriddenBubbleBeenAcknowledged(const std::string& extension_id,
                                              bool value);

  
  
  bool HasProxyOverriddenBubbleBeenAcknowledged(
      const std::string& extension_id);
  void SetProxyOverriddenBubbleBeenAcknowledged(const std::string& extension_id,
                                                bool value);

  
  
  
  
  
  
  bool SetAlertSystemFirstRun();

  
  
  base::Time LastPingDay(const std::string& extension_id) const;

  
  
  void SetLastPingDay(const std::string& extension_id, const base::Time& time);

  
  base::Time BlacklistLastPingDay() const;
  void SetBlacklistLastPingDay(const base::Time& time);

  
  
  base::Time LastActivePingDay(const std::string& extension_id);
  void SetLastActivePingDay(const std::string& extension_id,
                            const base::Time& time);

  
  
  
  bool GetActiveBit(const std::string& extension_id);
  void SetActiveBit(const std::string& extension_id, bool active);

  
  
  
  PermissionSet* GetGrantedPermissions(const std::string& extension_id);

  
  
  
  void AddGrantedPermissions(const std::string& extension_id,
                             const PermissionSet* permissions);

  
  void RemoveGrantedPermissions(const std::string& extension_id,
                                const PermissionSet* permissions);

  
  
  
  PermissionSet* GetActivePermissions(const std::string& extension_id);

  
  void SetActivePermissions(const std::string& extension_id,
                            const PermissionSet* permissions);

  
  void SetExtensionRunning(const std::string& extension_id, bool is_running);

  
  
  bool IsExtensionRunning(const std::string& extension_id);

  
  
  
  void SetIsActive(const std::string& extension_id, bool is_active);
  bool IsActive(const std::string& extension_id);

  
  
  
  
  
  bool IsIncognitoEnabled(const std::string& extension_id) const;
  void SetIsIncognitoEnabled(const std::string& extension_id, bool enabled);

  
  
  
  
  
  bool AllowFileAccess(const std::string& extension_id) const;
  void SetAllowFileAccess(const std::string& extension_id, bool allow);
  bool HasAllowFileAccessSetting(const std::string& extension_id) const;

  
  
  
  
  scoped_ptr<ExtensionsInfo> GetInstalledExtensionsInfo() const;

  
  
  scoped_ptr<ExtensionsInfo> GetUninstalledExtensionsInfo() const;

  
  
  scoped_ptr<ExtensionInfo> GetInstalledExtensionInfo(
      const std::string& extension_id) const;

  
  
  
  
  void SetDelayedInstallInfo(const Extension* extension,
                             Extension::State initial_state,
                             int install_flags,
                             DelayReason delay_reason,
                             const syncer::StringOrdinal& page_ordinal,
                             const std::string& install_parameter);

  
  
  bool RemoveDelayedInstallInfo(const std::string& extension_id);

  
  bool FinishDelayedInstallInfo(const std::string& extension_id);

  
  
  scoped_ptr<ExtensionInfo> GetDelayedInstallInfo(
      const std::string& extension_id) const;

  DelayReason GetDelayedInstallReason(const std::string& extension_id) const;

  
  
  scoped_ptr<ExtensionsInfo> GetAllDelayedInstallInfo() const;

  
  bool IsEphemeralApp(const std::string& extension_id) const;

  
  void OnEphemeralAppPromoted(const std::string& extension_id);

  
  
  bool WasAppDraggedByUser(const std::string& extension_id);

  
  
  void SetAppDraggedByUser(const std::string& extension_id);

  
  
  bool HasIncognitoPrefValue(const std::string& pref_key);

  
  int GetCreationFlags(const std::string& extension_id) const;

  
  int GetDelayedInstallCreationFlags(const std::string& extension_id) const;

  
  bool IsFromWebStore(const std::string& extension_id) const;

  
  
  bool IsFromBookmark(const std::string& extension_id) const;

  
  bool WasInstalledByDefault(const std::string& extension_id) const;

  
  bool WasInstalledByOem(const std::string& extension_id) const;

  
  
  
  base::Time GetInstallTime(const std::string& extension_id) const;

  
  bool DoNotSync(const std::string& extension_id) const;

  
  base::Time GetLastLaunchTime(const std::string& extension_id) const;
  void SetLastLaunchTime(const std::string& extension_id,
                         const base::Time& time);

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  bool extensions_disabled() const { return extensions_disabled_; }

  
  PrefService* pref_service() const { return prefs_; }

  
  AppSorting* app_sorting() const { return app_sorting_.get(); }

  
  
  
  void SetNeedsStorageGarbageCollection(bool value);
  bool NeedsStorageGarbageCollection();

  
  
  const base::DictionaryValue* GetGeometryCache(
        const std::string& extension_id) const;
  void SetGeometryCache(const std::string& extension_id,
                        scoped_ptr<base::DictionaryValue> cache);

  
  
  const base::DictionaryValue* GetInstallSignature();
  void SetInstallSignature(const base::DictionaryValue* signature);

  
  std::string GetInstallParam(const std::string& extension_id) const;
  void SetInstallParam(const std::string& extension_id,
                       const std::string& install_parameter);

  
  
  int GetCorruptedDisableCount();
  void IncrementCorruptedDisableCount();

 private:
  friend class ExtensionPrefsBlacklistedExtensions;  
  friend class ExtensionPrefsUninstallExtension;     

  enum DisableReasonChange {
    DISABLE_REASON_ADD,
    DISABLE_REASON_REMOVE,
    DISABLE_REASON_CLEAR
  };

  
  ExtensionPrefs(PrefService* prefs,
                 const base::FilePath& root_dir,
                 ExtensionPrefValueMap* extension_pref_value_map,
                 scoped_ptr<AppSorting> app_sorting,
                 scoped_ptr<TimeProvider> time_provider,
                 bool extensions_disabled,
                 const std::vector<ExtensionPrefsObserver*>& early_observers);

  
  
  void MakePathsRelative();

  
  
  void MakePathsAbsolute(base::DictionaryValue* dict);

  
  
  
  scoped_ptr<ExtensionInfo> GetInstalledInfoHelper(
      const std::string& extension_id,
      const base::DictionaryValue* extension) const;

  
  
  bool ReadPrefAsURLPatternSet(const std::string& extension_id,
                               const std::string& pref_key,
                               URLPatternSet* result,
                               int valid_schemes);

  
  
  void SetExtensionPrefURLPatternSet(const std::string& extension_id,
                                     const std::string& pref_key,
                                     const URLPatternSet& new_value);

  
  
  bool ReadPrefAsBooleanAndReturn(const std::string& extension_id,
                                  const std::string& key) const;

  
  
  PermissionSet* ReadPrefAsPermissionSet(const std::string& extension_id,
                                         const std::string& pref_key);

  
  
  void SetExtensionPrefPermissionSet(const std::string& extension_id,
                                     const std::string& pref_key,
                                     const PermissionSet* new_value);

  
  
  const base::DictionaryValue* GetExtensionPref(const std::string& id) const;

  
  
  
  
  void ModifyDisableReason(const std::string& extension_id,
                           Extension::DisableReason reason,
                           DisableReasonChange change);

  
  
  void FixMissingPrefs(const ExtensionIdList& extension_ids);

  
  
  void InitPrefStore();

  
  void MigratePermissions(const ExtensionIdList& extension_ids);

  
  void MigrateDisableReasons(const ExtensionIdList& extension_ids);

  
  
  bool DoesExtensionHaveState(const std::string& id,
                              Extension::State check_state) const;

  
  
  
  template <class ExtensionIdContainer>
  bool GetUserExtensionPrefIntoContainer(
      const char* pref,
      ExtensionIdContainer* id_container_out);

  
  template <class ExtensionIdContainer>
  void SetExtensionPrefFromContainer(const char* pref,
                                     const ExtensionIdContainer& strings);

  
  
  
  
  
  
  void PopulateExtensionInfoPrefs(const Extension* extension,
                                  const base::Time install_time,
                                  Extension::State initial_state,
                                  int install_flags,
                                  const std::string& install_parameter,
                                  base::DictionaryValue* extension_dict);

  void InitExtensionControlledPrefs(ExtensionPrefValueMap* value_map);

  
  
  
  void FinishExtensionInfoPrefs(
      const std::string& extension_id,
      const base::Time install_time,
      bool needs_sort_ordinal,
      const syncer::StringOrdinal& suggested_page_ordinal,
      base::DictionaryValue* extension_dict);

  
  
  PrefService* prefs_;

  
  base::FilePath install_directory_;

  
  ExtensionPrefValueMap* extension_pref_value_map_;

  
  
  scoped_ptr<AppSorting> app_sorting_;

  scoped_ptr<TimeProvider> time_provider_;

  bool extensions_disabled_;

  ObserverList<ExtensionPrefsObserver> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionPrefs);
};

}  

#endif  

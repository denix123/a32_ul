// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_PREFERENCES_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_PREFERENCES_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/storage_monitor/removable_storage_observer.h"

class Profile;

namespace base {
class DictionaryValue;
}

namespace extensions {
class Extension;
class ExtensionPrefs;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

typedef uint64 MediaGalleryPrefId;
const MediaGalleryPrefId kInvalidMediaGalleryPrefId = 0;

const char kMediaGalleriesPrefsVersionKey[] = "preferencesVersion";
const char kMediaGalleriesDefaultGalleryTypeKey[] = "defaultGalleryType";

struct MediaGalleryPermission {
  MediaGalleryPrefId pref_id;
  bool has_permission;
};

struct MediaGalleryPrefInfo {
  enum Type {
    kUserAdded,     
    kAutoDetected,  
    kBlackListed,   
    kScanResult,    
    kRemovedScan,   
    kInvalidType,
  };

  enum DefaultGalleryType {
    kNotDefault,    
    kMusicDefault,
    kPicturesDefault,
    kVideosDefault,
  };

  MediaGalleryPrefInfo();
  ~MediaGalleryPrefInfo();

  
  base::FilePath AbsolutePath() const;

  
  
  bool IsBlackListedType() const;

  
  MediaGalleryPrefId pref_id;

  
  base::string16 display_name;

  
  
  std::string device_id;

  
  base::FilePath path;

  
  Type type;

  
  
  base::string16 volume_label;

  
  
  base::string16 vendor_name;

  
  
  base::string16 model_name;

  
  
  uint64 total_size_in_bytes;

  
  
  
  base::Time last_attach_time;

  
  
  // never written.
  bool volume_metadata_valid;

  
  
  
  int audio_count;
  int image_count;
  int video_count;

  
  DefaultGalleryType default_gallery_type;

  
  
  
  
  
  
  int prefs_version;

  
  base::string16 GetGalleryDisplayName() const;
  base::string16 GetGalleryTooltip() const;
  base::string16 GetGalleryAdditionalDetails() const;

  
  
  bool IsGalleryAvailable() const;
};

typedef std::map<MediaGalleryPrefId, MediaGalleryPrefInfo>
    MediaGalleriesPrefInfoMap;
typedef std::set<MediaGalleryPrefId> MediaGalleryPrefIdSet;

class MediaGalleriesPreferences
    : public KeyedService,
      public storage_monitor::RemovableStorageObserver {
 public:
  class GalleryChangeObserver {
   public:
    
    
    virtual void OnPermissionAdded(MediaGalleriesPreferences* pref,
                                   const std::string& extension_id,
                                   MediaGalleryPrefId pref_id) {}

    virtual void OnPermissionRemoved(MediaGalleriesPreferences* pref,
                                     const std::string& extension_id,
                                     MediaGalleryPrefId pref_id) {}

    virtual void OnGalleryAdded(MediaGalleriesPreferences* pref,
                                MediaGalleryPrefId pref_id) {}

    virtual void OnGalleryRemoved(MediaGalleriesPreferences* pref,
                                  MediaGalleryPrefId pref_id) {}

    virtual void OnGalleryInfoUpdated(MediaGalleriesPreferences* pref,
                                      MediaGalleryPrefId pref_id) {}

   protected:
    virtual ~GalleryChangeObserver();
  };

  explicit MediaGalleriesPreferences(Profile* profile);
  virtual ~MediaGalleriesPreferences();

  
  
  
  
  
  
  
  
  void EnsureInitialized(base::Closure callback);

  
  bool IsInitialized() const;

  Profile* profile();

  void AddGalleryChangeObserver(GalleryChangeObserver* observer);
  void RemoveGalleryChangeObserver(GalleryChangeObserver* observer);

  
  virtual void OnRemovableStorageAttached(
      const storage_monitor::StorageInfo& info) OVERRIDE;

  
  
  bool LookUpGalleryByPath(const base::FilePath& path,
                           MediaGalleryPrefInfo* gallery) const;

  MediaGalleryPrefIdSet LookUpGalleriesByDeviceId(
      const std::string& device_id) const;

  
  
  
  
  
  
  
  
  base::FilePath LookUpGalleryPathForExtension(
      MediaGalleryPrefId gallery_id,
      const extensions::Extension* extension,
      bool include_unpermitted_galleries);

  
  
  
  MediaGalleryPrefId AddGallery(const std::string& device_id,
                                const base::FilePath& relative_path,
                                MediaGalleryPrefInfo::Type type,
                                const base::string16& volume_label,
                                const base::string16& vendor_name,
                                const base::string16& model_name,
                                uint64 total_size_in_bytes,
                                base::Time last_attach_time,
                                int audio_count,
                                int image_count,
                                int video_count);

  
  
  
  MediaGalleryPrefId AddGalleryByPath(const base::FilePath& path,
                                      MediaGalleryPrefInfo::Type type);

  
  
  
  
  void ForgetGalleryById(MediaGalleryPrefId id);

  
  
  
  void EraseGalleryById(MediaGalleryPrefId id);

  
  
  bool NonAutoGalleryHasPermission(MediaGalleryPrefId id) const;

  MediaGalleryPrefIdSet GalleriesForExtension(
      const extensions::Extension& extension);

  
  
  bool SetGalleryPermissionForExtension(const extensions::Extension& extension,
                                        MediaGalleryPrefId pref_id,
                                        bool has_permission);

  const MediaGalleriesPrefInfoMap& known_galleries() const;

  
  
  base::Time GetLastScanCompletionTime() const;
  void SetLastScanCompletionTime(const base::Time& time);

  
  virtual void Shutdown() OVERRIDE;

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  
  static bool APIHasBeenUsed(Profile* profile);

 private:
  friend class MediaGalleriesPreferencesTest;
  friend class MediaGalleriesPermissionsTest;

  typedef std::map<std::string , MediaGalleryPrefIdSet>
      DeviceIdPrefIdsMap;

  
  void OnInitializationCallbackReturned();
  void FinishInitialization();

  
  void AddDefaultGalleries();

  
  
  
  
  
  
  
  
  
  bool UpdateDeviceIDForSingletonType(const std::string& device_id);

  void OnStorageMonitorInit(bool api_has_been_used);

  
  void OnFinderDeviceID(const std::string& device_id);

  
  void InitFromPrefs();

  
  
  
  MediaGalleryPrefId AddOrUpdateGalleryInternal(
      const std::string& device_id,
      const base::string16& display_name,
      const base::FilePath& relative_path,
      MediaGalleryPrefInfo::Type type,
      const base::string16& volume_label,
      const base::string16& vendor_name,
      const base::string16& model_name,
      uint64 total_size_in_bytes,
      base::Time last_attach_time,
      bool volume_metadata_valid,
      int audio_count,
      int image_count,
      int video_count,
      int prefs_version,
      MediaGalleryPrefInfo::DefaultGalleryType default_gallery_type);

  void EraseOrBlacklistGalleryById(MediaGalleryPrefId id, bool erase);

  
  
  
  void UpdateDefaultGalleriesPaths();

  
  
  bool SetGalleryPermissionInPrefs(const std::string& extension_id,
                                   MediaGalleryPrefId gallery_id,
                                   bool has_access);

  
  
  
  bool UnsetGalleryPermissionInPrefs(const std::string& extension_id,
                                     MediaGalleryPrefId gallery_id);

  
  
  std::vector<MediaGalleryPermission> GetGalleryPermissionsFromPrefs(
      const std::string& extension_id) const;

  
  
  void RemoveGalleryPermissionsFromPrefs(MediaGalleryPrefId gallery_id);

  
  
  
  extensions::ExtensionPrefs* GetExtensionPrefs() const;

  
  void SetExtensionPrefsForTesting(extensions::ExtensionPrefs* extension_prefs);

  bool initialized_;
  std::vector<base::Closure> on_initialize_callbacks_;
  int pre_initialization_callbacks_waiting_;

  
  Profile* profile_;

  
  
  
  extensions::ExtensionPrefs* extension_prefs_for_testing_;

  
  MediaGalleriesPrefInfoMap known_galleries_;

  
  
  DeviceIdPrefIdsMap device_map_;

  ObserverList<GalleryChangeObserver> gallery_change_observers_;

  base::WeakPtrFactory<MediaGalleriesPreferences> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaGalleriesPreferences);
};

#endif  

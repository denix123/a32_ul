// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_SCAN_RESULT_CONTROLLER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_SCAN_RESULT_CONTROLLER_H_

#include <map>
#include <set>
#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/media_galleries/media_galleries_dialog_controller.h"
#include "chrome/browser/media_galleries/media_galleries_preferences.h"
#include "components/storage_monitor/removable_storage_observer.h"

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
}

namespace ui {
class MenuModel;
}

class MediaGalleriesScanResultController;
class MediaGalleryContextMenu;
class Profile;

class MediaGalleriesScanResultController
    : public MediaGalleriesDialogController,
      public storage_monitor::RemovableStorageObserver,
      public MediaGalleriesPreferences::GalleryChangeObserver {
 public:
  
  static size_t ScanResultCountForExtension(
      MediaGalleriesPreferences* preferences,
      const extensions::Extension* extension);

  
  MediaGalleriesScanResultController(
      content::WebContents* web_contents,
      const extensions::Extension& extension,
      const base::Closure& on_finish);

  
  virtual base::string16 GetHeader() const OVERRIDE;
  virtual base::string16 GetSubtext() const OVERRIDE;
  virtual bool IsAcceptAllowed() const OVERRIDE;
  virtual bool ShouldShowFolderViewer(const Entry& entry) const OVERRIDE;
  virtual std::vector<base::string16> GetSectionHeaders() const OVERRIDE;
  virtual Entries GetSectionEntries(size_t index) const OVERRIDE;
  virtual base::string16 GetAuxiliaryButtonText() const OVERRIDE;
  virtual void DidClickAuxiliaryButton() OVERRIDE;
  virtual void DidToggleEntry(MediaGalleryPrefId id, bool selected) OVERRIDE;
  virtual void DidClickOpenFolderViewer(MediaGalleryPrefId id) OVERRIDE;
  virtual void DidForgetEntry(MediaGalleryPrefId id) OVERRIDE;
  virtual base::string16 GetAcceptButtonText() const OVERRIDE;
  virtual void DialogFinished(bool accepted) OVERRIDE;
  virtual ui::MenuModel* GetContextMenu(MediaGalleryPrefId id) OVERRIDE;
  virtual content::WebContents* WebContents() OVERRIDE;

 protected:
  typedef base::Callback<MediaGalleriesDialog* (
      MediaGalleriesDialogController*)> CreateDialogCallback;
  typedef std::map<MediaGalleryPrefId, Entry> ScanResults;

  
  
  static void UpdateScanResultsFromPreferences(
      MediaGalleriesPreferences* preferences,
      const extensions::Extension* extension,
      MediaGalleryPrefIdSet ignore_list,
      ScanResults* scan_results);

  
  MediaGalleriesScanResultController(
      const extensions::Extension& extension,
      MediaGalleriesPreferences* preferences_,
      const CreateDialogCallback& create_dialog_callback,
      const base::Closure& on_finish);

  virtual ~MediaGalleriesScanResultController();

 private:
  friend class MediaGalleriesScanResultControllerTest;
  friend class MediaGalleriesScanResultCocoaTest;
  friend class TestMediaGalleriesAddScanResultsFunction;

  
  void OnPreferencesInitialized();

  
  void OnPreferenceUpdate(const std::string& extension_id);

  
  void OnRemovableDeviceUpdate(const std::string device_id);

  Profile* GetProfile() const;

  
  
  virtual void OnRemovableStorageAttached(
      const storage_monitor::StorageInfo& info) OVERRIDE;
  virtual void OnRemovableStorageDetached(
      const storage_monitor::StorageInfo& info) OVERRIDE;

  
  
  virtual void OnPermissionAdded(MediaGalleriesPreferences* pref,
                                 const std::string& extension_id,
                                 MediaGalleryPrefId pref_id) OVERRIDE;
  virtual void OnPermissionRemoved(MediaGalleriesPreferences* pref,
                                   const std::string& extension_id,
                                   MediaGalleryPrefId pref_id) OVERRIDE;
  virtual void OnGalleryAdded(MediaGalleriesPreferences* pref,
                              MediaGalleryPrefId pref_id) OVERRIDE;
  virtual void OnGalleryRemoved(MediaGalleriesPreferences* pref,
                                MediaGalleryPrefId pref_id) OVERRIDE;
  virtual void OnGalleryInfoUpdated(MediaGalleriesPreferences* pref,
                                    MediaGalleryPrefId pref_id) OVERRIDE;

  
  content::WebContents* web_contents_;

  
  
  const extensions::Extension* extension_;

  
  
  ScanResults scan_results_;

  
  
  MediaGalleryPrefIdSet results_to_remove_;

  
  base::Closure on_finish_;

  
  
  MediaGalleriesPreferences* preferences_;

  
  CreateDialogCallback create_dialog_callback_;

  
  scoped_ptr<MediaGalleriesDialog> dialog_;

  scoped_ptr<MediaGalleryContextMenu> context_menu_;

  DISALLOW_COPY_AND_ASSIGN(MediaGalleriesScanResultController);
};

#endif  

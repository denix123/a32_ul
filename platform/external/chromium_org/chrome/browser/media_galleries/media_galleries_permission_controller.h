// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_PERMISSION_CONTROLLER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_PERMISSION_CONTROLLER_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/media_galleries/media_galleries_dialog_controller.h"
#include "chrome/browser/media_galleries/media_galleries_preferences.h"
#include "components/storage_monitor/removable_storage_observer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/shell_dialogs/select_file_dialog.h"

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
}

namespace ui {
class MenuModel;
}

class MediaGalleriesDialogController;
class MediaGalleryContextMenu;
class Profile;

typedef MediaGalleryPrefId GalleryDialogId;

class MediaGalleriesPermissionController
    : public MediaGalleriesDialogController,
      public ui::SelectFileDialog::Listener,
      public storage_monitor::RemovableStorageObserver,
      public MediaGalleriesPreferences::GalleryChangeObserver {
 public:
  
  MediaGalleriesPermissionController(content::WebContents* web_contents,
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
  virtual void DidToggleEntry(GalleryDialogId gallery_id,
                              bool selected) OVERRIDE;
  virtual void DidClickOpenFolderViewer(GalleryDialogId gallery_id) OVERRIDE;
  virtual void DidForgetEntry(GalleryDialogId gallery_id) OVERRIDE;
  virtual base::string16 GetAcceptButtonText() const OVERRIDE;
  virtual void DialogFinished(bool accepted) OVERRIDE;
  virtual ui::MenuModel* GetContextMenu(GalleryDialogId gallery_id) OVERRIDE;
  virtual content::WebContents* WebContents() OVERRIDE;

 protected:
  friend class MediaGalleriesPermissionControllerTest;

  typedef base::Callback<MediaGalleriesDialog* (
      MediaGalleriesDialogController*)> CreateDialogCallback;

  
  MediaGalleriesPermissionController(
      const extensions::Extension& extension,
      MediaGalleriesPreferences* preferences,
      const CreateDialogCallback& create_dialog_callback,
      const base::Closure& on_finish);

  virtual ~MediaGalleriesPermissionController();

 private:
  
  typedef std::map<GalleryDialogId, Entry> GalleryPermissionsMap;
  typedef std::map<GalleryDialogId, bool > ToggledGalleryMap;

  class DialogIdMap {
   public:
    DialogIdMap();
    ~DialogIdMap();
    GalleryDialogId GetDialogId(MediaGalleryPrefId pref_id);
    MediaGalleryPrefId GetPrefId(GalleryDialogId id) const;

   private:
    GalleryDialogId next_dialog_id_;
    std::map<MediaGalleryPrefId, GalleryDialogId> back_map_;
    std::vector<MediaGalleryPrefId> forward_mapping_;
    DISALLOW_COPY_AND_ASSIGN(DialogIdMap);
  };


  
  void OnPreferencesInitialized();

  
  virtual void FileSelected(const base::FilePath& path,
                            int index,
                            void* params) OVERRIDE;

  
  
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

  
  
  
  void InitializePermissions();

  
  
  
  
  
  
  
  
  
  
  
  
  void SavePermissions();

  
  
  
  void UpdateGalleriesOnPreferencesEvent();

  
  void UpdateGalleriesOnDeviceEvent(const std::string& device_id);

  GalleryDialogId GetDialogId(MediaGalleryPrefId pref_id);
  MediaGalleryPrefId GetPrefId(GalleryDialogId id) const;

  Profile* GetProfile();

  
  content::WebContents* web_contents_;

  
  
  const extensions::Extension* extension_;

  
  DialogIdMap id_map_;

  
  
  GalleryPermissionsMap known_galleries_;

  
  ToggledGalleryMap toggled_galleries_;

  
  MediaGalleryPrefIdSet pref_permitted_galleries_;

  
  
  GalleryPermissionsMap new_galleries_;

  
  std::set<GalleryDialogId> forgotten_galleries_;

  
  base::Closure on_finish_;

  
  
  MediaGalleriesPreferences* preferences_;

  
  scoped_ptr<MediaGalleriesDialog> dialog_;

  scoped_refptr<ui::SelectFileDialog> select_folder_dialog_;

  scoped_ptr<MediaGalleryContextMenu> context_menu_;

  
  CreateDialogCallback create_dialog_callback_;

  DISALLOW_COPY_AND_ASSIGN(MediaGalleriesPermissionController);
};

#endif  

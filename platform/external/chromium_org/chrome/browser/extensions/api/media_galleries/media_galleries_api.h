// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_EXTENSIONS_API_MEDIA_GALLERIES_MEDIA_GALLERIES_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_MEDIA_GALLERIES_MEDIA_GALLERIES_API_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/browser/media_galleries/gallery_watch_manager_observer.h"
#include "chrome/browser/media_galleries/media_file_system_registry.h"
#include "chrome/browser/media_galleries/media_scan_manager_observer.h"
#include "chrome/common/extensions/api/media_galleries.h"
#include "chrome/common/media_galleries/metadata_types.h"
#include "components/storage_monitor/media_storage_util.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"

namespace MediaGalleries = extensions::api::media_galleries;

class MediaGalleriesScanResultController;

namespace content {
class BlobHandle;
class WebContents;
}

namespace metadata {
class SafeMediaMetadataParser;
}

namespace extensions {

class Extension;

class MediaGalleriesEventRouter : public BrowserContextKeyedAPI,
                                  public GalleryWatchManagerObserver,
                                  public MediaScanManagerObserver,
                                  public extensions::EventRouter::Observer {
 public:
  
  virtual void Shutdown() OVERRIDE;

  
  static BrowserContextKeyedAPIFactory<MediaGalleriesEventRouter>*
      GetFactoryInstance();

  
  static MediaGalleriesEventRouter* Get(content::BrowserContext* context);

  bool ExtensionHasGalleryChangeListener(const std::string& extension_id) const;
  bool ExtensionHasScanProgressListener(const std::string& extension_id) const;

  
  virtual void OnScanStarted(const std::string& extension_id) OVERRIDE;
  virtual void OnScanCancelled(const std::string& extension_id) OVERRIDE;
  virtual void OnScanFinished(
      const std::string& extension_id,
      int gallery_count,
      const MediaGalleryScanResult& file_counts) OVERRIDE;
  virtual void OnScanError(const std::string& extension_id) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<MediaGalleriesEventRouter>;

  void DispatchEventToExtension(const std::string& extension_id,
                                const std::string& event_name,
                                scoped_ptr<base::ListValue> event_args);

  explicit MediaGalleriesEventRouter(content::BrowserContext* context);
  virtual ~MediaGalleriesEventRouter();

  
  static const char* service_name() {
    return "MediaGalleriesAPI";
  }
  static const bool kServiceIsNULLWhileTesting = true;

  
  virtual void OnGalleryChanged(const std::string& extension_id,
                                MediaGalleryPrefId gallery_id) OVERRIDE;
  virtual void OnGalleryWatchDropped(const std::string& extension_id,
                                     MediaGalleryPrefId gallery_id) OVERRIDE;

  
  virtual void OnListenerRemoved(const EventListenerInfo& details) OVERRIDE;

  
  Profile* profile_;

  base::WeakPtrFactory<MediaGalleriesEventRouter> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaGalleriesEventRouter);
};

class MediaGalleriesGetMediaFileSystemsFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.getMediaFileSystems",
                             MEDIAGALLERIES_GETMEDIAFILESYSTEMS)

 protected:
  virtual ~MediaGalleriesGetMediaFileSystemsFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void OnPreferencesInit(
      MediaGalleries::GetMediaFileSystemsInteractivity interactive);

  
  void AlwaysShowDialog(const std::vector<MediaFileSystemInfo>& filesystems);

  
  void ShowDialogIfNoGalleries(
      const std::vector<MediaFileSystemInfo>& filesystems);

  
  
  void GetAndReturnGalleries();

  
  void ReturnGalleries(const std::vector<MediaFileSystemInfo>& filesystems);

  
  void ShowDialog();

  
  
  void GetMediaFileSystemsForExtension(const MediaFileSystemsCallback& cb);
};

class MediaGalleriesGetAllMediaFileSystemMetadataFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.getAllMediaFileSystemMetadata",
                             MEDIAGALLERIES_GETALLMEDIAFILESYSTEMMETADATA)

 protected:
  virtual ~MediaGalleriesGetAllMediaFileSystemMetadataFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  
  
  void OnPreferencesInit();

  
  
  void OnGetGalleries(
      const MediaGalleryPrefIdSet& permitted_gallery_ids,
      const storage_monitor::MediaStorageUtil::DeviceIdSet* available_devices);
};

class MediaGalleriesAddUserSelectedFolderFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.addUserSelectedFolder",
                             MEDIAGALLERIES_ADDUSERSELECTEDFOLDER)

 protected:
  virtual ~MediaGalleriesAddUserSelectedFolderFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void OnPreferencesInit();

  
  
  
  void OnDirectorySelected(const base::FilePath& selected_directory);

  
  
  
  
  
  void ReturnGalleriesAndId(
      MediaGalleryPrefId pref_id,
      const std::vector<MediaFileSystemInfo>& filesystems);

  
  
  void GetMediaFileSystemsForExtension(const MediaFileSystemsCallback& cb);
};

class MediaGalleriesDropPermissionForMediaFileSystemFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.dropPermissionForMediaFileSystem",
                             MEDIAGALLERIES_DROPPERMISSIONFORMEDIAFILESYSTEM)

 protected:
  virtual ~MediaGalleriesDropPermissionForMediaFileSystemFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void OnPreferencesInit(MediaGalleryPrefId pref_id);
};

class MediaGalleriesStartMediaScanFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.startMediaScan",
                             MEDIAGALLERIES_STARTMEDIASCAN)

 protected:
  virtual ~MediaGalleriesStartMediaScanFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void OnPreferencesInit();
};

class MediaGalleriesCancelMediaScanFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.cancelMediaScan",
                             MEDIAGALLERIES_CANCELMEDIASCAN)

 protected:
  virtual ~MediaGalleriesCancelMediaScanFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void OnPreferencesInit();
};

class MediaGalleriesAddScanResultsFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.addScanResults",
                             MEDIAGALLERIES_ADDSCANRESULTS)

 protected:
  virtual ~MediaGalleriesAddScanResultsFunction();
  virtual bool RunAsync() OVERRIDE;

  
  virtual MediaGalleriesScanResultController* MakeDialog(
      content::WebContents* web_contents,
      const extensions::Extension& extension,
      const base::Closure& on_finish);

 private:
  
  void OnPreferencesInit();

  
  
  void GetAndReturnGalleries();

  
  void ReturnGalleries(const std::vector<MediaFileSystemInfo>& filesystems);
};

class MediaGalleriesGetMetadataFunction : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.getMetadata",
                             MEDIAGALLERIES_GETMETADATA)

 protected:
  virtual ~MediaGalleriesGetMetadataFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void OnPreferencesInit(MediaGalleries::GetMetadataType metadata_type,
                         const std::string& blob_uuid);

  void GetMetadata(MediaGalleries::GetMetadataType metadata_type,
                   const std::string& blob_uuid,
                   scoped_ptr<std::string> blob_header,
                   int64 total_blob_length);

  void OnSafeMediaMetadataParserDone(
      bool parse_success, scoped_ptr<base::DictionaryValue> result_dictionary,
      scoped_ptr<std::vector<metadata::AttachedImage> > attached_images);

  void ConstructNextBlob(
      scoped_ptr<base::DictionaryValue> result_dictionary,
      scoped_ptr<std::vector<metadata::AttachedImage> > attached_images,
      scoped_ptr<std::vector<std::string> > blob_uuids,
      scoped_ptr<content::BlobHandle> current_blob);
};

class MediaGalleriesAddGalleryWatchFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.addGalleryWatch",
                             MEDIAGALLERIES_ADDGALLERYWATCH);

 protected:
  virtual ~MediaGalleriesAddGalleryWatchFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnPreferencesInit(const std::string& pref_id);

  
  void HandleResponse(MediaGalleryPrefId gallery_id, const std::string& error);
};

class MediaGalleriesRemoveGalleryWatchFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.removeGalleryWatch",
                             MEDIAGALLERIES_REMOVEGALLERYWATCH);

 protected:
  virtual ~MediaGalleriesRemoveGalleryWatchFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnPreferencesInit(const std::string& pref_id);
};

class MediaGalleriesGetAllGalleryWatchFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.getAllGalleryWatch",
                             MEDIAGALLERIES_GETALLGALLERYWATCH);

 protected:
  virtual ~MediaGalleriesGetAllGalleryWatchFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnPreferencesInit();
};

class MediaGalleriesRemoveAllGalleryWatchFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("mediaGalleries.removeAllGalleryWatch",
                             MEDIAGALLERIES_REMOVEALLGALLERYWATCH);

 protected:
  virtual ~MediaGalleriesRemoveAllGalleryWatchFunction();
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnPreferencesInit();
};

}  

#endif  

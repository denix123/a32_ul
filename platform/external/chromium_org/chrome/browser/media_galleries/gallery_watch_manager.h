// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_GALLERY_WATCH_MANAGER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_GALLERY_WATCH_MANAGER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/files/file_path_watcher.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "chrome/browser/media_galleries/media_galleries_preferences.h"
#include "components/storage_monitor/removable_storage_observer.h"

class GalleryWatchManagerObserver;

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;
}

class GalleryWatchManager
    : public MediaGalleriesPreferences::GalleryChangeObserver,
      public storage_monitor::RemovableStorageObserver {
 public:
  
  typedef base::Callback<void(const std::string& )> ResultCallback;

  static const char kInvalidGalleryIDError[];
  static const char kNoPermissionError[];
  static const char kCouldNotWatchGalleryError[];

  GalleryWatchManager();
  virtual ~GalleryWatchManager();

  
  
  
  void AddObserver(content::BrowserContext* browser_context,
                   GalleryWatchManagerObserver* observer);
  void RemoveObserver(content::BrowserContext* browser_context);

  
  void ShutdownBrowserContext(content::BrowserContext* browser_context);

  
  void AddWatch(content::BrowserContext* browser_context,
                const extensions::Extension* extension,
                MediaGalleryPrefId gallery_id,
                const ResultCallback& callback);

  
  
  void RemoveWatch(content::BrowserContext* browser_context,
                   const std::string& extension_id,
                   MediaGalleryPrefId gallery_id);

  
  void RemoveAllWatches(content::BrowserContext* browser_context,
                        const std::string& extension_id);

  
  MediaGalleryPrefIdSet GetWatchSet(content::BrowserContext* browser_context,
                                    const std::string& extension_id);

 private:
  class FileWatchManager;

  
  struct WatchOwner {
    WatchOwner(content::BrowserContext* browser_context,
               const std::string& extension_id,
               MediaGalleryPrefId gallery_id);

    content::BrowserContext* browser_context;
    const std::string extension_id;
    MediaGalleryPrefId gallery_id;

    
    bool operator<(const WatchOwner& other) const;
  };

  struct NotificationInfo {
    NotificationInfo();
    ~NotificationInfo();

    std::set<WatchOwner> owners;
    base::Time last_notify_time;
    bool delayed_notification_pending;
  };

  typedef std::map<WatchOwner, base::FilePath> WatchesMap;
  typedef std::map<base::FilePath, NotificationInfo> WatchedPaths;
  typedef std::map<content::BrowserContext*, GalleryWatchManagerObserver*>
      ObserverMap;

  
  
  void DeactivateFileWatch(const WatchOwner& owner, const base::FilePath& path);

  
  
  void OnFileWatchActivated(const WatchOwner& owner,
                            const base::FilePath& path,
                            const ResultCallback& callback,
                            bool success);

  
  void OnFilePathChanged(const base::FilePath& path, bool error);

  
  virtual void OnPermissionRemoved(MediaGalleriesPreferences* pref,
                                   const std::string& extension_id,
                                   MediaGalleryPrefId pref_id) OVERRIDE;
  virtual void OnGalleryRemoved(MediaGalleriesPreferences* pref,
                                MediaGalleryPrefId pref_id) OVERRIDE;

  
  virtual void OnRemovableStorageDetached(
      const storage_monitor::StorageInfo& info) OVERRIDE;

  
  bool storage_monitor_observed_;

  
  std::set<MediaGalleriesPreferences*> observed_preferences_;

  
  WatchesMap watches_;

  
  WatchedPaths watched_paths_;

  
  ObserverMap observers_;

  
  scoped_ptr<FileWatchManager> watch_manager_;

  base::WeakPtrFactory<GalleryWatchManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(GalleryWatchManager);
};

#endif  

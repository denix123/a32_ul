// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_SCAN_MANAGER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_SCAN_MANAGER_H_

#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "base/time/time.h"
#include "chrome/browser/media_galleries/media_folder_finder.h"
#include "chrome/browser/media_galleries/media_scan_types.h"
#include "extensions/browser/extension_registry_observer.h"

class MediaScanManagerObserver;
class Profile;

namespace extensions {
class Extension;
class ExtensionRegistry;
}

class MediaScanManager : public extensions::ExtensionRegistryObserver {
 public:
  MediaScanManager();
  virtual ~MediaScanManager();

  
  
  void AddObserver(Profile* profile, MediaScanManagerObserver* observer);
  void RemoveObserver(Profile* profile);

  
  void CancelScansForProfile(Profile* profile);

  
  
  
  void StartScan(Profile* profile, const extensions::Extension* extension,
                 bool user_gesture);
  void CancelScan(Profile* profile, const extensions::Extension* extension);

 protected:
  friend class MediaGalleriesPlatformAppBrowserTest;
  friend class MediaScanManagerTest;

  typedef base::Callback<MediaFolderFinder*(
      const MediaFolderFinder::MediaFolderFinderResultsCallback&)>
          MediaFolderFinderFactory;

  void SetMediaFolderFinderFactory(const MediaFolderFinderFactory& factory);

  
  static MediaFolderFinder::MediaFolderFinderResults FindContainerScanResults(
      const MediaFolderFinder::MediaFolderFinderResults& found_folders,
      const std::vector<base::FilePath>& sensitive_locations);

 private:
  struct ScanObservers {
    ScanObservers();
    ~ScanObservers();
    MediaScanManagerObserver* observer;
    std::set<std::string > scanning_extensions;
  };
  typedef std::map<Profile*, ScanObservers> ScanObserverMap;

  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;

  bool ScanInProgress() const;

  void OnScanCompleted(
      bool success,
      const MediaFolderFinder::MediaFolderFinderResults& found_folders);

  void OnFoundContainerDirectories(
      const MediaFolderFinder::MediaFolderFinderResults& found_folders,
      const MediaFolderFinder::MediaFolderFinderResults& container_folders);

  scoped_ptr<MediaFolderFinder> folder_finder_;

  base::Time scan_start_time_;

  
  MediaFolderFinderFactory testing_folder_finder_factory_;

  
  ScanObserverMap observers_;

  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      scoped_extension_registry_observer_;

  base::WeakPtrFactory<MediaScanManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaScanManager);
};

#endif  

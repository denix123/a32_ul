// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_DRIVE_DRIVE_APP_REGISTRY_H_
#define CHROME_BROWSER_DRIVE_DRIVE_APP_REGISTRY_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "google_apis/drive/gdata_errorcode.h"
#include "url/gurl.h"

namespace google_apis {
class AppList;
}  

namespace drive {

class DriveAppRegistryObserver;
class DriveServiceInterface;

struct DriveAppInfo {
  typedef std::vector<std::pair<int, GURL> > IconList;

  DriveAppInfo();
  DriveAppInfo(const std::string& app_id,
               const std::string& product_id,
               const IconList& app_icons,
               const IconList& document_icons,
               const std::string& app_name,
               const GURL& create_url,
               bool is_removable);
  ~DriveAppInfo();

  
  std::string app_id;
  
  
  
  
  std::string product_id;
  
  
  IconList app_icons;
  
  
  IconList document_icons;
  
  std::string app_name;
  
  
  GURL create_url;
  
  
  bool is_removable;
};

typedef base::Callback<void(google_apis::GDataErrorCode)> UninstallCallback;

class DriveAppRegistry {
 public:
  explicit DriveAppRegistry(DriveServiceInterface* scheduler);
  ~DriveAppRegistry();

  
  
  void GetAppsForFile(const base::FilePath::StringType& file_extension,
                      const std::string& mime_type,
                      std::vector<DriveAppInfo>* apps) const;

  
  void GetAppList(std::vector<DriveAppInfo>* apps) const;

  
  
  
  
  void UninstallApp(const std::string& app_id,
                    const UninstallCallback& callback);

  
  
  static bool IsAppUninstallSupported();

  
  void Update();

  
  void UpdateFromAppList(const google_apis::AppList& app_list);

  void AddObserver(DriveAppRegistryObserver* observer);
  void RemoveObserver(DriveAppRegistryObserver* observer);

 private:
  
  
  void UpdateAfterGetAppList(google_apis::GDataErrorCode gdata_error,
                             scoped_ptr<google_apis::AppList> app_list);

  
  void OnAppUninstalled(const std::string& app_id,
                        const UninstallCallback& callback,
                        google_apis::GDataErrorCode error);

  
  std::map<std::string, DriveAppInfo> all_apps_;

  
  
  typedef std::multimap<std::string, std::string> DriveAppFileSelectorMap;
  DriveAppFileSelectorMap extension_map_;
  DriveAppFileSelectorMap mimetype_map_;

  DriveServiceInterface* drive_service_;

  bool is_updating_;

  ObserverList<DriveAppRegistryObserver> observers_;

  
  
  base::WeakPtrFactory<DriveAppRegistry> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DriveAppRegistry);
};

namespace util {

const int kPreferredIconSize = 16;

GURL FindPreferredIcon(const DriveAppInfo::IconList& icons,
                       int preferred_size);

}  

}  

#endif  

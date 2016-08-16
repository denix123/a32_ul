// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_WEB_APPLICATIONS_WEB_APP_H_
#define CHROME_BROWSER_WEB_APPLICATIONS_WEB_APP_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "build/build_config.h"
#include "chrome/browser/shell_integration.h"
#include "chrome/common/web_application_info.h"
#include "extensions/common/manifest_handlers/file_handler_info.h"

class Profile;

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
}

namespace gfx {
class ImageFamily;
}

namespace web_app {

struct ShortcutInfo {
  ShortcutInfo();
  ~ShortcutInfo();

  GURL url;
  
  
  
  std::string extension_id;
  bool is_platform_app;
  base::string16 title;
  base::string16 description;
  base::FilePath extension_path;
  gfx::ImageFamily favicon;
  base::FilePath profile_path;
  std::string profile_name;
};

enum ApplicationsMenuLocation {
  APP_MENU_LOCATION_NONE,
  APP_MENU_LOCATION_ROOT,
  APP_MENU_LOCATION_SUBDIR_CHROME,
  APP_MENU_LOCATION_SUBDIR_CHROMEAPPS,
  APP_MENU_LOCATION_HIDDEN,
};

struct ShortcutLocations {
  ShortcutLocations();

  bool on_desktop;

  ApplicationsMenuLocation applications_menu_location;

  
  
  
  
  bool in_quick_launch_bar;
};

enum ShortcutCreationReason {
  SHORTCUT_CREATION_BY_USER,
  SHORTCUT_CREATION_AUTOMATED,
};

typedef base::Callback<void(const ShortcutInfo&,
                            const extensions::FileHandlersInfo&)> InfoCallback;

typedef base::Callback<void(const ShortcutInfo&)> ShortcutInfoCallback;

#if defined(TOOLKIT_VIEWS)
void GetShortcutInfoForTab(content::WebContents* web_contents,
                           ShortcutInfo* info);
#endif

void UpdateShortcutForTabContents(content::WebContents* web_contents);

ShortcutInfo ShortcutInfoForExtensionAndProfile(
    const extensions::Extension* app,
    Profile* profile);

void GetInfoForApp(const extensions::Extension* extension,
                   Profile* profile,
                   const InfoCallback& callback);

void GetShortcutInfoForApp(const extensions::Extension* extension,
                           Profile* profile,
                           const ShortcutInfoCallback& callback);

bool ShouldCreateShortcutFor(Profile* profile,
                             const extensions::Extension* extension);

base::FilePath GetWebAppDataDirectory(const base::FilePath& profile_path,
                                      const std::string& extension_id,
                                      const GURL& url);

base::FilePath GetWebAppDataDirectory(const base::FilePath& profile_path,
                                      const extensions::Extension& extension);

std::string GenerateApplicationNameFromInfo(const ShortcutInfo& shortcut_info);

std::string GenerateApplicationNameFromURL(const GURL& url);

std::string GenerateApplicationNameFromExtensionId(const std::string& id);

std::string GetExtensionIdFromApplicationName(const std::string& app_name);

void CreateShortcutsWithInfo(
    ShortcutCreationReason reason,
    const ShortcutLocations& locations,
    const ShortcutInfo& shortcut_info,
    const extensions::FileHandlersInfo& file_handlers_info);

void CreateShortcuts(ShortcutCreationReason reason,
                     const ShortcutLocations& locations,
                     Profile* profile,
                     const extensions::Extension* app);

void DeleteAllShortcuts(Profile* profile, const extensions::Extension* app);

void UpdateAllShortcuts(const base::string16& old_app_title,
                        Profile* profile,
                        const extensions::Extension* app);

void UpdateShortcutsForAllApps(Profile* profile,
                               const base::Closure& callback);

bool IsValidUrl(const GURL& url);

#if defined(TOOLKIT_VIEWS)
typedef std::vector<WebApplicationInfo::IconInfo> IconInfoList;
void GetIconsInfo(const WebApplicationInfo& app_info, IconInfoList* icons);
#endif

#if defined(OS_LINUX)
std::string GetWMClassFromAppName(std::string app_name);
#endif

namespace internals {

#if defined(OS_WIN)
std::vector<base::FilePath> GetShortcutPaths(
    const ShortcutLocations& creation_locations);
#endif

bool CreatePlatformShortcuts(
    const base::FilePath& shortcut_data_path,
    const ShortcutInfo& shortcut_info,
    const extensions::FileHandlersInfo& file_handlers_info,
    const ShortcutLocations& creation_locations,
    ShortcutCreationReason creation_reason);

void DeletePlatformShortcuts(const base::FilePath& shortcut_data_path,
                             const ShortcutInfo& shortcut_info);

void UpdatePlatformShortcuts(
    const base::FilePath& shortcut_data_path,
    const base::string16& old_app_title,
    const ShortcutInfo& shortcut_info,
    const extensions::FileHandlersInfo& file_handlers_info);

void DeleteAllShortcutsForProfile(const base::FilePath& profile_path);

base::FilePath GetSanitizedFileName(const base::string16& name);

}  

}  

#endif  

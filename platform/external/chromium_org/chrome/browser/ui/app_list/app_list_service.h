// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_APP_LIST_SERVICE_H_
#define CHROME_BROWSER_UI_APP_LIST_APP_LIST_SERVICE_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/browser/ui/host_desktop.h"
#include "ui/gfx/native_widget_types.h"

class AppListControllerDelegate;
class PrefRegistrySimple;
class Profile;

namespace base {
class CommandLine;
class FilePath;
}

namespace gfx {
class ImageSkia;
}

class AppListService {
 public:
  
  
  
  enum AppListEnableSource {
    ENABLE_NOT_RECORDED,        
    ENABLE_FOR_APP_INSTALL,     
    ENABLE_VIA_WEBSTORE_LINK,   
    ENABLE_VIA_COMMAND_LINE,    
    ENABLE_ON_REINSTALL,        
    ENABLE_SHOWN_UNDISCOVERED,  
                                
                                
    ENABLE_NUM_ENABLE_SOURCES
  };

  
  
  static AppListService* Get(chrome::HostDesktopType desktop_type);

  
  static void InitAll(Profile* initial_profile);

  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  
  static bool HandleLaunchCommandLine(const base::CommandLine& command_line,
                                      Profile* launch_profile);

  
  
  virtual void SetAppListNextPaintCallback(void (*callback)()) = 0;

  
  
  virtual void HandleFirstRun() = 0;

  virtual base::FilePath GetProfilePath(
      const base::FilePath& user_data_dir) = 0;
  virtual void SetProfilePath(const base::FilePath& profile_path) = 0;

  
  
  virtual void Show() = 0;

  
  virtual void CreateForProfile(Profile* requested_profile) = 0;

  
  
  
  virtual void ShowForProfile(Profile* requested_profile) = 0;

  
  
  
  
  virtual void AutoShowForProfile(Profile* requested_profile) = 0;

  
  virtual void DismissAppList() = 0;

  
  virtual Profile* GetCurrentAppListProfile() = 0;

  
  virtual bool IsAppListVisible() const = 0;

  
  
  virtual void EnableAppList(Profile* initial_profile,
                             AppListEnableSource enable_source) = 0;

  
  virtual gfx::NativeWindow GetAppListWindow() = 0;

  
  virtual AppListControllerDelegate* GetControllerDelegate() = 0;

  
  virtual void CreateShortcut() = 0;

 protected:
  AppListService() {}
  virtual ~AppListService() {}

  
  virtual void Init(Profile* initial_profile) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(AppListService);
};

#endif  

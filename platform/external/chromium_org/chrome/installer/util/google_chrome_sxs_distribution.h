// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_GOOGLE_CHROME_SXS_DISTRIBUTION_H_
#define CHROME_INSTALLER_UTIL_GOOGLE_CHROME_SXS_DISTRIBUTION_H_

#include "base/strings/string16.h"
#include "chrome/installer/util/browser_distribution.h"
#include "chrome/installer/util/google_chrome_distribution.h"
#include "chrome/installer/util/l10n_string_util.h"
#include "chrome/installer/util/util_constants.h"

class GoogleChromeSxSDistribution : public GoogleChromeDistribution {
 public:
  virtual base::string16 GetBaseAppName() OVERRIDE;
  virtual base::string16 GetShortcutName(ShortcutType shortcut_type) OVERRIDE;
  virtual int GetIconIndex(ShortcutType shortcut_type) OVERRIDE;
  virtual base::string16 GetStartMenuShortcutSubfolder(
      Subfolder subfolder_type) OVERRIDE;
  virtual base::string16 GetBaseAppId() OVERRIDE;
  virtual base::string16 GetBrowserProgIdPrefix() OVERRIDE;
  virtual base::string16 GetBrowserProgIdDesc() OVERRIDE;
  virtual base::string16 GetInstallSubDir() OVERRIDE;
  virtual base::string16 GetUninstallRegPath() OVERRIDE;
  virtual DefaultBrowserControlPolicy GetDefaultBrowserControlPolicy() OVERRIDE;
  virtual bool GetChromeChannel(base::string16* channel) OVERRIDE;
  virtual bool GetCommandExecuteImplClsid(
      base::string16* handler_class_uuid) OVERRIDE;
  virtual bool AppHostIsSupported() OVERRIDE;
  virtual bool ShouldSetExperimentLabels() OVERRIDE;
  virtual bool HasUserExperiments() OVERRIDE;
  
  static base::string16 ChannelName();
 private:
  friend class BrowserDistribution;

  
  GoogleChromeSxSDistribution();
};

#endif  

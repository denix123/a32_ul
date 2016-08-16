// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ASSETS_MANAGER_CHROMEOS_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ASSETS_MANAGER_CHROMEOS_H_

#include <map>

#include "chrome/browser/extensions/extension_assets_manager.h"

template <typename T> struct DefaultSingletonTraits;
class PrefRegistrySimple;

namespace base {
class DictionaryValue;
class SequencedTaskRunner;
}

namespace extensions {

class ExtensionAssetsManagerChromeOS : public ExtensionAssetsManager {
 public:
  static ExtensionAssetsManagerChromeOS* GetInstance();

  
  static const char kSharedExtensions[];

  
  static const char kSharedExtensionPath[];

  
  static const char kSharedExtensionUsers[];

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  virtual void InstallExtension(const Extension* extension,
                                const base::FilePath& unpacked_extension_root,
                                const base::FilePath& local_install_dir,
                                Profile* profile,
                                InstallExtensionCallback callback) OVERRIDE;
  virtual void UninstallExtension(
      const std::string& id,
      Profile* profile,
      const base::FilePath& local_install_dir,
      const base::FilePath& extension_root) OVERRIDE;

  
  static base::FilePath GetSharedInstallDir();

  
  static bool IsSharedInstall(const Extension* extension);

  
  
  
  
  static bool CleanUpSharedExtensions(
      std::multimap<std::string, base::FilePath>* live_extension_paths);

  static void SetSharedInstallDirForTesting(const base::FilePath& install_dir);

 private:
  friend struct DefaultSingletonTraits<ExtensionAssetsManagerChromeOS>;

  ExtensionAssetsManagerChromeOS();
  virtual ~ExtensionAssetsManagerChromeOS();

  
  
  static base::SequencedTaskRunner* GetFileTaskRunner(Profile* profile);

  
  
  static bool CanShareAssets(const Extension* extension,
                             const base::FilePath& unpacked_extension_root);

  
  
  static void CheckSharedExtension(
      const std::string& id,
      const std::string& version,
      const base::FilePath& unpacked_extension_root,
      const base::FilePath& local_install_dir,
      Profile* profile,
      InstallExtensionCallback callback);

  
  static void InstallSharedExtension(
      const std::string& id,
      const std::string& version,
      const base::FilePath& unpacked_extension_root);

  
  static void InstallSharedExtensionDone(
      const std::string& id,
      const std::string& version,
      const base::FilePath& shared_version_dir);

  
  
  static void InstallLocalExtension(
      const std::string& id,
      const std::string& version,
      const base::FilePath& unpacked_extension_root,
      const base::FilePath& local_install_dir,
      InstallExtensionCallback callback);

  
  static void MarkSharedExtensionUnused(const std::string& id,
                                        Profile* profile);

  
  static void DeleteSharedVersion(const base::FilePath& shared_version_dir);

  
  static bool CleanUpExtension(
      const std::string& id,
      base::DictionaryValue* extension_info,
      std::multimap<std::string, base::FilePath>* live_extension_paths);

  DISALLOW_COPY_AND_ASSIGN(ExtensionAssetsManagerChromeOS);
};

}  

#endif  

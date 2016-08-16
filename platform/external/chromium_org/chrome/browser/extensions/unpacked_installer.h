// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_UNPACKED_INSTALLER_H_
#define CHROME_BROWSER_EXTENSIONS_UNPACKED_INSTALLER_H_

#include <string>
#include <vector>

#include "base/bind.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/extensions/extension_install_checker.h"

class ExtensionService;

namespace extensions {

class Extension;

class UnpackedInstaller
    : public base::RefCountedThreadSafe<UnpackedInstaller> {
 public:
  typedef base::Callback<void(const base::FilePath&, const std::string&)>
      OnFailureCallback;

  static scoped_refptr<UnpackedInstaller> Create(
      ExtensionService* extension_service);

  
  
  
  
  void Load(const base::FilePath& extension_path);

  
  
  
  
  
  
  
  bool LoadFromCommandLine(const base::FilePath& extension_path,
                           std::string* extension_id);

  
  bool prompt_for_plugins() { return prompt_for_plugins_; }
  void set_prompt_for_plugins(bool val) { prompt_for_plugins_ = val; }

  
  
  bool require_modern_manifest_version() const {
    return require_modern_manifest_version_;
  }
  void set_require_modern_manifest_version(bool val) {
    require_modern_manifest_version_ = val;
  }

  void set_be_noisy_on_failure(bool be_noisy_on_failure) {
    be_noisy_on_failure_ = be_noisy_on_failure;
  }

 private:
  friend class base::RefCountedThreadSafe<UnpackedInstaller>;

  explicit UnpackedInstaller(ExtensionService* extension_service);
  virtual ~UnpackedInstaller();

  
  void ShowInstallPrompt();

  
  void StartInstallChecks();

  
  void OnInstallChecksComplete(int failed_checks);

  
  bool IsLoadingUnpackedAllowed() const;

  
  
  
  
  
  
  
  void GetAbsolutePath();
  void CheckExtensionFileAccess();
  void LoadWithFileAccess(int flags);

  
  void UnregisterLoadRetryListener();

  
  void ReportExtensionLoadError(const std::string& error);

  
  void InstallExtension();

  
  int GetFlags();

  const Extension* extension() { return install_checker_.extension().get(); }

  
  base::WeakPtr<ExtensionService> service_weak_;

  
  
  base::FilePath extension_path_;

  
  
  bool prompt_for_plugins_;

  
  
  bool require_modern_manifest_version_;

  
  bool be_noisy_on_failure_;

  
  
  ExtensionInstallChecker install_checker_;

  DISALLOW_COPY_AND_ASSIGN(UnpackedInstaller);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_DEFAULT_COMPONENT_INSTALLER_H_
#define COMPONENTS_COMPONENT_UPDATER_DEFAULT_COMPONENT_INSTALLER_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/values.h"
#include "base/version.h"
#include "components/component_updater/component_updater_service.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
class SingleThreadTaskRunner;
}  

namespace component_updater {

class ComponentInstallerTraits {
 public:
  virtual ~ComponentInstallerTraits();

  
  
  
  
  
  virtual bool VerifyInstallation(const base::FilePath& dir) const = 0;

  
  
  virtual bool CanAutoUpdate() const = 0;

  
  
  
  
  virtual bool OnCustomInstall(const base::DictionaryValue& manifest,
                               const base::FilePath& install_dir) = 0;

  
  
  
  
  
  
  
  
  
  
  virtual void ComponentReady(const base::Version& version,
                              const base::FilePath& install_dir,
                              scoped_ptr<base::DictionaryValue> manifest) = 0;

  
  
  virtual base::FilePath GetBaseDirectory() const = 0;

  
  virtual void GetHash(std::vector<uint8_t>* hash) const = 0;

  
  virtual std::string GetName() const = 0;
};

class DefaultComponentInstaller : public ComponentInstaller {
 public:
  DefaultComponentInstaller(
      scoped_ptr<ComponentInstallerTraits> installer_traits);

  
  void Register(ComponentUpdateService* cus);

  
  virtual void OnUpdateError(int error) OVERRIDE;
  virtual bool Install(const base::DictionaryValue& manifest,
                       const base::FilePath& unpack_path) OVERRIDE;
  virtual bool GetInstalledFile(const std::string& file,
                                base::FilePath* installed_file) OVERRIDE;

  virtual ~DefaultComponentInstaller();

 private:
  base::FilePath GetInstallDirectory();
  bool InstallHelper(const base::DictionaryValue& manifest,
                     const base::FilePath& unpack_path,
                     const base::FilePath& install_path);
  void StartRegistration(ComponentUpdateService* cus);
  void FinishRegistration(ComponentUpdateService* cus);

  base::Version current_version_;
  std::string current_fingerprint_;
  scoped_ptr<base::DictionaryValue> current_manifest_;
  scoped_ptr<ComponentInstallerTraits> installer_traits_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  
  
  scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(DefaultComponentInstaller);
};

}  

#endif  

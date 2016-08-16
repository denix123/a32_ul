// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_COMPONENT_UPDATER_PNACL_PNACL_COMPONENT_INSTALLER_H_
#define CHROME_BROWSER_COMPONENT_UPDATER_PNACL_PNACL_COMPONENT_INSTALLER_H_

#include <list>
#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/version.h"
#include "components/component_updater/component_updater_service.h"

namespace base {
class DictionaryValue;
}

namespace pnacl {
bool NeedsOnDemandUpdate();
}

namespace component_updater {

class PnaclComponentInstaller : public ComponentInstaller {
 public:
  PnaclComponentInstaller();

  virtual ~PnaclComponentInstaller();

  virtual void OnUpdateError(int error) OVERRIDE;

  virtual bool Install(const base::DictionaryValue& manifest,
                       const base::FilePath& unpack_path) OVERRIDE;

  virtual bool GetInstalledFile(const std::string& file,
                                base::FilePath* installed_file) OVERRIDE;

  
  void RegisterPnaclComponent(ComponentUpdateService* cus);

  CrxComponent GetCrxComponent();

  
  base::FilePath GetPnaclBaseDirectory();

  base::Version current_version() const { return current_version_; }

  void set_current_version(const base::Version& current_version) {
    current_version_ = current_version;
  }

  std::string current_fingerprint() const { return current_fingerprint_; }

  void set_current_fingerprint(const std::string& current_fingerprint) {
    current_fingerprint_ = current_fingerprint;
  }

  ComponentUpdateService* cus() const { return cus_; }

 private:
  base::Version current_version_;
  std::string current_fingerprint_;
  ComponentUpdateService* cus_;
  DISALLOW_COPY_AND_ASSIGN(PnaclComponentInstaller);
};

}  

#endif  

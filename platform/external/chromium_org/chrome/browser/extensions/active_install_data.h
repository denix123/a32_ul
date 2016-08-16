// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_ACTIVE_INSTALL_DATA_H_
#define CHROME_BROWSER_EXTENSIONS_ACTIVE_INSTALL_DATA_H_

#include <string>

#include "base/macros.h"
#include "base/scoped_observer.h"
#include "chrome/browser/extensions/install_observer.h"

namespace extensions {

class InstallTracker;

struct ActiveInstallData {
 public:
  ActiveInstallData();
  explicit ActiveInstallData(const std::string& extension_id);

  std::string extension_id;
  int percent_downloaded;
  bool is_ephemeral;
};

class ScopedActiveInstall : public InstallObserver {
 public:
  
  ScopedActiveInstall(InstallTracker* tracker,
                      const ActiveInstallData& install_data);

  
  
  ScopedActiveInstall(InstallTracker* tracker, const std::string& extension_id);

  virtual ~ScopedActiveInstall();

  
  
  
  void CancelDeregister();

 private:
  void Init();

  
  virtual void OnShutdown() OVERRIDE;

  InstallTracker* tracker_;
  ScopedObserver<InstallTracker, InstallObserver> tracker_observer_;
  std::string extension_id_;

  DISALLOW_COPY_AND_ASSIGN(ScopedActiveInstall);
};

}  

#endif  

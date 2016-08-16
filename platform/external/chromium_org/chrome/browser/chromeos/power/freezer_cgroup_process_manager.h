// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POWER_FREEZER_CGROUP_PROCESS_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_POWER_FREEZER_CGROUP_PROCESS_MANAGER_H_

#include "base/files/file_path.h"
#include "base/macros.h"
#include "chrome/browser/chromeos/power/renderer_freezer.h"

namespace chromeos {

class FreezerCgroupProcessManager : public RendererFreezer::Delegate {
 public:
  FreezerCgroupProcessManager();
  virtual ~FreezerCgroupProcessManager();

  
  virtual bool FreezeRenderers() OVERRIDE;
  virtual bool ThawRenderers() OVERRIDE;
  virtual bool CanFreezeRenderers() OVERRIDE;

 private:
  bool WriteCommandToStateFile(const std::string& command);

  base::FilePath state_path_;
  bool enabled_;

  DISALLOW_COPY_AND_ASSIGN(FreezerCgroupProcessManager);
};

}  

#endif  

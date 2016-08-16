// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_EXTENSION_DATA_TYPE_CONTROLLER_H_
#define CHROME_BROWSER_SYNC_GLUE_EXTENSION_DATA_TYPE_CONTROLLER_H_

#include <string>

#include "base/compiler_specific.h"
#include "components/sync_driver/generic_change_processor.h"
#include "components/sync_driver/ui_data_type_controller.h"

class Profile;

namespace browser_sync {

class ExtensionDataTypeController : public sync_driver::UIDataTypeController {
 public:
  ExtensionDataTypeController(
      syncer::ModelType type,  
      sync_driver::SyncApiComponentFactory* sync_factory,
      Profile* profile);

 private:
  virtual ~ExtensionDataTypeController();

  
  virtual bool StartModels() OVERRIDE;

  Profile* const profile_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionDataTypeController);
};

}  

#endif  

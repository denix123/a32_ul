// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_AUTOFILL_DATA_TYPE_CONTROLLER_H__
#define CHROME_BROWSER_SYNC_GLUE_AUTOFILL_DATA_TYPE_CONTROLLER_H__

#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "components/sync_driver/non_ui_data_type_controller.h"

class Profile;
class ProfileSyncComponentsFactory;

namespace autofill {
class AutofillWebDataService;
}  

namespace browser_sync {

class AutofillDataTypeController
    : public sync_driver::NonUIDataTypeController {
 public:
  AutofillDataTypeController(
      ProfileSyncComponentsFactory* profile_sync_factory,
      Profile* profile);

  
  virtual syncer::ModelType type() const OVERRIDE;
  virtual syncer::ModelSafeGroup model_safe_group() const OVERRIDE;

  
  
  virtual void StartAssociating(const StartCallback& start_callback) OVERRIDE;

 protected:
  virtual ~AutofillDataTypeController();

  
  virtual bool PostTaskOnBackendThread(
      const tracked_objects::Location& from_here,
      const base::Closure& task) OVERRIDE;
  virtual bool StartModels() OVERRIDE;

 private:
  friend class AutofillDataTypeControllerTest;
  FRIEND_TEST_ALL_PREFIXES(AutofillDataTypeControllerTest, StartWDSReady);
  FRIEND_TEST_ALL_PREFIXES(AutofillDataTypeControllerTest, StartWDSNotReady);

  
  void WebDatabaseLoaded();

  Profile* const profile_;

  DISALLOW_COPY_AND_ASSIGN(AutofillDataTypeController);
};

}  

#endif  

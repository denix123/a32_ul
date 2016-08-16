// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_UPDATED_PROGRESS_MARKER_CHECKER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_UPDATED_PROGRESS_MARKER_CHECKER_H_

#include "chrome/browser/sync/test/integration/single_client_status_change_checker.h"

class UpdatedProgressMarkerChecker : public SingleClientStatusChangeChecker {
 public:
  explicit UpdatedProgressMarkerChecker(ProfileSyncService* service);
  virtual ~UpdatedProgressMarkerChecker();

  virtual bool IsExitConditionSatisfied() OVERRIDE;
  virtual std::string GetDebugMessage() const OVERRIDE;
};

#endif  

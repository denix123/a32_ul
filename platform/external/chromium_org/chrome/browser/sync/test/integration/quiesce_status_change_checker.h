// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_QUIESCE_STATUS_CHANGE_CHECKER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_QUIESCE_STATUS_CHANGE_CHECKER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"
#include "chrome/browser/sync/test/integration/status_change_checker.h"

class ProfileSyncService;
class ProgressMarkerWatcher;

class QuiesceStatusChangeChecker : public StatusChangeChecker {
 public:
  explicit QuiesceStatusChangeChecker(
      std::vector<ProfileSyncService*> services);
  virtual ~QuiesceStatusChangeChecker();

  
  void Wait();

  
  void OnServiceStateChanged(ProfileSyncService* service);

  
  virtual bool IsExitConditionSatisfied() OVERRIDE;
  virtual std::string GetDebugMessage() const OVERRIDE;

 private:
  std::vector<ProfileSyncService*> services_;
  ScopedVector<ProgressMarkerWatcher> observers_;

  DISALLOW_COPY_AND_ASSIGN(QuiesceStatusChangeChecker);
};

#endif  

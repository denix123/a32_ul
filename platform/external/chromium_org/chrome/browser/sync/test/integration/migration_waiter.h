// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_MIGRATION_WAITER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_MIGRATION_WAITER_H_

#include "base/macros.h"
#include "chrome/browser/sync/test/integration/status_change_checker.h"
#include "sync/internal_api/public/base/model_type.h"

class MigrationWatcher;

class MigrationWaiter : public StatusChangeChecker {
 public:
  
  
  MigrationWaiter(syncer::ModelTypeSet expected_types,
                  MigrationWatcher* watcher);

  virtual ~MigrationWaiter();

  
  virtual bool IsExitConditionSatisfied() OVERRIDE;
  virtual std::string GetDebugMessage() const OVERRIDE;

  
  void Wait();

  
  void OnMigrationStateChange();

 private:
  
  MigrationWatcher* const watcher_;

  
  const syncer::ModelTypeSet expected_types_;

  DISALLOW_COPY_AND_ASSIGN(MigrationWaiter);
};

#endif  

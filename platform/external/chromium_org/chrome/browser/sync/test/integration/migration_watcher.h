// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_MIGRATION_WATCHER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_MIGRATION_WATCHER_H_

#include "base/macros.h"
#include "chrome/browser/sync/backend_migrator.h"
#include "sync/internal_api/public/base/model_type.h"

class ProfileSyncServiceHarness;
class MigrationWaiter;

class MigrationWatcher : public browser_sync::MigrationObserver {
 public:
  explicit MigrationWatcher(ProfileSyncServiceHarness* harness);
  virtual ~MigrationWatcher();

  
  bool HasPendingBackendMigration() const;

  
  syncer::ModelTypeSet GetMigratedTypes() const;

  
  virtual void OnMigrationStateChange() OVERRIDE;

  
  void set_migration_waiter(MigrationWaiter* waiter);

  
  void clear_migration_waiter();

 private:
  
  ProfileSyncServiceHarness* const harness_;

  
  syncer::ModelTypeSet pending_types_;

  
  
  syncer::ModelTypeSet migrated_types_;

  
  MigrationWaiter* migration_waiter_;

  DISALLOW_COPY_AND_ASSIGN(MigrationWatcher);
};

#endif  

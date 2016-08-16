// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_SYNCED_NOTIFICATIONS_PRIVATE_SYNCED_NOTIFICATIONS_SHIM_H_
#define CHROME_BROWSER_EXTENSIONS_API_SYNCED_NOTIFICATIONS_PRIVATE_SYNCED_NOTIFICATIONS_SHIM_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/common/extensions/api/synced_notifications_private.h"
#include "sync/api/syncable_service.h"

namespace extensions {
struct Event;
}

class SyncedNotificationsShim : public syncer::SyncableService {
 public:
  
  typedef base::Callback<void(scoped_ptr<extensions::Event>)> EventLauncher;

  explicit SyncedNotificationsShim(const EventLauncher& event_launcher,
                                   const base::Closure& refresh_request);
  virtual ~SyncedNotificationsShim();

  
  virtual syncer::SyncMergeResult MergeDataAndStartSyncing(
      syncer::ModelType type,
      const syncer::SyncDataList& initial_sync_data,
      scoped_ptr<syncer::SyncChangeProcessor> sync_processor,
      scoped_ptr<syncer::SyncErrorFactory> error_handler) OVERRIDE;
  virtual void StopSyncing(syncer::ModelType type) OVERRIDE;
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(
      syncer::ModelType type) const OVERRIDE;

  
  bool GetInitialData(
      extensions::api::synced_notifications_private::SyncDataType data_type,
      std::vector<
          linked_ptr<extensions::api::synced_notifications_private::SyncData> >*
          js_data_list) const;
  bool UpdateNotification(const std::string& changed_notification);
  bool SetRenderContext(
      extensions::api::synced_notifications_private::RefreshRequest
          refresh_status,
      const std::string& new_context);

  
  bool IsSyncReady() const;

 private:
  
  EventLauncher event_launcher_;

  
  base::Closure refresh_request_;

  
  scoped_ptr<syncer::SyncChangeProcessor> notifications_change_processor_;
  scoped_ptr<syncer::SyncChangeProcessor> app_info_change_processor_;

  DISALLOW_COPY_AND_ASSIGN(SyncedNotificationsShim);
};

#endif  

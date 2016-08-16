// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_GET_UPDATES_DELEGATE_H_
#define SYNC_ENGINE_GET_UPDATES_DELEGATE_H_

#include "sync/internal_api/public/events/protocol_event.h"
#include "sync/protocol/sync.pb.h"
#include "sync/sessions/model_type_registry.h"
#include "sync/sessions/nudge_tracker.h"
#include "sync/sessions/status_controller.h"

namespace syncer {

class GetUpdatesProcessor;

class SYNC_EXPORT_PRIVATE GetUpdatesDelegate {
 public:
  GetUpdatesDelegate();
  virtual ~GetUpdatesDelegate() = 0;

  
  virtual void HelpPopulateGuMessage(
      sync_pb::GetUpdatesMessage* get_updates) const = 0;

  
  virtual void ApplyUpdates(
      ModelTypeSet gu_types,
      sessions::StatusController* status,
      UpdateHandlerMap* update_handler_map) const = 0;

  virtual scoped_ptr<ProtocolEvent> GetNetworkRequestEvent(
      base::Time timestamp,
      const sync_pb::ClientToServerMessage& request) const = 0;
};

class SYNC_EXPORT_PRIVATE NormalGetUpdatesDelegate : public GetUpdatesDelegate {
 public:
  NormalGetUpdatesDelegate(const sessions::NudgeTracker& nudge_tracker);
  virtual ~NormalGetUpdatesDelegate();

  
  virtual void HelpPopulateGuMessage(
      sync_pb::GetUpdatesMessage* get_updates) const OVERRIDE;

  
  virtual void ApplyUpdates(
      ModelTypeSet gu_types,
      sessions::StatusController* status,
      UpdateHandlerMap* update_handler_map) const OVERRIDE;

  virtual scoped_ptr<ProtocolEvent> GetNetworkRequestEvent(
      base::Time timestamp,
      const sync_pb::ClientToServerMessage& request) const OVERRIDE;
 private:
  DISALLOW_COPY_AND_ASSIGN(NormalGetUpdatesDelegate);

  const sessions::NudgeTracker& nudge_tracker_;
};

class SYNC_EXPORT_PRIVATE ConfigureGetUpdatesDelegate
    : public GetUpdatesDelegate {
 public:
  ConfigureGetUpdatesDelegate(
      sync_pb::GetUpdatesCallerInfo::GetUpdatesSource source);
  virtual ~ConfigureGetUpdatesDelegate();

  
  virtual void HelpPopulateGuMessage(
      sync_pb::GetUpdatesMessage* get_updates) const OVERRIDE;

  
  
  
  
  virtual void ApplyUpdates(
      ModelTypeSet gu_types,
      sessions::StatusController* status,
      UpdateHandlerMap* update_handler_map) const OVERRIDE;

  virtual scoped_ptr<ProtocolEvent> GetNetworkRequestEvent(
      base::Time timestamp,
      const sync_pb::ClientToServerMessage& request) const OVERRIDE;
 private:
  DISALLOW_COPY_AND_ASSIGN(ConfigureGetUpdatesDelegate);

  static sync_pb::SyncEnums::GetUpdatesOrigin ConvertConfigureSourceToOrigin(
      sync_pb::GetUpdatesCallerInfo::GetUpdatesSource source);

  const sync_pb::GetUpdatesCallerInfo::GetUpdatesSource source_;
};

class SYNC_EXPORT_PRIVATE PollGetUpdatesDelegate : public GetUpdatesDelegate {
 public:
  PollGetUpdatesDelegate();
  virtual ~PollGetUpdatesDelegate();

  
  virtual void HelpPopulateGuMessage(
      sync_pb::GetUpdatesMessage* get_updates) const OVERRIDE;

  
  virtual void ApplyUpdates(
      ModelTypeSet gu_types,
      sessions::StatusController* status,
      UpdateHandlerMap* update_handler_map) const OVERRIDE;

  virtual scoped_ptr<ProtocolEvent> GetNetworkRequestEvent(
      base::Time timestamp,
      const sync_pb::ClientToServerMessage& request) const OVERRIDE;
 private:
  DISALLOW_COPY_AND_ASSIGN(PollGetUpdatesDelegate);
};

}  

#endif   

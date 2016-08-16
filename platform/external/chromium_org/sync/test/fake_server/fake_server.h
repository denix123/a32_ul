// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_FAKE_SERVER_FAKE_SERVER_H_
#define SYNC_TEST_FAKE_SERVER_FAKE_SERVER_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/values.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/protocol/sync.pb.h"
#include "sync/test/fake_server/fake_server_entity.h"

namespace fake_server {

class FakeServer {
 public:
  typedef base::Callback<void(int, int, const std::string&)>
      HandleCommandCallback;

  class Observer {
   public:
    virtual ~Observer() {}

    
    
    virtual void OnCommit(
        const std::string& committer_id,
        syncer::ModelTypeSet committed_model_types) = 0;
  };

  FakeServer();
  virtual ~FakeServer();

  
  
  
  void HandleCommand(const std::string& request,
                     const HandleCommandCallback& callback);

  
  
  
  
  scoped_ptr<base::DictionaryValue> GetEntitiesAsDictionaryValue();

  
  
  
  void InjectEntity(scoped_ptr<FakeServerEntity> entity);

  
  
  
  bool SetNewStoreBirthday(const std::string& store_birthday);

  
  
  void SetAuthenticated();

  
  
  void SetUnauthenticated();

  
  void TriggerError(const sync_pb::SyncEnums::ErrorType& error_type);

  
  
  void AddObserver(Observer* observer);

  
  
  void RemoveObserver(Observer* observer);

 private:
  typedef std::map<std::string, FakeServerEntity*> EntityMap;

  
  bool HandleGetUpdatesRequest(const sync_pb::GetUpdatesMessage& get_updates,
                               sync_pb::GetUpdatesResponse* response);

  
  bool HandleCommitRequest(const sync_pb::CommitMessage& message,
                           const std::string& invalidator_client_id,
                           sync_pb::CommitResponse* response);

  
  bool CreateDefaultPermanentItems();

  
  bool CreateMobileBookmarksPermanentItem();

  
  void SaveEntity(FakeServerEntity* entity);

  
  
  
  
  
  std::string CommitEntity(
      const sync_pb::SyncEntity& client_entity,
      sync_pb::CommitResponse_EntryResponse* entry_response,
      std::string client_guid,
      std::string parent_id);

  
  
  void BuildEntryResponseForSuccessfulCommit(
      sync_pb::CommitResponse_EntryResponse* entry_response,
      FakeServerEntity* entity);

  
  
  bool IsChild(const std::string& id, const std::string& potential_parent_id);

  
  
  bool DeleteChildren(const std::string& id);

  
  
  int64 version_;

  
  std::string store_birthday_;

  
  
  bool authenticated_;

  
  
  EntityMap entities_;

  
  std::vector<std::string> keystore_keys_;

  sync_pb::SyncEnums::ErrorType error_type_;

  
  ObserverList<Observer, true> observers_;
};

}  

#endif  

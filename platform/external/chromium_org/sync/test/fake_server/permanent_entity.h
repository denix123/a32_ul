// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_FAKE_SERVER_PERMANENT_ENTITY_H_
#define SYNC_TEST_FAKE_SERVER_PERMANENT_ENTITY_H_

#include <string>

#include "base/basictypes.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/protocol/sync.pb.h"
#include "sync/test/fake_server/fake_server_entity.h"

namespace fake_server {

class PermanentEntity : public FakeServerEntity {
 public:
  virtual ~PermanentEntity();

  
  
  static FakeServerEntity* Create(const syncer::ModelType& model_type,
                                  const std::string& server_tag,
                                  const std::string& name,
                                  const std::string& parent_server_tag);

  
  
  static FakeServerEntity* CreateTopLevel(const syncer::ModelType& model_type);

  
  
  static FakeServerEntity* CreateUpdatedNigoriEntity(
      const sync_pb::SyncEntity& client_entity,
      FakeServerEntity* current_server_entity);

  
  virtual std::string GetParentId() const OVERRIDE;
  virtual void SerializeAsProto(sync_pb::SyncEntity* proto) OVERRIDE;
  virtual bool IsDeleted() const OVERRIDE;
  virtual bool IsFolder() const OVERRIDE;

 private:
  PermanentEntity(const std::string& id,
                  const syncer::ModelType& model_type,
                  const std::string& name,
                  const std::string& parent_id,
                  const std::string& server_defined_unique_tag,
                  const sync_pb::EntitySpecifics& entity_specifics);

  
  std::string server_defined_unique_tag_;
  std::string parent_id_;
  sync_pb::EntitySpecifics specifics_;
};

}  

#endif  

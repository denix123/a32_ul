// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_FAKE_SERVER_FAKE_SERVER_ENTITY_H_
#define SYNC_TEST_FAKE_SERVER_FAKE_SERVER_ENTITY_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/protocol/sync.pb.h"

namespace fake_server {

class FakeServerEntity {
 public:
  
  
  
  
  
  
  static std::string CreateId(const syncer::ModelType& model_type,
                              const std::string& inner_id);

  
  static std::string GetTopLevelId(const syncer::ModelType& model_type);

  virtual ~FakeServerEntity();
  const std::string& GetId() const;
  syncer::ModelType GetModelType() const;
  int64 GetVersion() const;
  void SetVersion(int64 version);
  const std::string& GetName() const;

  
  virtual std::string GetParentId() const = 0;
  virtual void SerializeAsProto(sync_pb::SyncEntity* proto) = 0;
  virtual bool IsDeleted() const = 0;
  virtual bool IsFolder() const = 0;

 protected:
  
  
  static syncer::ModelType GetModelTypeFromId(const std::string& id);

  FakeServerEntity(const std::string& id,
                   const syncer::ModelType& model_type,
                   int64 version,
                   const std::string& name);

  void SerializeBaseProtoFields(sync_pb::SyncEntity* sync_entity);

  
  syncer::ModelType model_type_;

 private:
  
  std::string id_;

  
  int64 version_;

  
  std::string name_;
};

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DEVICE_INFO_H_
#define COMPONENTS_SYNC_DRIVER_DEVICE_INFO_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "sync/protocol/sync.pb.h"

namespace base {
class DictionaryValue;
}

namespace sync_driver {

class DeviceInfo {
 public:
  DeviceInfo(const std::string& guid,
             const std::string& client_name,
             const std::string& chrome_version,
             const std::string& sync_user_agent,
             const sync_pb::SyncEnums::DeviceType device_type,
             const std::string& signin_scoped_device_id);
  ~DeviceInfo();

  
  
  
  
  const std::string& guid() const;

  
  const std::string& client_name() const;

  
  const std::string& chrome_version() const;

  
  
  
  const std::string& sync_user_agent() const;

  
  const std::string& public_id() const;

  
  sync_pb::SyncEnums::DeviceType device_type() const;

  
  
  const std::string& signin_scoped_device_id() const;

  
  std::string GetOSString() const;

  
  std::string GetDeviceTypeString() const;

  
  bool Equals(const DeviceInfo& other) const;

  
  
  
  
  void set_public_id(std::string id);

  
  
  base::DictionaryValue* ToValue();

 private:
  const std::string guid_;

  const std::string client_name_;

  const std::string chrome_version_;

  const std::string sync_user_agent_;

  const sync_pb::SyncEnums::DeviceType device_type_;

  std::string signin_scoped_device_id_;

  
  
  
  
  std::string public_id_;

  DISALLOW_COPY_AND_ASSIGN(DeviceInfo);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef EXTENSIONS_COMMON_PERMISSIONS_SOCKET_PERMISSION_DATA_H_
#define EXTENSIONS_COMMON_PERMISSIONS_SOCKET_PERMISSION_DATA_H_

#include <string>

#include "extensions/common/permissions/api_permission.h"
#include "extensions/common/permissions/socket_permission_entry.h"
#include "ipc/ipc_param_traits.h"

namespace ipc_fuzzer {
template <class T>
struct FuzzTraits;
template <class T>
struct GenerateTraits;
}  

namespace extensions {

class SocketPermissionData {
 public:
  SocketPermissionData();
  ~SocketPermissionData();

  
  
  bool operator<(const SocketPermissionData& rhs) const;
  bool operator==(const SocketPermissionData& rhs) const;

  
  
  bool Check(const APIPermission::CheckParam* param) const;

  
  scoped_ptr<base::Value> ToValue() const;

  
  bool FromValue(const base::Value* value);

  
  
  
  bool ParseForTest(const std::string& permission) { return Parse(permission); }
  const std::string& GetAsStringForTest() const { return GetAsString(); }

  const SocketPermissionEntry& entry() const { return entry_; }

 private:
  
  friend struct IPC::ParamTraits<SocketPermissionData>;
  friend struct ipc_fuzzer::FuzzTraits<SocketPermissionData>;
  friend struct ipc_fuzzer::GenerateTraits<SocketPermissionData>;

  SocketPermissionEntry& entry();

  bool Parse(const std::string& permission);
  const std::string& GetAsString() const;
  void Reset();

  SocketPermissionEntry entry_;
  mutable std::string spec_;
};

}  

#endif  

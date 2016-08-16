// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_API_BLUETOOTH_BLUETOOTH_MANIFEST_DATA_H_
#define EXTENSIONS_COMMON_API_BLUETOOTH_BLUETOOTH_MANIFEST_DATA_H_

#include <vector>

#include "base/strings/string16.h"
#include "extensions/common/extension.h"
#include "extensions/common/manifest_handler.h"

namespace extensions {
class BluetoothManifestPermission;
struct BluetoothPermissionRequest;
}

namespace extensions {

class BluetoothManifestData : public Extension::ManifestData {
 public:
  explicit BluetoothManifestData(
      scoped_ptr<BluetoothManifestPermission> permission);
  virtual ~BluetoothManifestData();

  
  
  static BluetoothManifestData* Get(const Extension* extension);

  static bool CheckRequest(const Extension* extension,
                           const BluetoothPermissionRequest& request);

  static bool CheckSocketPermitted(const Extension* extension);
  static bool CheckLowEnergyPermitted(const Extension* extension);

  
  
  static scoped_ptr<BluetoothManifestData> FromValue(const base::Value& value,
                                                     base::string16* error);

  const BluetoothManifestPermission* permission() const {
    return permission_.get();
  }

 private:
  scoped_ptr<BluetoothManifestPermission> permission_;
};

struct BluetoothPermissionRequest {
  explicit BluetoothPermissionRequest(const std::string& uuid);
  ~BluetoothPermissionRequest();

  std::string uuid;
};

}  

#endif  

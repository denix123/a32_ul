// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef EXTENSIONS_COMMON_PERMISSIONS_USB_DEVICE_PERMISSION_DATA_H_
#define EXTENSIONS_COMMON_PERMISSIONS_USB_DEVICE_PERMISSION_DATA_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/common/permissions/api_permission.h"

namespace base {

class Value;

}  

namespace extensions {

class UsbDevicePermissionData {
 public:
  enum SpecialInterfaces {
    
    
    
    ANY_INTERFACE = -1,

    
    
    UNSPECIFIED_INTERFACE = -2
  };

  UsbDevicePermissionData();
  UsbDevicePermissionData(uint16 vendor_id,
                          uint16 product_id,
                          int interface_id);

  
  
  bool Check(const APIPermission::CheckParam* param) const;

  
  scoped_ptr<base::Value> ToValue() const;

  
  bool FromValue(const base::Value* value);

  bool operator<(const UsbDevicePermissionData& rhs) const;
  bool operator==(const UsbDevicePermissionData& rhs) const;

  const uint16& vendor_id() const { return vendor_id_; }
  const uint16& product_id() const { return product_id_; }

  
  
  uint16& vendor_id() { return vendor_id_; }
  uint16& product_id() { return product_id_; }

 private:
  uint16 vendor_id_;
  uint16 product_id_;
  int interface_id_;
};

}  

#endif  

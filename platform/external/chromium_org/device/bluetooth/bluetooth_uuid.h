// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_UUID_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_UUID_H_

#include <string>

namespace device {

class BluetoothUUID {
 public:
  
  enum Format {
    kFormatInvalid,
    kFormat16Bit,
    kFormat32Bit,
    kFormat128Bit
  };

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  explicit BluetoothUUID(const std::string& uuid);

  
  
  
  
  BluetoothUUID();
  virtual ~BluetoothUUID();

  
  bool IsValid() const;

  
  
  Format format() const { return format_; }

  
  
  
  
  
  
  
  const std::string& value() const { return value_; }

  
  
  
  const std::string& canonical_value() const { return canonical_value_; }

  
  
  bool operator<(const BluetoothUUID& uuid) const;

  
  bool operator==(const BluetoothUUID& uuid) const;
  bool operator!=(const BluetoothUUID& uuid) const;

 private:
  
  
  
  
  
  Format format_;
  std::string value_;

  
  std::string canonical_value_;
};

void PrintTo(const BluetoothUUID& uuid, std::ostream* out);

}  

#endif  

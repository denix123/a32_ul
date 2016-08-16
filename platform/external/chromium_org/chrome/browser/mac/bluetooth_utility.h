// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MAC_BLUETOOTH_UTILITY_H_
#define CHROME_BROWSER_MAC_BLUETOOTH_UTILITY_H_

namespace bluetooth_utility {

enum BluetoothAvailability {
  BLUETOOTH_AVAILABILITY_ERROR = 0,  
  BLUETOOTH_NOT_AVAILABLE = 1,
  BLUETOOTH_AVAILABLE_WITHOUT_LE = 2,
  BLUETOOTH_AVAILABLE_WITH_LE = 3,

  
  
  BLUETOOTH_AVAILABLE_LE_UNKNOWN = 4,
  BLUETOOTH_AVAILABILITY_COUNT,
};

BluetoothAvailability GetBluetoothAvailability();

}  

#endif  

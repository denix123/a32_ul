// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_USB_USB_ERROR_H_
#define DEVICE_USB_USB_ERROR_H_

#include <string>

namespace device {

std::string ConvertPlatformUsbErrorToString(int errcode);

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_IOS_DEVICE_UTIL_H_
#define BASE_IOS_DEVICE_UTIL_H_

#include <string>

namespace ios {
namespace device_util {

std::string GetPlatform();

bool RamIsAtLeast512Mb();

bool RamIsAtLeast1024Mb();

bool RamIsAtLeast(uint64_t ram_in_mb);

bool IsSingleCoreDevice();

std::string GetMacAddress(const std::string& interface_name);

std::string GetRandomId();

std::string GetDeviceIdentifier(const char* salt);

std::string GetSaltedString(const std::string& in_string,
                            const std::string& salt);

}  
}  

#endif  

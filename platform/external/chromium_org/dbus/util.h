// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DBUS_UTIL_H_
#define DBUS_UTIL_H_

#include <string>

#include "dbus/dbus_export.h"

namespace dbus {

CHROME_DBUS_EXPORT std::string GetAbsoluteMemberName(
    const std::string& interface_name,
    const std::string& member_name);

}  

#endif  

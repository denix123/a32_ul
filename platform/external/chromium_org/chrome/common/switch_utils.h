// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_SWITCH_UTILS_H_
#define CHROME_COMMON_SWITCH_UTILS_H_

#include <map>
#include <string>

#include "base/command_line.h"

namespace switches {

void RemoveSwitchesForAutostart(
    std::map<std::string, base::CommandLine::StringType>* switches);

}  

#endif  
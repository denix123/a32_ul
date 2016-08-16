// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_INVALIDATION_SERVICE_UTIL_H_
#define COMPONENTS_INVALIDATION_INVALIDATION_SERVICE_UTIL_H_

#include "jingle/notifier/base/notifier_options.h"

namespace base {
class CommandLine;
}

namespace invalidation {

notifier::NotifierOptions ParseNotifierOptions(
    const base::CommandLine& command_line);

std::string GenerateInvalidatorClientId();

}  

#endif  

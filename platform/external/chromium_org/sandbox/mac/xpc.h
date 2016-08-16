// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef SANDBOX_MAC_XPC_H_
#define SANDBOX_MAC_XPC_H_

#include <AvailabilityMacros.h>
#include <mach/mach.h>

#include "sandbox/sandbox_export.h"

#include "sandbox/mac/xpc_stubs_header.fragment"

#if !defined(MAC_OS_X_VERSION_10_7) || \
    MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_7

#include "sandbox/mac/xpc_stubs.h"

extern "C" {
#include "sandbox/mac/xpc_stubs.sig"
#include "sandbox/mac/xpc_private_stubs.sig"
}  

#else

extern "C" {
#include "sandbox/mac/xpc_private_stubs.sig"
}  

#endif

namespace sandbox {

bool SANDBOX_EXPORT InitializeXPC();

}  

#endif  

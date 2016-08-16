// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_BACKOFF_POLICY_H_
#define COMPONENTS_GCM_DRIVER_GCM_BACKOFF_POLICY_H_

#include "net/base/backoff_entry.h"

namespace gcm {

const net::BackoffEntry::Policy& GetGCMBackoffPolicy();

}  

#endif  

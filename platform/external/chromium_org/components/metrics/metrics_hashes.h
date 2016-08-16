// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_METRICS_HASHES_H_
#define COMPONENTS_METRICS_METRICS_HASHES_H_

#include <string>

#include "base/basictypes.h"

namespace metrics {

uint64 HashMetricName(const std::string& name);

}  

#endif  

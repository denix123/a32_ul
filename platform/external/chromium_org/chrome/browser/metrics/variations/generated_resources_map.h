// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_VARIATIONS_GENERATED_RESOURCES_MAP_H_
#define CHROME_BROWSER_METRICS_VARIATIONS_GENERATED_RESOURCES_MAP_H_

#include "base/basictypes.h"

namespace chrome_variations {



extern const size_t kNumResources;

extern const uint32_t kResourceHashes[];

extern const int kResourceIndices[];

int GetResourceIndex(uint32_t hash);

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_CONFIG_GPU_UTIL_H_
#define GPU_CONFIG_GPU_UTIL_H_

#include <set>
#include <string>

#include "base/command_line.h"
#include "build/build_config.h"
#include "gpu/gpu_export.h"

namespace base {
class CommandLine;
}

namespace gpu {

struct GPUInfo;

GPU_EXPORT void MergeFeatureSets(
    std::set<int>* dst, const std::set<int>& src);

GPU_EXPORT void ApplyGpuDriverBugWorkarounds(base::CommandLine* command_line);

GPU_EXPORT void ApplyGpuDriverBugWorkarounds(
    const GPUInfo& gpu_inco, base::CommandLine* command_line);

GPU_EXPORT void StringToFeatureSet(
    const std::string& str, std::set<int>* feature_set);

}  

#endif  


// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_CONFIG_GPU_INFO_COLLECTOR_H_
#define GPU_CONFIG_GPU_INFO_COLLECTOR_H_

#include "base/basictypes.h"
#include "build/build_config.h"
#include "gpu/config/gpu_info.h"
#include "gpu/gpu_export.h"

namespace gpu {

GPU_EXPORT CollectInfoResult CollectGpuID(uint32* vendor_id, uint32* device_id);

GPU_EXPORT CollectInfoResult CollectBasicGraphicsInfo(GPUInfo* gpu_info);

GPU_EXPORT CollectInfoResult CollectContextGraphicsInfo(GPUInfo* gpu_info);

#if defined(OS_WIN)
GPU_EXPORT bool GetDxDiagnostics(DxDiagNode* output);
#endif  

GPU_EXPORT CollectInfoResult CollectGraphicsInfoGL(GPUInfo* gpu_info);

GPU_EXPORT CollectInfoResult CollectDriverInfoGL(GPUInfo* gpu_info);

GPU_EXPORT void MergeGPUInfo(GPUInfo* basic_gpu_info,
                             const GPUInfo& context_gpu_info);

GPU_EXPORT void MergeGPUInfoGL(GPUInfo* basic_gpu_info,
                               const GPUInfo& context_gpu_info);

}  

#endif  

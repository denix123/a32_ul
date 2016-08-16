// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_GPU_GPU_METRICS_PROVIDER_H_
#define COMPONENTS_METRICS_GPU_GPU_METRICS_PROVIDER_H_

#include "base/basictypes.h"
#include "components/metrics/metrics_provider.h"
#include "ui/gfx/size.h"

namespace metrics {

class GPUMetricsProvider : public MetricsProvider {
 public:
  GPUMetricsProvider();
  virtual ~GPUMetricsProvider();

  
  virtual void ProvideSystemProfileMetrics(
      SystemProfileProto* system_profile_proto) OVERRIDE;

 protected:
  

  
  virtual gfx::Size GetScreenSize() const;

  
  virtual float GetScreenDeviceScaleFactor() const;

  
  virtual int GetScreenCount() const;

 private:
  DISALLOW_COPY_AND_ASSIGN(GPUMetricsProvider);
};

}  

#endif  

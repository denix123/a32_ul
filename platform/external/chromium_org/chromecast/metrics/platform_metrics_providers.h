// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_METRICS_PLATFORM_METRICS_PROVIDERS_H_
#define CHROMECAST_METRICS_PLATFORM_METRICS_PROVIDERS_H_

#include "components/metrics/proto/system_profile.pb.h"

namespace metrics {
class MetricsService;
}

namespace chromecast {
namespace metrics {

void RegisterPlatformMetricsProviders(
    ::metrics::MetricsService* metrics_service);

::metrics::SystemProfileProto::Channel GetPlatformReleaseChannel();

std::string GetPlatformVersionString();

bool PlatformIsReportingEnabled();

void PlatformSetClientID(const std::string& client_id);

void PlatformOnLogUploadComplete();

}  
}  

#endif  

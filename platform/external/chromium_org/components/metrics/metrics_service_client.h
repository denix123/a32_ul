// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_METRICS_SERVICE_CLIENT_H_
#define COMPONENTS_METRICS_METRICS_SERVICE_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/metrics/proto/system_profile.pb.h"

namespace metrics {

class MetricsLogUploader;

class MetricsServiceClient {
 public:
  virtual ~MetricsServiceClient() {}

  
  
  virtual void SetMetricsClientId(const std::string& client_id) = 0;

  
  virtual bool IsOffTheRecordSessionActive() = 0;

  
  virtual std::string GetApplicationLocale() = 0;

  
  
  virtual bool GetBrand(std::string* brand_code) = 0;

  
  virtual SystemProfileProto::Channel GetChannel() = 0;

  
  virtual std::string GetVersionString() = 0;

  
  virtual void OnLogUploadComplete() = 0;

  
  
  virtual void StartGatheringMetrics(const base::Closure& done_callback) = 0;

  
  
  
  virtual void CollectFinalMetrics(const base::Closure& done_callback) = 0;

  
  
  virtual scoped_ptr<MetricsLogUploader> CreateUploader(
      const std::string& server_url,
      const std::string& mime_type,
      const base::Callback<void(int)>& on_upload_complete) = 0;

  
  
  virtual base::string16 GetRegistryBackupKey();
};

}  

#endif  

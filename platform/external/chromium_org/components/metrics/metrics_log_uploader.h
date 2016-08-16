// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_METRICS_LOG_UPLOADER_H_
#define COMPONENTS_METRICS_METRICS_LOG_UPLOADER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/macros.h"

namespace metrics {

class MetricsLogUploader {
 public:
  
  
  
  MetricsLogUploader(const std::string& server_url,
                     const std::string& mime_type,
                     const base::Callback<void(int)>& on_upload_complete);
  virtual ~MetricsLogUploader();

  
  
  
  virtual bool UploadLog(const std::string& compressed_log_data,
                         const std::string& log_hash) = 0;

 protected:
  const std::string server_url_;
  const std::string mime_type_;
  const base::Callback<void(int)> on_upload_complete_;

 private:
  DISALLOW_COPY_AND_ASSIGN(MetricsLogUploader);
};

}  

#endif  

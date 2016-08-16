// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_REPORT_UPLOADER_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_REPORT_UPLOADER_H_

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"

namespace safe_browsing {

class ClientIncidentResponse;

class IncidentReportUploader {
 public:
  
  
  enum Result {
    UPLOAD_SUCCESS = 0,           
    UPLOAD_SUPPRESSED = 1,        
    UPLOAD_INVALID_REQUEST = 2,   
    UPLOAD_CANCELLED = 3,         
    UPLOAD_REQUEST_FAILED = 4,    
    UPLOAD_INVALID_RESPONSE = 5,  
    UPLOAD_NO_DOWNLOAD = 6,       
    NUM_UPLOAD_RESULTS
  };

  
  
  
  typedef base::Callback<void(Result, scoped_ptr<ClientIncidentResponse>)>
      OnResultCallback;

  virtual ~IncidentReportUploader();

 protected:
  explicit IncidentReportUploader(const OnResultCallback& callback);

  
  OnResultCallback callback_;
};

}  

#endif  

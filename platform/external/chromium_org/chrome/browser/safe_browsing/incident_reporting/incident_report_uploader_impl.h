// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_REPORT_UPLOADER_IMPL_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_INCIDENT_REPORT_UPLOADER_IMPL_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "chrome/browser/safe_browsing/incident_reporting/incident_report_uploader.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}  

namespace safe_browsing {

class ClientIncidentReport;

class IncidentReportUploaderImpl : public IncidentReportUploader,
                                   public net::URLFetcherDelegate {
 public:
  
  static const int kTestUrlFetcherId;

  virtual ~IncidentReportUploaderImpl();

  
  
  
  static scoped_ptr<IncidentReportUploader> UploadReport(
      const OnResultCallback& callback,
      const scoped_refptr<net::URLRequestContextGetter>& request_context_getter,
      const ClientIncidentReport& report);

 private:
  IncidentReportUploaderImpl(
      const OnResultCallback& callback,
      const scoped_refptr<net::URLRequestContextGetter>& request_context_getter,
      const std::string& post_data);

  
  static GURL GetIncidentReportUrl();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  
  scoped_ptr<net::URLFetcher> url_fetcher_;

  
  base::TimeTicks time_begin_;

  DISALLOW_COPY_AND_ASSIGN(IncidentReportUploaderImpl);
};

}  

#endif  

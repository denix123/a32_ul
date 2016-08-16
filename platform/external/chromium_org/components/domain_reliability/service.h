// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_SERVICE_H_
#define COMPONENTS_DOMAIN_RELIABILITY_SERVICE_H_

#include <string>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/single_thread_task_runner.h"
#include "components/domain_reliability/clear_mode.h"
#include "components/domain_reliability/domain_reliability_export.h"
#include "components/keyed_service/core/keyed_service.h"

class PrefService;

namespace base {
class Value;
}  

namespace net {
class URLRequestContextGetter;
}  

namespace domain_reliability {

class DomainReliabilityMonitor;

class DOMAIN_RELIABILITY_EXPORT DomainReliabilityService
    : public KeyedService {
 public:
  
  
  static DomainReliabilityService* Create(
      const std::string& upload_reporter_string);

  virtual ~DomainReliabilityService();

  
  
  
  
  
  virtual scoped_ptr<DomainReliabilityMonitor> CreateMonitor(
      scoped_refptr<base::SingleThreadTaskRunner> network_task_runner) = 0;

  
  
  virtual void ClearBrowsingData(DomainReliabilityClearMode clear_mode,
                                 const base::Closure& callback) = 0;

  virtual void GetWebUIData(
      const base::Callback<void(scoped_ptr<base::Value>)>& callback)
      const = 0;

 protected:
  DomainReliabilityService();

 private:
  DISALLOW_COPY_AND_ASSIGN(DomainReliabilityService);
};

}  

#endif  

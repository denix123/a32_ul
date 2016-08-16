// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_PUBLIC_COPRESENCE_MANAGER_H_
#define COMPONENTS_COPRESENCE_PUBLIC_COPRESENCE_MANAGER_H_

#include "base/memory/scoped_ptr.h"
#include "components/copresence/public/copresence_delegate.h"

namespace copresence {

class ReportRequest;

class CopresenceManager {
 public:
  CopresenceManager() {}
  virtual ~CopresenceManager() {}

  
  
  
  
  
  virtual void ExecuteReportRequest(ReportRequest request,
                                    const std::string& app_id,
                                    const StatusCallback& callback) = 0;

  
  
  static scoped_ptr<CopresenceManager> Create(CopresenceDelegate* delegate);

 private:

  DISALLOW_COPY_AND_ASSIGN(CopresenceManager);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_CLIENT_INFO_H_
#define COMPONENTS_METRICS_CLIENT_INFO_H_

#include <string>

#include "base/basictypes.h"
#include "base/macros.h"

namespace metrics {

struct ClientInfo {
 public:
  ClientInfo();
  ~ClientInfo();

  
  std::string client_id;

  
  int64 installation_date;

  
  
  int64 reporting_enabled_date;

 private:
  DISALLOW_COPY_AND_ASSIGN(ClientInfo);
};

}  

#endif  

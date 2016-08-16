// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMAHA_QUERY_PARAMS_OMAHA_QUERY_PARAMS_DELEGATE_H_
#define COMPONENTS_OMAHA_QUERY_PARAMS_OMAHA_QUERY_PARAMS_DELEGATE_H_

#include <string>

#include "base/basictypes.h"

namespace omaha_query_params {

class OmahaQueryParamsDelegate {
 public:
  OmahaQueryParamsDelegate();
  virtual ~OmahaQueryParamsDelegate();

  
  
  virtual std::string GetExtraParams() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(OmahaQueryParamsDelegate);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMAHA_QUERY_PARAMS_OMAHA_QUERY_PARAMS_H_
#define COMPONENTS_OMAHA_QUERY_PARAMS_OMAHA_QUERY_PARAMS_H_

#include <string>

#include "base/basictypes.h"

namespace omaha_query_params {

class OmahaQueryParamsDelegate;

class OmahaQueryParams {
 public:
  enum ProdId {
    CHROME = 0,
    CRX,
  };

  
  
  
  static std::string Get(ProdId prod);

  
  
  static const char* GetProdIdString(ProdId prod);

  
  
  static const char* GetOS();

  
  
  static const char* GetArch();

  
  
  
  
  static const char* GetNaclArch();

  
  static void SetDelegate(OmahaQueryParamsDelegate* delegate);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(OmahaQueryParams);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_CONFIGURATOR_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_CONFIGURATOR_H_

#include <string>

#include "base/macros.h"

namespace data_reduction_proxy {

class DataReductionProxyConfigurator {
 public:
  DataReductionProxyConfigurator() {}
  virtual ~DataReductionProxyConfigurator() {}

  
  
  
  
  
  virtual void Enable(bool primary_restricted,
                      bool fallback_restricted,
                      const std::string& primary_origin,
                      const std::string& fallback_origin,
                      const std::string& ssl_origin) = 0;

  
  virtual void Disable() = 0;

  
  
  
  
  
  virtual void AddHostPatternToBypass(const std::string& pattern) = 0;

  
  
  
  virtual void AddURLPatternToBypass(const std::string& pattern) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyConfigurator);
};

}  

#endif  

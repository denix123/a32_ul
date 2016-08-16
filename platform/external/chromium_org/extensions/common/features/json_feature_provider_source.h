// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_FEATURES_JSON_FEATURE_PROVIDER_SOURCE_H_
#define EXTENSIONS_COMMON_FEATURES_JSON_FEATURE_PROVIDER_SOURCE_H_

#include <string>

#include "base/values.h"

namespace extensions {

class JSONFeatureProviderSource {
 public:
  explicit JSONFeatureProviderSource(const std::string& name);
  ~JSONFeatureProviderSource();

  
  
  void LoadJSON(int resource_id);

  
  const base::DictionaryValue& dictionary() { return dictionary_; }

 private:
  
  const std::string name_;

  base::DictionaryValue dictionary_;

  DISALLOW_COPY_AND_ASSIGN(JSONFeatureProviderSource);
};

}  

#endif  

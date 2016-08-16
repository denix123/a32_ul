// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_FEATURES_SIMPLE_FEATURE_FILTER_H_
#define EXTENSIONS_COMMON_FEATURES_SIMPLE_FEATURE_FILTER_H_

#include <string>

#include "extensions/common/features/feature.h"
#include "extensions/common/manifest.h"

class GURL;

namespace base {
class DictionaryValue;
}

namespace extensions {

class SimpleFeature;

class SimpleFeatureFilter {
 public:
  explicit SimpleFeatureFilter(SimpleFeature* feature);
  virtual ~SimpleFeatureFilter();

  SimpleFeature* feature() const { return feature_; }

  
  
  
  virtual std::string Parse(const base::DictionaryValue* value);

  
  
  virtual Feature::Availability IsAvailableToContext(
      const Extension* extension,
      Feature::Context context,
      const GURL& url,
      Feature::Platform platform) const;

  
  
  virtual Feature::Availability IsAvailableToManifest(
      const std::string& extension_id,
      Manifest::Type type,
      Manifest::Location location,
      int manifest_version,
      Feature::Platform platform) const;

 private:
  
  SimpleFeature* feature_;

  DISALLOW_COPY_AND_ASSIGN(SimpleFeatureFilter);
};

}  

#endif  

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_FEATURES_FEATURE_PROVIDER_H_
#define EXTENSIONS_COMMON_FEATURES_FEATURE_PROVIDER_H_

#include <string>
#include <vector>

namespace extensions {

class Feature;

class FeatureProvider {
 public:
  FeatureProvider() {}
  virtual ~FeatureProvider() {}

  
  virtual Feature* GetFeature(const std::string& name) const = 0;

  
  virtual Feature* GetParent(Feature* feature) const = 0;

  
  virtual std::vector<Feature*> GetChildren(const Feature& parent) const = 0;

  
  virtual const std::vector<std::string>& GetAllFeatureNames() const = 0;

  
  static const FeatureProvider* GetByName(const std::string& name);

  
  static const FeatureProvider* GetAPIFeatures();
  static const FeatureProvider* GetManifestFeatures();
  static const FeatureProvider* GetPermissionFeatures();
};

}  

#endif  

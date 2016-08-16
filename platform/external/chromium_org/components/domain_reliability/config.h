// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_CONFIG_H_
#define COMPONENTS_DOMAIN_RELIABILITY_CONFIG_H_

#include <string>
#include <vector>

#include "base/json/json_value_converter.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "base/time/time.h"
#include "base/values.h"
#include "components/domain_reliability/domain_reliability_export.h"
#include "url/gurl.h"

namespace domain_reliability {

class DOMAIN_RELIABILITY_EXPORT DomainReliabilityConfig {
 public:
  static const size_t kInvalidResourceIndex;

  
  
  
  class DOMAIN_RELIABILITY_EXPORT Resource {
   public:
    Resource();
    ~Resource();

    
    
    bool MatchesUrl(const GURL& url) const;

    
    
    
    bool DecideIfShouldReportRequest(bool success) const;

    
    
    static void RegisterJSONConverter(
        base::JSONValueConverter<Resource>* converter);

    bool IsValid() const;

    
    std::string name;

    
    ScopedVector<std::string> url_patterns;

    
    
    double success_sample_rate;
    double failure_sample_rate;

   private:
    DISALLOW_COPY_AND_ASSIGN(Resource);
  };

  
  
  
  struct DOMAIN_RELIABILITY_EXPORT Collector {
   public:
    Collector();
    ~Collector();

    
    
    static void RegisterJSONConverter(
        base::JSONValueConverter<Collector>* converter);

    bool IsValid() const;

    GURL upload_url;

   private:
    DISALLOW_COPY_AND_ASSIGN(Collector);
  };

  DomainReliabilityConfig();
  ~DomainReliabilityConfig();

  
  static scoped_ptr<const DomainReliabilityConfig> FromJSON(
      const base::StringPiece& json);

  bool IsValid() const;

  
  bool IsExpired(base::Time now) const;

  
  
  
  size_t GetResourceIndexForUrl(const GURL& url) const;

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<DomainReliabilityConfig>* converter);

  std::string version;
  double valid_until;
  std::string domain;
  ScopedVector<Resource> resources;
  ScopedVector<Collector> collectors;

 private:
  DISALLOW_COPY_AND_ASSIGN(DomainReliabilityConfig);
};

}  

#endif  

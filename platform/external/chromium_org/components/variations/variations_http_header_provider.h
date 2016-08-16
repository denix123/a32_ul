// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_VARIATIONS_VARIATIONS_HTTP_HEADER_PROVIDER_H_
#define COMPONENTS_VARIATIONS_VARIATIONS_HTTP_HEADER_PROVIDER_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/metrics/field_trial.h"
#include "base/synchronization/lock.h"
#include "components/variations/variations_associated_data.h"

namespace content {
class ResourceContext;
}

namespace net {
class HttpRequestHeaders;
}

class GURL;

template <typename T> struct DefaultSingletonTraits;

namespace variations {

class VariationsHttpHeaderProvider : base::FieldTrialList::Observer {
 public:
  static VariationsHttpHeaderProvider* GetInstance();

  
  
  
  
  void AppendHeaders(const GURL& url,
                     bool incognito,
                     bool uma_enabled,
                     net::HttpRequestHeaders* headers);

  
  
  
  
  
  bool SetDefaultVariationIds(const std::string& variation_ids);

 private:
  friend struct DefaultSingletonTraits<VariationsHttpHeaderProvider>;

  FRIEND_TEST_ALL_PREFIXES(VariationsHttpHeaderProviderTest,
                           ShouldAppendHeaders);
  FRIEND_TEST_ALL_PREFIXES(VariationsHttpHeaderProviderTest,
                           SetDefaultVariationIds_Valid);
  FRIEND_TEST_ALL_PREFIXES(VariationsHttpHeaderProviderTest,
                           SetDefaultVariationIds_Invalid);
  FRIEND_TEST_ALL_PREFIXES(VariationsHttpHeaderProviderTest,
                           OnFieldTrialGroupFinalized);

  VariationsHttpHeaderProvider();
  virtual ~VariationsHttpHeaderProvider();

  
  
  
  virtual void OnFieldTrialGroupFinalized(
      const std::string& trial_name,
      const std::string& group_name) OVERRIDE;

  
  
  
  void InitVariationIDsCacheIfNeeded();

  
  
  
  void UpdateVariationIDsHeaderValue();

  
  
  static bool ShouldAppendHeaders(const GURL& url);

  
  
  base::Lock lock_;

  
  bool variation_ids_cache_initialized_;

  
  
  std::set<VariationID> variation_ids_set_;
  std::set<VariationID> variation_trigger_ids_set_;

  
  std::set<VariationID> default_variation_ids_set_;
  std::set<VariationID> default_trigger_id_set_;

  std::string variation_ids_header_;

  DISALLOW_COPY_AND_ASSIGN(VariationsHttpHeaderProvider);
};

}  

#endif  

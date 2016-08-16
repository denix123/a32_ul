// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_VARIATIONS_VARIATIONS_ASSOCIATED_DATA_H_
#define COMPONENTS_VARIATIONS_VARIATIONS_ASSOCIATED_DATA_H_

#include <map>
#include <string>

#include "base/metrics/field_trial.h"
#include "components/variations/active_field_trials.h"


namespace variations {

typedef int VariationID;

const VariationID EMPTY_ID = 0;

enum IDCollectionKey {
  
  
  GOOGLE_WEB_PROPERTIES,
  
  
  
  GOOGLE_WEB_PROPERTIES_TRIGGER,
  
  
  GOOGLE_UPDATE_SERVICE,
  
  ID_COLLECTION_COUNT,
};

void AssociateGoogleVariationID(IDCollectionKey key,
                                const std::string& trial_name,
                                const std::string& group_name,
                                VariationID id);

void AssociateGoogleVariationIDForce(IDCollectionKey key,
                                     const std::string& trial_name,
                                     const std::string& group_name,
                                     VariationID id);

VariationID GetGoogleVariationID(IDCollectionKey key,
                                 const std::string& trial_name,
                                 const std::string& group_name);

bool AssociateVariationParams(const std::string& trial_name,
                              const std::string& group_name,
                              const std::map<std::string, std::string>& params);

bool GetVariationParams(const std::string& trial_name,
                        std::map<std::string, std::string>* params);

std::string GetVariationParamValue(const std::string& trial_name,
                                   const std::string& param_name);

namespace testing {

void ClearAllVariationIDs();

void ClearAllVariationParams();

}  

}  

#endif  

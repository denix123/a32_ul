// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_VARIATIONS_ACTIVE_FIELD_TRIALS_H_
#define COMPONENTS_VARIATIONS_ACTIVE_FIELD_TRIALS_H_

#include <string>

#include "base/basictypes.h"
#include "base/metrics/field_trial.h"

namespace variations {

struct ActiveGroupId {
  uint32 name;
  uint32 group;
};

ActiveGroupId MakeActiveGroupId(const std::string& trial_name,
                                const std::string& group_name);

struct ActiveGroupIdCompare {
  bool operator() (const ActiveGroupId& lhs, const ActiveGroupId& rhs) const {
    
    
    
    if (lhs.group != rhs.group)
      return lhs.group < rhs.group;
    return lhs.name < rhs.name;
  }
};

void GetFieldTrialActiveGroupIds(std::vector<ActiveGroupId>* name_group_ids);

void GetFieldTrialActiveGroupIdsAsStrings(std::vector<std::string>* output);

namespace testing {

void TestGetFieldTrialActiveGroupIds(
    const base::FieldTrial::ActiveGroups& active_groups,
    std::vector<ActiveGroupId>* name_group_ids);

}  

}  

#endif  

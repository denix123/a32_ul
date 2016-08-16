// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_VARIATIONS_VARIATIONS_SEED_SIMULATOR_H_
#define COMPONENTS_VARIATIONS_VARIATIONS_SEED_SIMULATOR_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/metrics/field_trial.h"
#include "base/version.h"
#include "components/variations/proto/study.pb.h"
#include "components/variations/proto/variations_seed.pb.h"

namespace variations {

class ProcessedStudy;
class VariationsSeed;

class VariationsSeedSimulator {
 public:
  
  
  
  struct Result {
    
    
    int normal_group_change_count;

    
    
    int kill_best_effort_group_change_count;

    
    
    int kill_critical_group_change_count;

    Result();
    ~Result();
  };

  
  explicit VariationsSeedSimulator(
      const base::FieldTrial::EntropyProvider& provider);
  virtual ~VariationsSeedSimulator();

  
  
  
  
  Result SimulateSeedStudies(const VariationsSeed& seed,
                             const std::string& locale,
                             const base::Time& reference_date,
                             const base::Version& version,
                             Study_Channel channel,
                             Study_FormFactor form_factor,
                             const std::string& hardware_class);

 private:
  friend class VariationsSeedSimulatorTest;

  enum ChangeType {
    NO_CHANGE,
    CHANGED,
    CHANGED_KILL_BEST_EFFORT,
    CHANGED_KILL_CRITICAL,
  };

  
  
  
  
  
  Result ComputeDifferences(
      const std::vector<ProcessedStudy>& processed_studies);

  
  ChangeType ConvertExperimentTypeToChangeType(Study_Experiment_Type type);

  
  
  
  ChangeType PermanentStudyGroupChanged(const ProcessedStudy& processed_study,
                                        const std::string& selected_group);

  
  
  
  
  ChangeType SessionStudyGroupChanged(const ProcessedStudy& filtered_study,
                                      const std::string& selected_group);

  const base::FieldTrial::EntropyProvider& entropy_provider_;

  DISALLOW_COPY_AND_ASSIGN(VariationsSeedSimulator);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_VARIATIONS_STUDY_FILTERING_H_
#define COMPONENTS_VARIATIONS_STUDY_FILTERING_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/time/time.h"
#include "base/version.h"
#include "components/variations/processed_study.h"
#include "components/variations/proto/study.pb.h"
#include "components/variations/proto/variations_seed.pb.h"

namespace variations {

namespace internal {

bool CheckStudyChannel(const Study_Filter& filter, Study_Channel channel);

bool CheckStudyFormFactor(const Study_Filter& filter,
                          Study_FormFactor form_factor);

bool CheckStudyHardwareClass(const Study_Filter& filter,
                             const std::string& hardware_class);

bool CheckStudyLocale(const Study_Filter& filter, const std::string& locale);

bool CheckStudyPlatform(const Study_Filter& filter, Study_Platform platform);

bool CheckStudyStartDate(const Study_Filter& filter,
                         const base::Time& date_time);

bool CheckStudyVersion(const Study_Filter& filter,
                       const base::Version& version);

bool IsStudyExpired(const Study& study, const base::Time& date_time);

bool ShouldAddStudy(const Study& study,
                    const std::string& locale,
                    const base::Time& reference_date,
                    const base::Version& version,
                    Study_Channel channel,
                    Study_FormFactor form_factor,
                    const std::string& hardware_class);

}  

void FilterAndValidateStudies(const VariationsSeed& seed,
                              const std::string& locale,
                              const base::Time& reference_date,
                              const base::Version& version,
                              Study_Channel channel,
                              Study_FormFactor form_factor,
                              const std::string& hardware_class,
                              std::vector<ProcessedStudy>* filtered_studies);

}  

#endif  

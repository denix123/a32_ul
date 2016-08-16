// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_SEARCH_H_
#define COMPONENTS_SEARCH_SEARCH_H_

#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"

namespace chrome {

bool IsInstantExtendedAPIEnabled();

uint64 EmbeddedSearchPageVersion();

typedef std::vector<std::pair<std::string, std::string> > FieldTrialFlags;

bool GetFieldTrialInfo(FieldTrialFlags* flags);

std::string GetStringValueForFlagWithDefault(const std::string& flag,
                                             const std::string& default_value,
                                             const FieldTrialFlags& flags);

uint64 GetUInt64ValueForFlagWithDefault(const std::string& flag,
                                        uint64 default_value,
                                        const FieldTrialFlags& flags);

bool GetBoolValueForFlagWithDefault(const std::string& flag,
                                    bool default_value,
                                    const FieldTrialFlags& flags);

bool ShouldHideTopVerbatimMatch();

}  

#endif  

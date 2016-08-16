// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_

#include <string>

#include "components/metrics/proto/omnibox_input_type.pb.h"

class AutocompleteSchemeClassifier {
 public:
  virtual ~AutocompleteSchemeClassifier() {}

  
  
  
  virtual metrics::OmniboxInputType::Type GetInputTypeForScheme(
      const std::string& scheme) const = 0;
};

#endif  

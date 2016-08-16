// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_AUTOCOMPLETE_AUTOCOMPLETE_CLASSIFIER_H_
#define CHROME_BROWSER_AUTOCOMPLETE_AUTOCOMPLETE_CLASSIFIER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/omnibox/autocomplete_scheme_classifier.h"

class AutocompleteController;
struct AutocompleteMatch;
class GURL;

class AutocompleteClassifier : public KeyedService {
 public:
  
  
  
  static const int kDefaultOmniboxProviders;

  AutocompleteClassifier(
      scoped_ptr<AutocompleteController> controller_,
      scoped_ptr<AutocompleteSchemeClassifier> scheme_classifier);
  virtual ~AutocompleteClassifier();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void Classify(const base::string16& text,
                bool prefer_keyword,
                bool allow_exact_keyword_match,
                metrics::OmniboxEventProto::PageClassification
                    page_classification,
                AutocompleteMatch* match,
                GURL* alternate_nav_url);

 private:
  
  virtual void Shutdown() OVERRIDE;

  scoped_ptr<AutocompleteController> controller_;
  scoped_ptr<AutocompleteSchemeClassifier> scheme_classifier_;

  
  
  bool inside_classify_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(AutocompleteClassifier);
};

#endif  

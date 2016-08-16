// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_OMNIBOX_FIELD_TRIAL_H_
#define COMPONENTS_OMNIBOX_OMNIBOX_FIELD_TRIAL_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/omnibox/autocomplete_match_type.h"

namespace base {
class TimeDelta;
}

struct HUPScoringParams {
  
  
  
  class ScoreBuckets {
   public:
    
    typedef std::pair<double, int> CountMaxRelevance;

    ScoreBuckets();
    ~ScoreBuckets();

    
    double HalfLifeTimeDecay(const base::TimeDelta& elapsed_time) const;

    int relevance_cap() const { return relevance_cap_; }
    void set_relevance_cap(int relevance_cap) {
      relevance_cap_ = relevance_cap;
    }

    int half_life_days() const { return half_life_days_; }
    void set_half_life_days(int half_life_days) {
      half_life_days_ = half_life_days;
    }

    std::vector<CountMaxRelevance>& buckets() { return buckets_; }
    const std::vector<CountMaxRelevance>& buckets() const { return buckets_; }

   private:
    
    
    
    
    int relevance_cap_;

    
    
    int half_life_days_;

    
    
    
    
    
    
    
    
    
    
    
    std::vector<CountMaxRelevance> buckets_;
  };

  HUPScoringParams() : experimental_scoring_enabled(false) {}

  bool experimental_scoring_enabled;

  ScoreBuckets typed_count_buckets;

  
  ScoreBuckets visited_count_buckets;
};

class OmniboxFieldTrial {
 public:
  
  
  
  typedef std::map<AutocompleteMatchType::Type, float> DemotionMultipliers;

  
  
  
  
  
  
  static void ActivateDynamicTrials();

  
  
  
  
  
  
  static int GetDisabledProviderTypes();

  
  
  static bool HasDynamicFieldTrialGroupPrefix(const char *group_prefix);

  
  

  
  
  static void GetActiveSuggestFieldTrialHashes(
      std::vector<uint32>* field_trial_hash);

  
  

  
  
  
  
  static base::TimeDelta StopTimerFieldTrialDuration();

  
  

  
  
  
  static bool InZeroSuggestFieldTrial();

  
  
  
  static bool InZeroSuggestMostVisitedFieldTrial();

  
  
  static bool InZeroSuggestAfterTypingFieldTrial();

  
  
  static bool InZeroSuggestPersonalizedFieldTrial();

  
  
  

  
  
  
  
  
  
  
  
  
  
  static bool ShortcutsScoringMaxRelevance(
      metrics::OmniboxEventProto::PageClassification
          current_page_classification,
      int* max_relevance);

  
  
  

  
  
  
  static bool SearchHistoryPreventInlining(
      metrics::OmniboxEventProto::PageClassification
          current_page_classification);

  
  
  
  static bool SearchHistoryDisable(
      metrics::OmniboxEventProto::PageClassification
          current_page_classification);

  
  
  

  
  
  
  
  
  static void GetDemotionsByType(
      metrics::OmniboxEventProto::PageClassification
          current_page_classification,
      DemotionMultipliers* demotions_by_type);

  
  
  

  
  
  
  static void GetExperimentalHUPScoringParams(HUPScoringParams* scoring_params);

  
  

  
  
  
  
  static int HQPBookmarkValue();

  
  
  

  
  
  
  static bool HQPAllowMatchInTLDValue();

  
  
  

  
  
  
  static bool HQPAllowMatchInSchemeValue();

  
  
  

  
  
  
  
  
  
  static bool DisableInlining();

  
  
  

  
  
  
  
  static bool EnableAnswersInSuggest();

  
  
  

  
  
  
  
  
  
  
  
  static bool AddUWYTMatchEvenIfPromotedURLs();

  
  
  

  
  
  
  static bool DisplayHintTextWhenPossible();

  
  
  static const char kBundledExperimentFieldTrialName[];
  
  static const char kShortcutsScoringMaxRelevanceRule[];
  static const char kSearchHistoryRule[];
  static const char kDemoteByTypeRule[];
  static const char kHQPBookmarkValueRule[];
  static const char kHQPDiscountFrecencyWhenFewVisitsRule[];
  static const char kHQPAllowMatchInTLDRule[];
  static const char kHQPAllowMatchInSchemeRule[];
  static const char kZeroSuggestRule[];
  static const char kZeroSuggestVariantRule[];
  static const char kDisableInliningRule[];
  static const char kAnswersInSuggestRule[];
  static const char kAddUWYTMatchEvenIfPromotedURLsRule[];
  static const char kDisplayHintTextWhenPossibleRule[];

  
  static const char kHUPNewScoringEnabledParam[];
  static const char kHUPNewScoringTypedCountRelevanceCapParam[];
  static const char kHUPNewScoringTypedCountHalfLifeTimeParam[];
  static const char kHUPNewScoringTypedCountScoreBucketsParam[];
  static const char kHUPNewScoringVisitedCountRelevanceCapParam[];
  static const char kHUPNewScoringVisitedCountHalfLifeTimeParam[];
  static const char kHUPNewScoringVisitedCountScoreBucketsParam[];

 private:
  friend class OmniboxFieldTrialTest;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static std::string GetValueForRuleInContext(
      const std::string& rule,
      metrics::OmniboxEventProto::PageClassification page_classification);

  DISALLOW_IMPLICIT_CONSTRUCTORS(OmniboxFieldTrial);
};

#endif  

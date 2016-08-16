// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_SAFE_BROWSING_PHISHING_TERM_FEATURE_EXTRACTOR_H_
#define CHROME_RENDERER_SAFE_BROWSING_PHISHING_TERM_FEATURE_EXTRACTOR_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/strings/string_piece.h"

namespace safe_browsing {
class FeatureExtractorClock;
class FeatureMap;

class PhishingTermFeatureExtractor {
 public:
  
  
  typedef base::Callback<void(bool)> DoneCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  PhishingTermFeatureExtractor(
      const base::hash_set<std::string>* page_term_hashes,
      const base::hash_set<uint32>* page_word_hashes,
      size_t max_words_per_term,
      uint32 murmurhash3_seed,
      size_t max_shingles_per_page,
      size_t shingle_size,
      FeatureExtractorClock* clock);
  ~PhishingTermFeatureExtractor();

  
  
  
  
  
  
  
  
  
  
  
  
  
  void ExtractFeatures(const base::string16* page_text,
                       FeatureMap* features,
                       std::set<uint32>* shingle_hashes,
                       const DoneCallback& done_callback);

  
  
  
  void CancelPendingExtraction();

 private:
  struct ExtractionState;

  
  
  static const int kMaxTimePerChunkMs;

  
  
  
  static const int kClockCheckGranularity;

  
  
  static const int kMaxTotalTimeMs;

  
  
  
  
  void ExtractFeaturesWithTimeout();

  
  void HandleWord(const base::StringPiece16& word);

  
  
  
  void CheckNoPendingExtraction();

  
  void RunCallback(bool success);

  
  void Clear();

  
  const base::hash_set<std::string>* page_term_hashes_;

  
  
  
  
  
  const base::hash_set<uint32>* page_word_hashes_;

  
  const size_t max_words_per_term_;

  
  const uint32 murmurhash3_seed_;

  
  const size_t max_shingles_per_page_;

  
  const size_t shingle_size_;

  
  FeatureExtractorClock* clock_;

  
  const base::string16* page_text_;  
  FeatureMap* features_;  
  std::set<uint32>* shingle_hashes_;
  DoneCallback done_callback_;

  
  scoped_ptr<ExtractionState> state_;

  
  
  base::WeakPtrFactory<PhishingTermFeatureExtractor> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PhishingTermFeatureExtractor);
};

}  

#endif  

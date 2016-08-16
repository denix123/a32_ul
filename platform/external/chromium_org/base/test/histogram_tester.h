// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TEST_HISTOGRAM_TESTER_H_
#define BASE_TEST_HISTOGRAM_TESTER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/metrics/histogram.h"
#include "base/metrics/histogram_base.h"

namespace base {

class HistogramSamples;

class HistogramTester {
 public:
  
  
  HistogramTester();
  ~HistogramTester();

  
  
  
  void ExpectUniqueSample(const std::string& name,
                          base::HistogramBase::Sample sample,
                          base::HistogramBase::Count expected_count) const;

  
  
  
  void ExpectBucketCount(const std::string& name,
                         base::HistogramBase::Sample sample,
                         base::HistogramBase::Count expected_count) const;

  
  
  
  void ExpectTotalCount(const std::string& name,
                        base::HistogramBase::Count count) const;

  
  
  scoped_ptr<HistogramSamples> GetHistogramSamplesSinceCreation(
      const std::string& histogram_name);

 private:
  
  
  
  void CheckBucketCount(const std::string& name,
                        base::HistogramBase::Sample sample,
                        base::Histogram::Count expected_count,
                        base::HistogramSamples& samples) const;

  
  
  
  void CheckTotalCount(const std::string& name,
                       base::Histogram::Count expected_count,
                       base::HistogramSamples& samples) const;

  
  
  
  std::map<std::string, HistogramSamples*> histograms_snapshot_;

  DISALLOW_COPY_AND_ASSIGN(HistogramTester);
};

}  

#endif  

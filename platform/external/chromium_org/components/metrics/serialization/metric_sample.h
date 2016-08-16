// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_SERIALIZATION_METRIC_SAMPLE_H_
#define COMPONENTS_METRICS_SERIALIZATION_METRIC_SAMPLE_H_

#include <string>

#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"

namespace metrics {

class MetricSample {
 public:
  
  enum SampleType {
    CRASH,
    HISTOGRAM,
    LINEAR_HISTOGRAM,
    SPARSE_HISTOGRAM,
    USER_ACTION
  };

  ~MetricSample();

  
  
  
  bool IsValid() const;

  
  
  SampleType type() const { return type_; }
  const std::string& name() const { return name_; }

  
  
  
  
  const int sample() const;
  const int min() const;
  const int max() const;
  const int bucket_count() const;

  
  
  
  
  
  
  
  
  std::string ToString() const;

  
  static scoped_ptr<MetricSample> CrashSample(const std::string& crash_name);

  
  static scoped_ptr<MetricSample> HistogramSample(
      const std::string& histogram_name,
      int sample,
      int min,
      int max,
      int bucket_count);
  
  static scoped_ptr<MetricSample> ParseHistogram(const std::string& serialized);

  
  static scoped_ptr<MetricSample> SparseHistogramSample(
      const std::string& histogram_name,
      int sample);
  
  static scoped_ptr<MetricSample> ParseSparseHistogram(
      const std::string& serialized);

  
  static scoped_ptr<MetricSample> LinearHistogramSample(
      const std::string& histogram_name,
      int sample,
      int max);
  
  static scoped_ptr<MetricSample> ParseLinearHistogram(
      const std::string& serialized);

  
  static scoped_ptr<MetricSample> UserActionSample(
      const std::string& action_name);

  
  
  bool IsEqual(const MetricSample& sample);

 private:
  MetricSample(SampleType sample_type,
               const std::string& metric_name,
               const int sample,
               const int min,
               const int max,
               const int bucket_count);

  const SampleType type_;
  const std::string name_;
  const int sample_;
  const int min_;
  const int max_;
  const int bucket_count_;

  DISALLOW_COPY_AND_ASSIGN(MetricSample);
};

}  

#endif  

// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTERNAL_METRICS_H_
#define CHROME_BROWSER_CHROMEOS_EXTERNAL_METRICS_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"

namespace metrics {
class MetricSample;
}  

namespace chromeos {

class ExternalMetrics : public base::RefCountedThreadSafe<ExternalMetrics> {
 public:
  ExternalMetrics();

  
  
  
  void Start();

  
  
  static scoped_refptr<ExternalMetrics> CreateForTesting(
      const std::string& filename);

 private:
  friend class base::RefCountedThreadSafe<ExternalMetrics>;
  friend class ExternalMetricsTest;

  FRIEND_TEST_ALL_PREFIXES(ExternalMetricsTest, CanReceiveHistogram);
  FRIEND_TEST_ALL_PREFIXES(ExternalMetricsTest, HandleMissingFile);
  FRIEND_TEST_ALL_PREFIXES(ExternalMetricsTest,
                           IncorrectHistogramsAreDiscarded);

  
  static const int kMetricsMessageMaxLength = 1024;  

  ~ExternalMetrics();

  
  void RecordActionUI(std::string action_string);

  
  void RecordAction(const std::string& action_name);

  
  
  void RecordCrashUI(const std::string& crash_kind);

  
  void RecordCrash(const std::string& crash_kind);

  
  void RecordHistogram(const metrics::MetricSample& sample);

  
  void RecordSparseHistogram(const metrics::MetricSample& sample);

  
  void RecordLinearHistogram(const metrics::MetricSample& sample);

  
  
  
  
  int CollectEvents();

  
  void CollectEventsAndReschedule();

  
  void ScheduleCollector();

  
  
  
  
  void SetupFieldTrialsOnFileThread();

  
  base::hash_set<std::string> valid_user_actions_;

  
  std::string uma_events_file_;

  DISALLOW_COPY_AND_ASSIGN(ExternalMetrics);
};

}  

#endif  

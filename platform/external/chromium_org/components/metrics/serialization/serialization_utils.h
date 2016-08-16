// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_SERIALIZATION_SERIALIZATION_UTILS_H_
#define COMPONENTS_METRICS_SERIALIZATION_SERIALIZATION_UTILS_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"

namespace metrics {

class MetricSample;

namespace SerializationUtils {

scoped_ptr<MetricSample> ParseSample(const std::string& sample);

void ReadAndTruncateMetricsFromFile(const std::string& filename,
                                    ScopedVector<MetricSample>* metrics);

//  NB: the file will never leave the device so message_size will be written
bool WriteMetricToFile(const MetricSample& sample, const std::string& filename);

static const int kMessageMaxLength = 1024;

}  
}  

#endif  

// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_DISK_CACHE_BLOCKFILE_HISTOGRAM_MACROS_H_
#define NET_DISK_CACHE_BLOCKFILE_HISTOGRAM_MACROS_H_

#include "base/metrics/histogram.h"



#define CACHE_HISTOGRAM_CUSTOM_COUNTS(name, sample, min, max, bucket_count) \
    do { \
      base::HistogramBase* counter = base::Histogram::FactoryGet( \
            name, min, max, bucket_count, \
            base::Histogram::kUmaTargetedHistogramFlag); \
      counter->Add(sample); \
    } while (0)

#define CACHE_HISTOGRAM_COUNTS(name, sample) CACHE_HISTOGRAM_CUSTOM_COUNTS( \
    name, sample, 1, 1000000, 50)

#define CACHE_HISTOGRAM_COUNTS_10000(name, sample) \
    CACHE_HISTOGRAM_CUSTOM_COUNTS(name, sample, 1, 10000, 50)

#define CACHE_HISTOGRAM_COUNTS_50000(name, sample) \
    CACHE_HISTOGRAM_CUSTOM_COUNTS(name, sample, 1, 50000000, 50)

#define CACHE_HISTOGRAM_CUSTOM_TIMES(name, sample, min, max, bucket_count) \
    do { \
      base::HistogramBase* counter = base::Histogram::FactoryTimeGet( \
            name, min, max, bucket_count, \
            base::Histogram::kUmaTargetedHistogramFlag); \
      counter->AddTime(sample); \
    } while (0)

#define CACHE_HISTOGRAM_TIMES(name, sample) CACHE_HISTOGRAM_CUSTOM_TIMES( \
    name, sample, base::TimeDelta::FromMilliseconds(1), \
    base::TimeDelta::FromSeconds(10), 50)

#define CACHE_HISTOGRAM_ENUMERATION(name, sample, boundary_value) do { \
    base::HistogramBase* counter = base::LinearHistogram::FactoryGet( \
                    name, 1, boundary_value, boundary_value + 1, \
                    base::Histogram::kUmaTargetedHistogramFlag); \
    counter->Add(sample); \
  } while (0)

#define CACHE_HISTOGRAM_PERCENTAGE(name, under_one_hundred) \
    CACHE_HISTOGRAM_ENUMERATION(name, under_one_hundred, 101)


#define CACHE_HISTOGRAM_HOURS CACHE_HISTOGRAM_COUNTS_10000

#define CACHE_HISTOGRAM_AGE(name, initial_time) \
    CACHE_HISTOGRAM_COUNTS_10000(name, \
                                 (base::Time::Now() - initial_time).InHours())

#define CACHE_HISTOGRAM_AGE_MS(name, initial_time)\
    CACHE_HISTOGRAM_TIMES(name, base::TimeTicks::Now() - initial_time)

#define CACHE_HISTOGRAM_CACHE_ERROR(name, sample) \
    CACHE_HISTOGRAM_ENUMERATION(name, sample, 50)

#define CACHE_UMA(type, name, experiment, sample) {\
    const std::string my_name =\
        CACHE_UMA_BACKEND_IMPL_OBJ->HistogramName(name, experiment);\
    switch (CACHE_UMA_BACKEND_IMPL_OBJ->cache_type()) {\
      default:\
        NOTREACHED();\
        \
      case net::DISK_CACHE:\
      case net::MEDIA_CACHE:\
      case net::APP_CACHE:\
      case net::SHADER_CACHE:\
      case net::PNACL_CACHE:\
        CACHE_HISTOGRAM_##type(my_name.data(), sample);\
        break;\
    }\
  }

#endif  

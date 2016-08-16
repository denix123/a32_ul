// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_NETWORK_STATS_UPLOADER_H_
#define CHROME_BROWSER_METRICS_NETWORK_STATS_UPLOADER_H_

#include <string>

#include "base/basictypes.h"

class PrefService;
class PrefRegistrySimple;

class NetworkStatsUploader {
 public:
  NetworkStatsUploader();
  ~NetworkStatsUploader();

  
  void CollectAndReportNetworkStats();

 private:
  
  std::string network_stats_server_;

  DISALLOW_COPY_AND_ASSIGN(NetworkStatsUploader);
};

#endif  

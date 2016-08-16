// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MAC_MAC_STARTUP_PROFILER_H_
#define CHROME_BROWSER_MAC_MAC_STARTUP_PROFILER_H_

#include <map>

#include "base/memory/singleton.h"
#include "base/time/time.h"

class MacStartupProfiler {
 public:
  
  static MacStartupProfiler* GetInstance();

  MacStartupProfiler();
  ~MacStartupProfiler();

  
  
  
  
  
  enum Location {
    PRE_MAIN_MESSAGE_LOOP_START,
    AWAKE_FROM_NIB,
    POST_MAIN_MESSAGE_LOOP_START,
    PRE_PROFILE_INIT,
    POST_PROFILE_INIT,
    WILL_FINISH_LAUNCHING,
    DID_FINISH_LAUNCHING,
  };

  
  void Profile(Location location);

  
  void RecordMetrics();

 private:
  friend struct DefaultSingletonTraits<MacStartupProfiler>;

  
  const std::string HistogramName(Location location);

  
  void RecordHistogram(Location location, const base::TimeDelta& delta);

  
  std::map<Location, base::Time> profiled_times_;

  
  bool recorded_metrics_;

  DISALLOW_COPY_AND_ASSIGN(MacStartupProfiler);
};

#endif  

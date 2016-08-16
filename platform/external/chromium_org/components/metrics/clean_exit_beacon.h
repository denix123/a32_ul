// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_CLEAN_EXIT_BEACON_H_
#define COMPONENTS_METRICS_CLEAN_EXIT_BEACON_H_

#include "base/macros.h"
#include "base/strings/string16.h"

class PrefService;

namespace metrics {

class CleanExitBeacon {
 public:
  
  
  
  
  CleanExitBeacon(
      const base::string16& backup_registry_key,
      PrefService* local_state);

  ~CleanExitBeacon();

  
  bool exited_cleanly() const { return initial_value_; }

  
  void WriteBeaconValue(bool exited_cleanly);

 private:
  PrefService* const local_state_;
  const bool initial_value_;
  const base::string16 backup_registry_key_;

  DISALLOW_COPY_AND_ASSIGN(CleanExitBeacon);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POWER_ORIGIN_POWER_MAP_H_
#define COMPONENTS_POWER_ORIGIN_POWER_MAP_H_

#include <map>

#include "base/callback_list.h"
#include "components/keyed_service/core/keyed_service.h"
#include "url/gurl.h"

namespace power {

class OriginPowerMap : public KeyedService {
 public:
  typedef std::map<GURL, int> PercentOriginMap;
  typedef base::CallbackList<void(void)>::Subscription Subscription;

  OriginPowerMap();
  virtual ~OriginPowerMap();

  
  
  int GetPowerForOrigin(const GURL& url);

  
  
  void AddPowerForOrigin(const GURL& url, double power);

  
  
  PercentOriginMap GetPercentOriginMap();

  
  scoped_ptr<Subscription> AddPowerConsumptionUpdatedCallback(
      const base::Closure& callback);

  
  
  void OnAllOriginsUpdated();

  
  void ClearOriginMap();

 private:
  
  
  typedef std::map<GURL, double> OriginMap;
  OriginMap origin_map_;

  
  
  double total_consumed_;

  base::CallbackList<void(void)> callback_list_;

  DISALLOW_COPY_AND_ASSIGN(OriginPowerMap);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_DAILY_EVENT_H_
#define COMPONENTS_METRICS_DAILY_EVENT_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"

class PrefRegistrySimple;
class PrefService;

namespace metrics {

class DailyEvent {
 public:
  
  
  
  class Observer {
   public:
    Observer();
    virtual ~Observer();

    
    virtual void OnDailyEvent() = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(Observer);
  };

  
  
  
  
  
  
  
  DailyEvent(PrefService* pref_service,
             const char* pref_name,
             const std::string& histogram_name);
  ~DailyEvent();

  
  
  void AddObserver(scoped_ptr<Observer> observer);

  
  
  void CheckInterval();

  
  static void RegisterPref(PrefRegistrySimple* registry, const char* pref_name);

 private:
  
  void OnInterval(base::Time now);

  
  
  
  PrefService* pref_service_;

  
  
  const char* pref_name_;

  
  std::string histogram_name_;

  
  ScopedVector<Observer> observers_;

  
  base::Time last_fired_;

  DISALLOW_COPY_AND_ASSIGN(DailyEvent);
};

}  

#endif  

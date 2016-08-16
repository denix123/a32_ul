// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_COMPOSITOR_VSYNC_MANAGER_H_
#define UI_COMPOSITOR_COMPOSITOR_VSYNC_MANAGER_H_

#include "base/memory/ref_counted.h"
#include "base/observer_list_threadsafe.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "ui/compositor/compositor_export.h"

namespace ui {

class COMPOSITOR_EXPORT CompositorVSyncManager
    : public base::RefCountedThreadSafe<CompositorVSyncManager> {
 public:
  class Observer {
   public:
    virtual void OnUpdateVSyncParameters(base::TimeTicks timebase,
                                         base::TimeDelta interval) = 0;
  };

  CompositorVSyncManager();

  
  
  
  
  
  
  void SetAuthoritativeVSyncInterval(base::TimeDelta interval);

  
  
  
  void UpdateVSyncParameters(base::TimeTicks timebase,
                             base::TimeDelta interval);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  friend class base::RefCountedThreadSafe<CompositorVSyncManager>;

  ~CompositorVSyncManager();

  void NotifyObservers(base::TimeTicks timebase, base::TimeDelta interval);

  
  scoped_refptr<ObserverListThreadSafe<Observer> > observer_list_;

  
  base::Lock vsync_parameters_lock_;
  base::TimeTicks last_timebase_;
  base::TimeDelta last_interval_;
  base::TimeDelta authoritative_vsync_interval_;

  DISALLOW_COPY_AND_ASSIGN(CompositorVSyncManager);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_QUOTA_STORAGE_OBSERVER_H_
#define STORAGE_BROWSER_QUOTA_STORAGE_OBSERVER_H_

#include "base/basictypes.h"
#include "base/time/time.h"
#include "storage/browser/quota/quota_client.h"
#include "storage/common/quota/quota_types.h"
#include "url/gurl.h"

namespace storage {

class STORAGE_EXPORT StorageObserver {
 public:
  struct STORAGE_EXPORT Filter {
    
    
    StorageType storage_type;

    
    GURL origin;

    Filter();
    Filter(StorageType storage_type, const GURL& origin);
    bool operator==(const Filter& other) const;
  };

  struct STORAGE_EXPORT MonitorParams {
    
    Filter filter;

    
    
    
    base::TimeDelta rate;

    
    bool dispatch_initial_state;

    MonitorParams();
    MonitorParams(StorageType storage_type,
                  const GURL& origin,
                  const base::TimeDelta& rate,
                  bool get_initial_state);
    MonitorParams(const Filter& filter,
                  const base::TimeDelta& rate,
                  bool get_initial_state);
  };

  struct STORAGE_EXPORT Event {
    
    Filter filter;

    
    int64 usage;

    
    int64 quota;

    Event();
    Event(const Filter& filter, int64 usage, int64 quota);
    bool operator==(const Event& other) const;
  };

  
  virtual void OnStorageEvent(const Event& event) = 0;

 protected:
  virtual ~StorageObserver() {}
};

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_MEMORY_LOW_MEMORY_OBSERVER_H_
#define CHROME_BROWSER_CHROMEOS_MEMORY_LOW_MEMORY_OBSERVER_H_

#include "base/memory/ref_counted.h"

namespace chromeos {

class LowMemoryObserverImpl;

class LowMemoryObserver {
 public:
  LowMemoryObserver();
  ~LowMemoryObserver();

  void Start();
  void Stop();

 private:
  scoped_refptr<LowMemoryObserverImpl> observer_;

  DISALLOW_COPY_AND_ASSIGN(LowMemoryObserver);
};

}  

#endif  

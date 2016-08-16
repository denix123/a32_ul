// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_METRICS_THREAD_WATCHER_ANDROID_H_
#define CHROME_BROWSER_METRICS_THREAD_WATCHER_ANDROID_H_

#include "base/basictypes.h"

class ThreadWatcherAndroid {
 public:
  static void RegisterApplicationStatusListener();

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(ThreadWatcherAndroid);
};

#endif  

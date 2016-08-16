// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_SCOPED_KEEP_ALIVE_H_
#define CHROME_BROWSER_APPS_SCOPED_KEEP_ALIVE_H_

#include "base/macros.h"

class ScopedKeepAlive {
 public:
  ScopedKeepAlive();
  ~ScopedKeepAlive();

 private:
  DISALLOW_COPY_AND_ASSIGN(ScopedKeepAlive);
};

#endif  

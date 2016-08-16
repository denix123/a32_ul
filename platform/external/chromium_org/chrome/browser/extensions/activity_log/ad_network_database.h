// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_ACTIVITY_LOG_AD_NETWORK_DATABASE_H_
#define CHROME_BROWSER_EXTENSIONS_ACTIVITY_LOG_AD_NETWORK_DATABASE_H_

#include "base/memory/scoped_ptr.h"

class GURL;

namespace extensions {
class Action;

class AdNetworkDatabase {
 public:
  virtual ~AdNetworkDatabase();

  static const AdNetworkDatabase* Get();
  static void SetForTesting(scoped_ptr<AdNetworkDatabase> database);

  
  virtual bool IsAdNetwork(const GURL& url) const = 0;
};

}  

#endif  

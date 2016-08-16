// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_ACTIVITY_LOG_HASHED_AD_NETWORK_DATABASE_H_
#define CHROME_BROWSER_EXTENSIONS_ACTIVITY_LOG_HASHED_AD_NETWORK_DATABASE_H_

#include "chrome/browser/extensions/activity_log/ad_network_database.h"

namespace extensions {

class HashedAdNetworkDatabase : public AdNetworkDatabase {
 public:
  HashedAdNetworkDatabase();
  virtual ~HashedAdNetworkDatabase();

  void set_entries_for_testing(const char** entries, int num_entries) {
    entries_ = entries;
    num_entries_ = num_entries;
  }

 private:
  
  virtual bool IsAdNetwork(const GURL& url) const OVERRIDE;

  
  
  const char** entries_;

  
  int num_entries_;
};

}  

#endif  

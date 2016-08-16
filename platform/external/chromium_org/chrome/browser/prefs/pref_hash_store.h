// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_PREF_HASH_STORE_H_
#define CHROME_BROWSER_PREFS_PREF_HASH_STORE_H_

#include "base/memory/scoped_ptr.h"

class HashStoreContents;
class PrefHashStoreTransaction;

class PrefHashStore {
 public:
  virtual ~PrefHashStore() {}

  
  
  
  
  virtual scoped_ptr<PrefHashStoreTransaction> BeginTransaction(
      scoped_ptr<HashStoreContents> storage) = 0;
};

#endif  

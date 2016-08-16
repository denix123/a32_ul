// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_PREF_HASH_STORE_IMPL_H_
#define CHROME_BROWSER_PREFS_PREF_HASH_STORE_IMPL_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/prefs/pref_hash_calculator.h"
#include "chrome/browser/prefs/pref_hash_store.h"

class HashStoreContents;
class PrefHashStoreTransaction;

class PrefHashStoreImpl : public PrefHashStore {
 public:
  enum StoreVersion {
    
    VERSION_UNINITIALIZED = 0,
    
    
    VERSION_PRE_MIGRATION = 1,
    
    VERSION_LATEST = 2,
  };

  
  
  
  
  
  PrefHashStoreImpl(const std::string& seed,
                    const std::string& device_id,
                    bool use_super_mac);

  virtual ~PrefHashStoreImpl();

  
  
  void set_legacy_hash_store_contents(
      scoped_ptr<HashStoreContents> legacy_hash_store_contents);

  
  
  void Reset();

  
  virtual scoped_ptr<PrefHashStoreTransaction> BeginTransaction(
      scoped_ptr<HashStoreContents> storage) OVERRIDE;

 private:
  class PrefHashStoreTransactionImpl;

  const PrefHashCalculator pref_hash_calculator_;
  scoped_ptr<HashStoreContents> legacy_hash_store_contents_;
  bool use_super_mac_;

  DISALLOW_COPY_AND_ASSIGN(PrefHashStoreImpl);
};

#endif  

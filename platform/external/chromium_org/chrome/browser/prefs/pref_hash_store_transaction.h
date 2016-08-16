// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_PREF_HASH_STORE_TRANSACTION_H_
#define CHROME_BROWSER_PREFS_PREF_HASH_STORE_TRANSACTION_H_

#include <string>
#include <vector>

namespace base {
class DictionaryValue;
class Value;
}  

class PrefHashStoreTransaction {
 public:
  enum ValueState {
    
    UNCHANGED,
    
    CLEARED,
    
    
    
    SECURE_LEGACY,
    
    CHANGED,
    
    UNTRUSTED_UNKNOWN_VALUE,
    
    
    
    
    
    TRUSTED_UNKNOWN_VALUE,
  };

  
  virtual ~PrefHashStoreTransaction() {}

  
  virtual ValueState CheckValue(
      const std::string& path, const base::Value* initial_value) const = 0;

  
  virtual void StoreHash(const std::string& path,
                         const base::Value* value) = 0;

  
  
  
  
  
  
  virtual ValueState CheckSplitValue(
      const std::string& path,
      const base::DictionaryValue* initial_split_value,
      std::vector<std::string>* invalid_keys) const = 0;

  
  
  virtual void StoreSplitHash(
      const std::string& path,
      const base::DictionaryValue* split_value) = 0;

  
  virtual bool HasHash(const std::string& path) const = 0;

  
  
  
  
  
  
  
  
  
  virtual void ImportHash(const std::string& path, const base::Value* hash) = 0;

  
  
  virtual void ClearHash(const std::string& path) = 0;

  
  
  virtual bool IsSuperMACValid() const = 0;

  
  
  virtual bool StampSuperMac() = 0;
};

#endif  

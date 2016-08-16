// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_HASH_STORE_CONTENTS_H_
#define CHROME_BROWSER_PREFS_TRACKED_HASH_STORE_CONTENTS_H_

#include <string>

#include "base/memory/scoped_ptr.h"

namespace base {
class DictionaryValue;
} 

class HashStoreContents {
 public:
  
  
  
  class MutableDictionary {
   public:
    virtual ~MutableDictionary() {}
    
    
    virtual base::DictionaryValue* operator->() = 0;
  };

  virtual ~HashStoreContents() {}

  
  virtual std::string hash_store_id() const = 0;

  
  virtual void Reset() = 0;

  
  virtual bool IsInitialized() const = 0;

  
  
  virtual const base::DictionaryValue* GetContents() const = 0;

  
  virtual scoped_ptr<MutableDictionary> GetMutableContents() = 0;

  
  
  virtual std::string GetSuperMac() const = 0;

  
  virtual void SetSuperMac(const std::string& super_mac) = 0;
};

#endif  

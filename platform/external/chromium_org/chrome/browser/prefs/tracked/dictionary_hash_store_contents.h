// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_DICTIONARY_HASH_STORE_CONTENTS_H_
#define CHROME_BROWSER_PREFS_TRACKED_DICTIONARY_HASH_STORE_CONTENTS_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/prefs/tracked/hash_store_contents.h"

namespace base {
class DictionaryValue;
}  

namespace user_prefs {
class PrefRegistrySyncable;
}  

class DictionaryHashStoreContents : public HashStoreContents {
 public:
  
  
  explicit DictionaryHashStoreContents(base::DictionaryValue* storage);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  virtual std::string hash_store_id() const OVERRIDE;
  virtual void Reset() OVERRIDE;
  virtual bool IsInitialized() const OVERRIDE;
  virtual const base::DictionaryValue* GetContents() const OVERRIDE;
  virtual scoped_ptr<MutableDictionary> GetMutableContents() OVERRIDE;
  virtual std::string GetSuperMac() const OVERRIDE;
  virtual void SetSuperMac(const std::string& super_mac) OVERRIDE;

 private:
  base::DictionaryValue* storage_;

  DISALLOW_COPY_AND_ASSIGN(DictionaryHashStoreContents);
};

#endif  

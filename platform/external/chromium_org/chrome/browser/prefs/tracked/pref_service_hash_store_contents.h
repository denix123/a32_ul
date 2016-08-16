// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_PREF_SERVICE_HASH_STORE_CONTENTS_H_
#define CHROME_BROWSER_PREFS_TRACKED_PREF_SERVICE_HASH_STORE_CONTENTS_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/prefs/tracked/hash_store_contents.h"

class PrefRegistrySimple;
class PrefService;

class PrefServiceHashStoreContents : public HashStoreContents {
 public:
  
  
  
  
  
  PrefServiceHashStoreContents(const std::string& hash_store_id,
                               PrefService* pref_service);

  
  
  
  static const char kProfilePreferenceHashes[];

  
  
  
  
  static const char kHashOfHashesDict[];

  
  
  
  
  static const char kStoreVersionsDict[];

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  static void ResetAllPrefHashStores(PrefService* pref_service);

  
  virtual std::string hash_store_id() const OVERRIDE;
  virtual void Reset() OVERRIDE;
  virtual bool IsInitialized() const OVERRIDE;
  virtual const base::DictionaryValue* GetContents() const OVERRIDE;
  virtual scoped_ptr<MutableDictionary> GetMutableContents() OVERRIDE;
  virtual std::string GetSuperMac() const OVERRIDE;
  virtual void SetSuperMac(const std::string& super_mac) OVERRIDE;

 private:
  const std::string hash_store_id_;
  PrefService* pref_service_;

  DISALLOW_COPY_AND_ASSIGN(PrefServiceHashStoreContents);
};

#endif  

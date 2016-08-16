// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCE_H_
#define CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCE_H_

class PrefHashStoreTransaction;

namespace base {
class DictionaryValue;
class Value;
}

class TrackedPreference {
 public:
  virtual ~TrackedPreference() {}

  
  
  virtual void OnNewValue(const base::Value* value,
                          PrefHashStoreTransaction* transaction) const = 0;

  
  
  
  
  
  virtual bool EnforceAndReport(
      base::DictionaryValue* pref_store_contents,
      PrefHashStoreTransaction* transaction) const = 0;
};

#endif  

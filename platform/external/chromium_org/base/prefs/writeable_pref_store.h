// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PREFS_WRITEABLE_PREF_STORE_H_
#define BASE_PREFS_WRITEABLE_PREF_STORE_H_

#include <string>

#include "base/basictypes.h"
#include "base/prefs/pref_store.h"

namespace base {
class Value;
}

// A pref store that can be written to as well as read from.
class BASE_PREFS_EXPORT WriteablePrefStore : public PrefStore {
 public:
  WriteablePrefStore() {}

  
  
  virtual void SetValue(const std::string& key, base::Value* value) = 0;

  
  virtual void RemoveValue(const std::string& key) = 0;

  
  virtual bool GetMutableValue(const std::string& key,
                               base::Value** result) = 0;

  
  
  
  
  virtual void ReportValueChanged(const std::string& key) = 0;

  
  
  
  
  virtual void SetValueSilently(const std::string& key, base::Value* value) = 0;

 protected:
  virtual ~WriteablePrefStore() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(WriteablePrefStore);
};

#endif  

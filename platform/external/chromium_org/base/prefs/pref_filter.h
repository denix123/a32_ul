// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PREFS_PREF_FILTER_H_
#define BASE_PREFS_PREF_FILTER_H_

#include <string>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/base_prefs_export.h"

namespace base {
class DictionaryValue;
class Value;
}  

class BASE_PREFS_EXPORT PrefFilter {
 public:
  
  
  
  
  typedef base::Callback<void(scoped_ptr<base::DictionaryValue> prefs,
                              bool schedule_write)> PostFilterOnLoadCallback;

  virtual ~PrefFilter() {}

  
  
  
  
  
  
  
  virtual void FilterOnLoad(
      const PostFilterOnLoadCallback& post_filter_on_load_callback,
      scoped_ptr<base::DictionaryValue> pref_store_contents) = 0;

  
  
  virtual void FilterUpdate(const std::string& path) = 0;

  
  
  
  
  virtual void FilterSerializeData(
      base::DictionaryValue* pref_store_contents) = 0;
};

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_VALUE_COUNTER_H_
#define EXTENSIONS_COMMON_VALUE_COUNTER_H_

#include <vector>

#include "base/memory/linked_ptr.h"

namespace base {
class Value;
}

namespace extensions {

class ValueCounter {
 public:
  ValueCounter();
  ~ValueCounter();

  
  
  
  
  int Add(const base::Value& value);

  
  
  int Remove(const base::Value& value);

  
  int AddIfMissing(const base::Value& value);

 private:
  class Entry {
   public:
    explicit Entry(const base::Value& value);
    ~Entry();

    int Increment();
    int Decrement();

    const base::Value* value() const { return value_.get(); }
    int count() const { return count_; }

   private:
    linked_ptr<base::Value> value_;
    int count_;

    DISALLOW_COPY_AND_ASSIGN(Entry);
  };
  typedef std::vector<linked_ptr<Entry> > EntryList;

  int AddImpl(const base::Value& value, bool increment);

  EntryList entries_;

  DISALLOW_COPY_AND_ASSIGN(ValueCounter);
};

}  

#endif  

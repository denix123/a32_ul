// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_SCOPED_OBSERVER_H_
#define BASE_SCOPED_OBSERVER_H_

#include <algorithm>
#include <vector>

#include "base/basictypes.h"
#include "base/logging.h"

template <class Source, class Observer>
class ScopedObserver {
 public:
  explicit ScopedObserver(Observer* observer) : observer_(observer) {}

  ~ScopedObserver() {
    RemoveAll();
  }

  
  void Add(Source* source) {
    sources_.push_back(source);
    source->AddObserver(observer_);
  }

  
  void Remove(Source* source) {
    auto it = std::find(sources_.begin(), sources_.end(), source);
    DCHECK(it != sources_.end());
    sources_.erase(it);
    source->RemoveObserver(observer_);
  }

  void RemoveAll() {
    for (size_t i = 0; i < sources_.size(); ++i)
      sources_[i]->RemoveObserver(observer_);
    sources_.clear();
  }

  bool IsObserving(Source* source) const {
    return std::find(sources_.begin(), sources_.end(), source) !=
        sources_.end();
  }

 private:
  Observer* observer_;

  std::vector<Source*> sources_;

  DISALLOW_COPY_AND_ASSIGN(ScopedObserver);
};

#endif  

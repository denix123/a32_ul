// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_FILTER_CHAIN_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_FILTER_CHAIN_H_

#include <vector>

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_filter.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {
namespace internal {

class FilterChain {
  MOJO_MOVE_ONLY_TYPE_FOR_CPP_03(FilterChain, RValue)

 public:
  
  
  explicit FilterChain(MessageReceiver* sink = NULL);

  
  FilterChain(RValue other);
  FilterChain& operator=(RValue other);

  ~FilterChain();

  template <typename FilterType>
  inline void Append();

  
  
  void SetSink(MessageReceiver* sink);

  
  
  
  
  MessageReceiver* GetHead();

 private:
  
  std::vector<MessageFilter*> filters_;

  MessageReceiver* sink_;
};

template <typename FilterType>
inline void FilterChain::Append() {
  FilterType* filter = new FilterType(sink_);
  if (!filters_.empty())
    filters_.back()->set_sink(filter);
  filters_.push_back(filter);
}

template <>
inline void FilterChain::Append<PassThroughFilter>() {
}

}  
}  

#endif  

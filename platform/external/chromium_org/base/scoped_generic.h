// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_SCOPED_GENERIC_H_
#define BASE_SCOPED_GENERIC_H_

#include <stdlib.h>

#include <algorithm>

#include "base/compiler_specific.h"
#include "base/move.h"

namespace base {

template<typename T, typename Traits>
class ScopedGeneric {
  MOVE_ONLY_TYPE_FOR_CPP_03(ScopedGeneric, RValue)

 private:
  
  
  
  
  
  
  struct Data : public Traits {
    explicit Data(const T& in) : generic(in) {}
    Data(const T& in, const Traits& other) : Traits(other), generic(in) {}
    T generic;
  };

 public:
  typedef T element_type;
  typedef Traits traits_type;

  ScopedGeneric() : data_(traits_type::InvalidValue()) {}

  
  
  explicit ScopedGeneric(const element_type& value) : data_(value) {}

  
  ScopedGeneric(const element_type& value, const traits_type& traits)
      : data_(value, traits) {
  }

  
  ScopedGeneric(RValue rvalue)
      : data_(rvalue.object->release(), rvalue.object->get_traits()) {
  }

  ~ScopedGeneric() {
    FreeIfNecessary();
  }

  
  
  
  void reset(const element_type& value = traits_type::InvalidValue()) {
    if (data_.generic != traits_type::InvalidValue() && data_.generic == value)
      abort();
    FreeIfNecessary();
    data_.generic = value;
  }

  void swap(ScopedGeneric& other) {
    
    
    
    using std::swap;
    swap(static_cast<Traits&>(data_), static_cast<Traits&>(other.data_));
    swap(data_.generic, other.data_.generic);
  }

  
  
  
  element_type release() WARN_UNUSED_RESULT {
    element_type old_generic = data_.generic;
    data_.generic = traits_type::InvalidValue();
    return old_generic;
  }

  const element_type& get() const { return data_.generic; }

  
  
  bool is_valid() const { return data_.generic != traits_type::InvalidValue(); }

  bool operator==(const element_type& value) const {
    return data_.generic == value;
  }
  bool operator!=(const element_type& value) const {
    return data_.generic != value;
  }

  Traits& get_traits() { return data_; }
  const Traits& get_traits() const { return data_; }

 private:
  void FreeIfNecessary() {
    if (data_.generic != traits_type::InvalidValue()) {
      data_.Free(data_.generic);
      data_.generic = traits_type::InvalidValue();
    }
  }

  
  
  
  template <typename T2, typename Traits2> bool operator==(
      const ScopedGeneric<T2, Traits2>& p2) const;
  template <typename T2, typename Traits2> bool operator!=(
      const ScopedGeneric<T2, Traits2>& p2) const;

  Data data_;
};

template<class T, class Traits>
void swap(const ScopedGeneric<T, Traits>& a,
          const ScopedGeneric<T, Traits>& b) {
  a.swap(b);
}

template<class T, class Traits>
bool operator==(const T& value, const ScopedGeneric<T, Traits>& scoped) {
  return value == scoped.get();
}

template<class T, class Traits>
bool operator!=(const T& value, const ScopedGeneric<T, Traits>& scoped) {
  return value != scoped.get();
}

}  

#endif  

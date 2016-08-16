// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_UNIQUE_VECTOR_H_
#define TOOLS_GN_UNIQUE_VECTOR_H_

#include <algorithm>

#include "base/containers/hash_tables.h"

namespace internal {

template<typename T>
class UniquifyRef {
 public:
  UniquifyRef()
      : value_(NULL),
        vect_(NULL),
        index_(static_cast<size_t>(-1)),
        hash_val_(0) {
  }

  
  UniquifyRef(const T* v)
      : value_(v),
        vect_(NULL),
        index_(static_cast<size_t>(-1)) {
    FillHashValue();
  }

  
  UniquifyRef(const std::vector<T>* v, size_t i)
      : value_(NULL),
        vect_(v),
        index_(i) {
    FillHashValue();
  }

  
  
  UniquifyRef(const std::vector<T>* v, size_t i, size_t hash_value)
      : value_(NULL),
        vect_(v),
        index_(i),
        hash_val_(hash_value) {
  }

  const T& value() const { return value_ ? *value_ : (*vect_)[index_]; }
  size_t hash_val() const { return hash_val_; }
  size_t index() const { return index_; }

 private:
  void FillHashValue() {
#if defined(COMPILER_GCC)
    BASE_HASH_NAMESPACE::hash<T> h;
    hash_val_ = h(value());
#elif defined(COMPILER_MSVC)
    hash_val_ = BASE_HASH_NAMESPACE::hash_value(value());
#else
    #error write me
#endif  
  }

  
  const T* value_;

  
  const std::vector<T>* vect_;
  size_t index_;

  size_t hash_val_;
};

template<typename T> inline bool operator==(const UniquifyRef<T>& a,
                                            const UniquifyRef<T>& b) {
  return a.value() == b.value();
}

template<typename T> inline bool operator<(const UniquifyRef<T>& a,
                                           const UniquifyRef<T>& b) {
  return a.value() < b.value();
}

}  

namespace BASE_HASH_NAMESPACE {

#if defined(COMPILER_GCC)
template<typename T> struct hash< internal::UniquifyRef<T> > {
  std::size_t operator()(const internal::UniquifyRef<T>& v) const {
    return v.hash_val();
  }
};
#elif defined(COMPILER_MSVC)
template<typename T>
inline size_t hash_value(const internal::UniquifyRef<T>& v) {
  return v.hash_val();
}
#endif  

}  

template<typename T>
class UniqueVector {
 public:
  typedef std::vector<T> Vector;
  typedef typename Vector::iterator iterator;
  typedef typename Vector::const_iterator const_iterator;

  const Vector& vector() const { return vector_; }
  size_t size() const { return vector_.size(); }
  bool empty() const { return vector_.empty(); }
  void clear() { vector_.clear(); set_.clear(); }
  void reserve(size_t s) { vector_.reserve(s); }

  const T& operator[](size_t index) const { return vector_[index]; }

  const_iterator begin() const { return vector_.begin(); }
  iterator begin() { return vector_.begin(); }
  const_iterator end() const { return vector_.end(); }
  iterator end() { return vector_.end(); }

  
  
  bool push_back(const T& t) {
    Ref ref(&t);
    if (set_.find(ref) != set_.end())
      return false;  

    vector_.push_back(t);
    set_.insert(Ref(&vector_, vector_.size() - 1, ref.hash_val()));
    return true;
  }

  
  bool PushBackViaSwap(T* t) {
    using std::swap;

    Ref ref(t);
    if (set_.find(ref) != set_.end())
      return false;  

    size_t new_index = vector_.size();
    vector_.resize(new_index + 1);
    swap(vector_[new_index], *t);
    set_.insert(Ref(&vector_, vector_.size() - 1, ref.hash_val()));
    return true;
  }

  
  template<typename iter> void Append(const iter& begin, const iter& end) {
    for (iter i = begin; i != end; ++i)
      push_back(*i);
  }

  
  
  size_t IndexOf(const T& t) const {
    Ref ref(&t);
    typename HashSet::const_iterator found = set_.find(ref);
    if (found == set_.end())
      return static_cast<size_t>(-1);
    return found->index();
  }

 private:
  typedef internal::UniquifyRef<T> Ref;
  typedef base::hash_set<Ref> HashSet;

  HashSet set_;
  Vector vector_;
};

#endif  

// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_LABEL_PTR_H_
#define TOOLS_GN_LABEL_PTR_H_

#include <functional>

#include "tools/gn/label.h"

class Config;
class ParseNode;
class Target;

template<typename T>
struct LabelPtrPair {
  typedef T DestType;

  LabelPtrPair() : label(), ptr(NULL), origin(NULL) {}

  explicit LabelPtrPair(const Label& l) : label(l), ptr(NULL), origin(NULL) {
  }

  
  
  explicit LabelPtrPair(const T* p) : label(p->label()), ptr(p), origin(NULL) {
  }

  ~LabelPtrPair() {}

  Label label;
  const T* ptr;  

  
  
  
  const ParseNode* origin;
};

typedef LabelPtrPair<Config> LabelConfigPair;
typedef LabelPtrPair<Target> LabelTargetPair;

typedef std::vector<LabelConfigPair> LabelConfigVector;
typedef std::vector<LabelTargetPair> LabelTargetVector;


template<typename T>
struct LabelPtrLabelEquals : public std::unary_function<Label, bool> {
  explicit LabelPtrLabelEquals(const Label& l) : label(l) {}

  bool operator()(const LabelPtrPair<T>& arg) const {
    return arg.label == label;
  }

  const Label& label;
};

template<typename T>
struct LabelPtrPtrEquals : public std::unary_function<T, bool> {
  explicit LabelPtrPtrEquals(const T* p) : ptr(p) {}

  bool operator()(const LabelPtrPair<T>& arg) const {
    return arg.ptr == ptr;
  }

  const T* ptr;
};

template<typename T>
struct LabelPtrLabelLess : public std::binary_function<LabelPtrPair<T>,
                                                       LabelPtrPair<T>,
                                                       bool> {
  bool operator()(const LabelPtrPair<T>& a, const LabelPtrPair<T>& b) const {
    return a.label < b.label;
  }
};


template<typename T> inline bool operator==(const LabelPtrPair<T>& a,
                                            const LabelPtrPair<T>& b) {
  return a.label == b.label;
}

template<typename T> inline bool operator<(const LabelPtrPair<T>& a,
                                           const LabelPtrPair<T>& b) {
  return a.label < b.label;
}

namespace BASE_HASH_NAMESPACE {

#if defined(COMPILER_GCC)
template<typename T> struct hash< LabelPtrPair<T> > {
  std::size_t operator()(const LabelPtrPair<T>& v) const {
    BASE_HASH_NAMESPACE::hash<Label> h;
    return h(v.label);
  }
};
#elif defined(COMPILER_MSVC)
template<typename T>
inline size_t hash_value(const LabelPtrPair<T>& v) {
  return BASE_HASH_NAMESPACE::hash_value(v.label);
}
#endif  

}  

#endif  

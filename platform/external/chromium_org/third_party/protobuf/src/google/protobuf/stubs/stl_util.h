// Copyright 2008 Google Inc.  All rights reserved.
//     * Redistributions of source code must retain the above copyright
// copyright notice, this list of conditions and the following disclaimer
// this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT


#ifndef GOOGLE_PROTOBUF_STUBS_STL_UTIL_H__
#define GOOGLE_PROTOBUF_STUBS_STL_UTIL_H__

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {

template <class ForwardIterator>
void STLDeleteContainerPointers(ForwardIterator begin,
                                ForwardIterator end) {
  while (begin != end) {
    ForwardIterator temp = begin;
    ++begin;
    delete *temp;
  }
}

inline void STLStringResizeUninitialized(string* s, size_t new_size) {
  s->resize(new_size);
}

inline char* string_as_array(string* str) {
  
  return str->empty() ? NULL : &*str->begin();
}

template <class T>
void STLDeleteElements(T *container) {
  if (!container) return;
  STLDeleteContainerPointers(container->begin(), container->end());
  container->clear();
}


template <class T>
void STLDeleteValues(T *v) {
  if (!v) return;
  for (typename T::iterator i = v->begin(); i != v->end(); ++i) {
    delete i->second;
  }
  v->clear();
}

}  
}  

#endif  
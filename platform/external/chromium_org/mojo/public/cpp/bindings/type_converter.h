// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TYPE_CONVERTER_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TYPE_CONVERTER_H_

namespace mojo {

template <typename T, typename U>
struct TypeConverter;

template <typename T>
struct TypeConverter<T, T> {
  static T Convert(const T& obj) { return obj; }
};

template <typename T, typename U>
inline T ConvertTo(const U& obj) {
  return TypeConverter<T, U>::Convert(obj);
};

}  

#endif  

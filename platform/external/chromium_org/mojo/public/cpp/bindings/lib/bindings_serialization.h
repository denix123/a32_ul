// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_BINDINGS_SERIALIZATION_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_BINDINGS_SERIALIZATION_H_

#include <vector>

#include "mojo/public/cpp/system/core.h"

namespace mojo {
namespace internal {

class BoundsChecker;

const MojoHandle kEncodedInvalidHandleValue = static_cast<MojoHandle>(-1);

size_t Align(size_t size);
char* AlignPointer(char* ptr);

bool IsAligned(const void* ptr);

void EncodePointer(const void* ptr, uint64_t* offset);
const void* DecodePointerRaw(const uint64_t* offset);

template <typename T>
inline void DecodePointer(const uint64_t* offset, T** ptr) {
  *ptr = reinterpret_cast<T*>(const_cast<void*>(DecodePointerRaw(offset)));
}

bool ValidateEncodedPointer(const uint64_t* offset);

void EncodeHandle(Handle* handle, std::vector<Handle>* handles);
void DecodeHandle(Handle* handle, std::vector<Handle>* handles);


template <typename T>
inline void Encode(T* obj, std::vector<Handle>* handles) {
  if (obj->ptr)
    obj->ptr->EncodePointersAndHandles(handles);
  EncodePointer(obj->ptr, &obj->offset);
}

template <typename T>
inline void Decode(T* obj, std::vector<Handle>* handles) {
  DecodePointer(&obj->offset, &obj->ptr);
  if (obj->ptr)
    obj->ptr->DecodePointersAndHandles(handles);
}

bool ValidateStructHeader(const void* data,
                          uint32_t min_num_bytes,
                          uint32_t min_num_fields,
                          BoundsChecker* bounds_checker);

}  
}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_SYSTEM_HANDLE_H_
#define MOJO_PUBLIC_CPP_SYSTEM_HANDLE_H_

#include <assert.h>
#include <limits>

#include "mojo/public/c/system/functions.h"
#include "mojo/public/c/system/types.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {



template <class HandleType>
class ScopedHandleBase {
  MOJO_MOVE_ONLY_TYPE_FOR_CPP_03(ScopedHandleBase, RValue)

 public:
  ScopedHandleBase() {}
  explicit ScopedHandleBase(HandleType handle) : handle_(handle) {}
  ~ScopedHandleBase() { CloseIfNecessary(); }

  template <class CompatibleHandleType>
  explicit ScopedHandleBase(ScopedHandleBase<CompatibleHandleType> other)
      : handle_(other.release()) {
  }

  
  ScopedHandleBase(RValue other) : handle_(other.object->release()) {}
  ScopedHandleBase& operator=(RValue other) {
    if (other.object != this) {
      CloseIfNecessary();
      handle_ = other.object->release();
    }
    return *this;
  }

  const HandleType& get() const { return handle_; }

  template <typename PassedHandleType>
  static ScopedHandleBase<HandleType> From(
      ScopedHandleBase<PassedHandleType> other) {
    MOJO_COMPILE_ASSERT(
        sizeof(static_cast<PassedHandleType*>(static_cast<HandleType*>(0))),
        HandleType_is_not_a_subtype_of_PassedHandleType);
    return ScopedHandleBase<HandleType>(
        static_cast<HandleType>(other.release().value()));
  }

  void swap(ScopedHandleBase& other) {
    handle_.swap(other.handle_);
  }

  HandleType release() MOJO_WARN_UNUSED_RESULT {
    HandleType rv;
    rv.swap(handle_);
    return rv;
  }

  void reset(HandleType handle = HandleType()) {
    CloseIfNecessary();
    handle_ = handle;
  }

  bool is_valid() const {
    return handle_.is_valid();
  }

 private:
  void CloseIfNecessary() {
    if (!handle_.is_valid())
      return;
    MojoResult result MOJO_ALLOW_UNUSED = MojoClose(handle_.value());
    assert(result == MOJO_RESULT_OK);
  }

  HandleType handle_;
};

template <typename HandleType>
inline ScopedHandleBase<HandleType> MakeScopedHandle(HandleType handle) {
  return ScopedHandleBase<HandleType>(handle);
}


const MojoHandle kInvalidHandleValue = MOJO_HANDLE_INVALID;

class Handle {
 public:
  Handle() : value_(kInvalidHandleValue) {}
  explicit Handle(MojoHandle value) : value_(value) {}
  ~Handle() {}

  void swap(Handle& other) {
    MojoHandle temp = value_;
    value_ = other.value_;
    other.value_ = temp;
  }

  bool is_valid() const {
    return value_ != kInvalidHandleValue;
  }

  const MojoHandle& value() const { return value_; }
  MojoHandle* mutable_value() { return &value_; }
  void set_value(MojoHandle value) { value_ = value; }

 private:
  MojoHandle value_;

  
};

MOJO_COMPILE_ASSERT(sizeof(Handle) == sizeof(MojoHandle),
                    bad_size_for_cpp_Handle);

typedef ScopedHandleBase<Handle> ScopedHandle;
MOJO_COMPILE_ASSERT(sizeof(ScopedHandle) == sizeof(Handle),
                    bad_size_for_cpp_ScopedHandle);

inline MojoResult Wait(Handle handle,
                       MojoHandleSignals signals,
                       MojoDeadline deadline) {
  return MojoWait(handle.value(), signals, deadline);
}

template <class HandleVectorType, class FlagsVectorType>
inline MojoResult WaitMany(const HandleVectorType& handles,
                           const FlagsVectorType& signals,
                           MojoDeadline deadline) {
  if (signals.size() != handles.size())
    return MOJO_RESULT_INVALID_ARGUMENT;
  if (handles.size() > std::numeric_limits<uint32_t>::max())
    return MOJO_RESULT_OUT_OF_RANGE;

  if (handles.size() == 0)
    return MojoWaitMany(NULL, NULL, 0, deadline);

  const Handle& first_handle = handles[0];
  const MojoHandleSignals& first_signals = signals[0];
  return MojoWaitMany(
      reinterpret_cast<const MojoHandle*>(&first_handle),
      reinterpret_cast<const MojoHandleSignals*>(&first_signals),
      static_cast<uint32_t>(handles.size()),
      deadline);
}

template <class HandleType>
inline void Close(ScopedHandleBase<HandleType> ) {}

inline MojoResult CloseRaw(Handle handle) {
  return MojoClose(handle.value());
}

inline bool operator<(const Handle a, const Handle b) {
  return a.value() < b.value();
}

}  

#endif  

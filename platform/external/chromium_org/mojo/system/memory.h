// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_MEMORY_H_
#define MOJO_SYSTEM_MEMORY_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>  

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/public/c/system/macros.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

namespace internal {

template <typename T>
struct remove_const {
  typedef T type;
};
template <typename T>
struct remove_const<const T> {
  typedef T type;
};

template <typename T>
struct VoidToChar {
  typedef T type;
};
template <>
struct VoidToChar<void> {
  typedef char type;
};
template <>
struct VoidToChar<const void> {
  typedef const char type;
};

template <size_t size, size_t alignment>
void MOJO_SYSTEM_IMPL_EXPORT CheckUserPointer(const void* pointer);

template <size_t size, size_t alignment>
void MOJO_SYSTEM_IMPL_EXPORT
    CheckUserPointerWithCount(const void* pointer, size_t count);

template <size_t alignment>
void MOJO_SYSTEM_IMPL_EXPORT
    CheckUserPointerWithSize(const void* pointer, size_t size);

}  

template <typename Type>
class UserPointerReader;
template <typename Type>
class UserPointerWriter;
template <typename Type>
class UserPointerReaderWriter;
template <class Options>
class UserOptionsReader;

struct NullUserPointer {};

template <typename Type>
class UserPointer {
 private:
  typedef typename internal::VoidToChar<Type>::type NonVoidType;

 public:
  
  
  
  
  UserPointer() : pointer_(nullptr) {}
  explicit UserPointer(Type* pointer) : pointer_(pointer) {}
  
  UserPointer(NullUserPointer) : pointer_(nullptr) {}
  ~UserPointer() {}

  
  UserPointer<Type>& operator=(NullUserPointer) {
    pointer_ = nullptr;
    return *this;
  }

  
  operator UserPointer<const Type>() const {
    return UserPointer<const Type>(pointer_);
  }

  bool IsNull() const { return !pointer_; }

  
  template <typename ToType>
  UserPointer<ToType> ReinterpretCast() const {
    return UserPointer<ToType>(reinterpret_cast<ToType*>(pointer_));
  }

  
  
  
  
  void Check() const {
    internal::CheckUserPointer<sizeof(NonVoidType), MOJO_ALIGNOF(NonVoidType)>(
        pointer_);
  }

  
  
  
  
  
  
  
  void CheckArray(size_t count) const {
    internal::CheckUserPointerWithCount<sizeof(NonVoidType),
                                        MOJO_ALIGNOF(NonVoidType)>(pointer_,
                                                                   count);
  }

  
  
  
  
  
  
  NonVoidType Get() const {
    Check();
    internal::CheckUserPointer<sizeof(NonVoidType), MOJO_ALIGNOF(NonVoidType)>(
        pointer_);
    return *pointer_;
  }

  
  
  
  
  
  void GetArray(typename internal::remove_const<Type>::type* destination,
                size_t count) const {
    CheckArray(count);
    memcpy(destination, pointer_, count * sizeof(NonVoidType));
  }

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void Put(const NonVoidType& value) {
    Check();
    *pointer_ = value;
  }

  
  
  
  
  
  
  
  void PutArray(const Type* source, size_t count) {
    CheckArray(count);
    memcpy(pointer_, source, count * sizeof(NonVoidType));
  }

  
  UserPointer At(size_t i) const {
    return UserPointer(
        static_cast<Type*>(static_cast<NonVoidType*>(pointer_) + i));
  }

  
  
  
  uintptr_t GetPointerValue() const {
    return reinterpret_cast<uintptr_t>(pointer_);
  }

  
  
  
  
  
  
  
  // guarantee that the changes are written back to user memory (it may be
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  typedef UserPointerReader<Type> Reader;
  typedef UserPointerWriter<Type> Writer;
  typedef UserPointerReaderWriter<Type> ReaderWriter;

 private:
  friend class UserPointerReader<Type>;
  friend class UserPointerReader<const Type>;
  friend class UserPointerWriter<Type>;
  friend class UserPointerReaderWriter<Type>;
  template <class Options>
  friend class UserOptionsReader;

  Type* pointer_;
  
};

template <typename Type>
inline UserPointer<Type> MakeUserPointer(Type* pointer) {
  return UserPointer<Type>(pointer);
}

template <typename Type>
class UserPointerReader {
 private:
  typedef typename internal::remove_const<Type>::type TypeNoConst;

 public:
  
  UserPointerReader(UserPointer<const Type> user_pointer, size_t count) {
    Init(user_pointer.pointer_, count, true);
  }
  UserPointerReader(UserPointer<TypeNoConst> user_pointer, size_t count) {
    Init(user_pointer.pointer_, count, true);
  }

  const Type* GetPointer() const { return buffer_.get(); }

 private:
  template <class Options>
  friend class UserOptionsReader;

  struct NoCheck {};
  UserPointerReader(NoCheck,
                    UserPointer<const Type> user_pointer,
                    size_t count) {
    Init(user_pointer.pointer_, count, false);
  }

  void Init(const Type* user_pointer, size_t count, bool check) {
    if (count == 0)
      return;

    if (check) {
      internal::CheckUserPointerWithCount<sizeof(Type), MOJO_ALIGNOF(Type)>(
          user_pointer, count);
    }
    buffer_.reset(new TypeNoConst[count]);
    memcpy(buffer_.get(), user_pointer, count * sizeof(Type));
  }

  scoped_ptr<TypeNoConst[]> buffer_;

  DISALLOW_COPY_AND_ASSIGN(UserPointerReader);
};

template <typename Type>
class UserPointerWriter {
 public:
  
  UserPointerWriter(UserPointer<Type> user_pointer, size_t count)
      : user_pointer_(user_pointer), count_(count) {
    if (count_ > 0) {
      buffer_.reset(new Type[count_]);
      memset(buffer_.get(), 0, count_ * sizeof(Type));
    }
  }

  Type* GetPointer() const { return buffer_.get(); }

  void Commit() {
    internal::CheckUserPointerWithCount<sizeof(Type), MOJO_ALIGNOF(Type)>(
        user_pointer_.pointer_, count_);
    memcpy(user_pointer_.pointer_, buffer_.get(), count_ * sizeof(Type));
  }

 private:
  UserPointer<Type> user_pointer_;
  size_t count_;
  scoped_ptr<Type[]> buffer_;

  DISALLOW_COPY_AND_ASSIGN(UserPointerWriter);
};

template <typename Type>
class UserPointerReaderWriter {
 public:
  
  UserPointerReaderWriter(UserPointer<Type> user_pointer, size_t count)
      : user_pointer_(user_pointer), count_(count) {
    if (count_ > 0) {
      internal::CheckUserPointerWithCount<sizeof(Type), MOJO_ALIGNOF(Type)>(
          user_pointer_.pointer_, count_);
      buffer_.reset(new Type[count]);
      memcpy(buffer_.get(), user_pointer.pointer_, count * sizeof(Type));
    }
  }

  Type* GetPointer() const { return buffer_.get(); }
  size_t GetCount() const { return count_; }

  void Commit() {
    internal::CheckUserPointerWithCount<sizeof(Type), MOJO_ALIGNOF(Type)>(
        user_pointer_.pointer_, count_);
    memcpy(user_pointer_.pointer_, buffer_.get(), count_ * sizeof(Type));
  }

 private:
  UserPointer<Type> user_pointer_;
  size_t count_;
  scoped_ptr<Type[]> buffer_;

  DISALLOW_COPY_AND_ASSIGN(UserPointerReaderWriter);
};

}  
}  

#endif  

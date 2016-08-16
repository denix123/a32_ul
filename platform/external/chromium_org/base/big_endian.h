// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_BIG_ENDIAN_H_
#define BASE_BIG_ENDIAN_H_

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/strings/string_piece.h"

namespace base {

template<typename T>
inline void ReadBigEndian(const char buf[], T* out) {
  *out = buf[0];
  for (size_t i = 1; i < sizeof(T); ++i) {
    *out <<= 8;
    
    *out |= static_cast<uint8>(buf[i]);
  }
}

template<typename T>
inline void WriteBigEndian(char buf[], T val) {
  for (size_t i = 0; i < sizeof(T); ++i) {
    buf[sizeof(T)-i-1] = static_cast<char>(val & 0xFF);
    val >>= 8;
  }
}

template<>
inline void ReadBigEndian<uint8>(const char buf[], uint8* out) {
  *out = buf[0];
}

template<>
inline void WriteBigEndian<uint8>(char buf[], uint8 val) {
  buf[0] = static_cast<char>(val);
}

class BASE_EXPORT BigEndianReader {
 public:
  BigEndianReader(const char* buf, size_t len);

  const char* ptr() const { return ptr_; }
  int remaining() const { return end_ - ptr_; }

  bool Skip(size_t len);
  bool ReadBytes(void* out, size_t len);
  
  bool ReadPiece(base::StringPiece* out, size_t len);
  bool ReadU8(uint8* value);
  bool ReadU16(uint16* value);
  bool ReadU32(uint32* value);
  bool ReadU64(uint64* value);

 private:
  
  template<typename T>
  bool Read(T* v);

  const char* ptr_;
  const char* end_;
};

class BASE_EXPORT BigEndianWriter {
 public:
  BigEndianWriter(char* buf, size_t len);

  char* ptr() const { return ptr_; }
  int remaining() const { return end_ - ptr_; }

  bool Skip(size_t len);
  bool WriteBytes(const void* buf, size_t len);
  bool WriteU8(uint8 value);
  bool WriteU16(uint16 value);
  bool WriteU32(uint32 value);
  bool WriteU64(uint64 value);

 private:
  
  template<typename T>
  bool Write(T v);

  char* ptr_;
  char* end_;
};

}  

#endif  

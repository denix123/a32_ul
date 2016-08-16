// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_BITSET_32_H_
#define UI_EVENTS_GESTURE_DETECTION_BITSET_32_H_

#include "base/basictypes.h"
#include "base/logging.h"

namespace ui {

struct BitSet32 {
  uint32_t value;

  inline BitSet32() : value(0) {}
  explicit inline BitSet32(uint32_t value) : value(value) {}

  
  static inline uint32_t value_for_bit(uint32_t n) {
    DCHECK_LE(n, 31U);
    return 0x80000000 >> n;
  }

  
  inline void clear() { value = 0; }

  
  inline uint32_t count() const { return popcnt(value); }

  
  inline bool is_empty() const { return !value; }

  
  inline bool is_full() const { return value == 0xffffffff; }

  
  inline bool has_bit(uint32_t n) const {
    return (value & value_for_bit(n)) != 0;
  }

  
  inline void mark_bit(uint32_t n) { value |= value_for_bit(n); }

  
  inline void clear_bit(uint32_t n) { value &= ~value_for_bit(n); }

  
  
  inline uint32_t first_marked_bit() const { return clz(value); }

  
  
  inline uint32_t first_unmarked_bit() const { return clz(~value); }

  
  
  inline uint32_t last_marked_bit() const { return 31 - ctz(value); }

  
  
  
  inline uint32_t clear_first_marked_bit() {
    uint32_t n = first_marked_bit();
    clear_bit(n);
    return n;
  }

  
  
  
  inline uint32_t mark_first_unmarked_bit() {
    uint32_t n = first_unmarked_bit();
    mark_bit(n);
    return n;
  }

  
  
  inline uint32_t clear_last_marked_bit() {
    uint32_t n = last_marked_bit();
    clear_bit(n);
    return n;
  }

  
  
  inline uint32_t get_index_of_bit(uint32_t n) const {
    DCHECK_LE(n, 31U);
    return popcnt(value & ~(0xffffffffUL >> n));
  }

  inline bool operator==(const BitSet32& other) const {
    return value == other.value;
  }
  inline bool operator!=(const BitSet32& other) const {
    return value != other.value;
  }

 private:
#if defined(COMPILER_GCC) || defined(__clang__)
  static inline uint32_t popcnt(uint32_t v) { return __builtin_popcount(v); }
  static inline uint32_t clz(uint32_t v) { return __builtin_clz(v); }
  static inline uint32_t ctz(uint32_t v) { return __builtin_ctz(v); }
#else
  
  static inline uint32_t popcnt(uint32_t v) {
    v = v - ((v >> 1) & 0x55555555);
    v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
    return (((v + (v >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
  }
  
  static inline uint32_t clz(uint32_t v) {
    v |= (v >> 1);
    v |= (v >> 2);
    v |= (v >> 4);
    v |= (v >> 8);
    v |= (v >> 16);
    return 32 - popcnt(v);
  }
  static inline uint32_t ctz(uint32_t v) {
    return popcnt((v & static_cast<uint32_t>(-static_cast<int>(v))) - 1);
  }
#endif
};

}  

#endif  

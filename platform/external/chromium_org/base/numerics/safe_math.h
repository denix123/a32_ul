// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_SAFE_MATH_H_
#define BASE_SAFE_MATH_H_

#include "base/numerics/safe_math_impl.h"

namespace base {

namespace internal {

template <typename T>
class CheckedNumeric {
 public:
  typedef T type;

  CheckedNumeric() {}

  
  template <typename Src>
  CheckedNumeric(const CheckedNumeric<Src>& rhs)
      : state_(rhs.ValueUnsafe(), rhs.validity()) {}

  template <typename Src>
  CheckedNumeric(Src value, RangeConstraint validity)
      : state_(value, validity) {}

  
  
  template <typename Src>
  CheckedNumeric(Src value)
      : state_(value) {
    COMPILE_ASSERT(std::numeric_limits<Src>::is_specialized,
                   argument_must_be_numeric);
  }

  
  bool IsValid() const { return validity() == RANGE_VALID; }

  
  
  T ValueOrDie() const {
    CHECK(IsValid());
    return state_.value();
  }

  
  
  
  T ValueOrDefault(T default_value) const {
    return IsValid() ? state_.value() : default_value;
  }

  
  
  
  T ValueFloating() const {
    COMPILE_ASSERT(std::numeric_limits<T>::is_iec559, argument_must_be_float);
    return CheckedNumeric<T>::cast(*this).ValueUnsafe();
  }

  
  
  
  
  
  
  
  RangeConstraint validity() const { return state_.validity(); }

  
  
  
  
  
  
  
  T ValueUnsafe() const { return state_.value(); }

  
  template <typename Src> CheckedNumeric& operator+=(Src rhs);
  template <typename Src> CheckedNumeric& operator-=(Src rhs);
  template <typename Src> CheckedNumeric& operator*=(Src rhs);
  template <typename Src> CheckedNumeric& operator/=(Src rhs);
  template <typename Src> CheckedNumeric& operator%=(Src rhs);

  CheckedNumeric operator-() const {
    RangeConstraint validity;
    T value = CheckedNeg(state_.value(), &validity);
    
    if (std::numeric_limits<T>::is_iec559)
      return CheckedNumeric<T>(value);

    validity = GetRangeConstraint(state_.validity() | validity);
    return CheckedNumeric<T>(value, validity);
  }

  CheckedNumeric Abs() const {
    RangeConstraint validity;
    T value = CheckedAbs(state_.value(), &validity);
    
    if (std::numeric_limits<T>::is_iec559)
      return CheckedNumeric<T>(value);

    validity = GetRangeConstraint(state_.validity() | validity);
    return CheckedNumeric<T>(value, validity);
  }

  CheckedNumeric& operator++() {
    *this += 1;
    return *this;
  }

  CheckedNumeric operator++(int) {
    CheckedNumeric value = *this;
    *this += 1;
    return value;
  }

  CheckedNumeric& operator--() {
    *this -= 1;
    return *this;
  }

  CheckedNumeric operator--(int) {
    CheckedNumeric value = *this;
    *this -= 1;
    return value;
  }

  
  
  
  template <typename Src>
  static CheckedNumeric<T> cast(
      Src u,
      typename enable_if<std::numeric_limits<Src>::is_specialized, int>::type =
          0) {
    return u;
  }

  template <typename Src>
  static CheckedNumeric<T> cast(
      const CheckedNumeric<Src>& u,
      typename enable_if<!is_same<Src, T>::value, int>::type = 0) {
    return u;
  }

  static const CheckedNumeric<T>& cast(const CheckedNumeric<T>& u) { return u; }

 private:
  CheckedNumericState<T> state_;
};

#define BASE_NUMERIC_ARITHMETIC_OPERATORS(NAME, OP, COMPOUND_OP)              \
        \
  template <typename T>                                                       \
  CheckedNumeric<typename ArithmeticPromotion<T>::type> operator OP(          \
      const CheckedNumeric<T>& lhs, const CheckedNumeric<T>& rhs) {           \
    typedef typename ArithmeticPromotion<T>::type Promotion;                  \
                               \
    if (std::numeric_limits<T>::is_iec559)                                    \
      return CheckedNumeric<T>(lhs.ValueUnsafe() OP rhs.ValueUnsafe());       \
    if (IsIntegerArithmeticSafe<Promotion, T, T>::value)                      \
      return CheckedNumeric<Promotion>(                                       \
          lhs.ValueUnsafe() OP rhs.ValueUnsafe(),                             \
          GetRangeConstraint(rhs.validity() | lhs.validity()));               \
    RangeConstraint validity = RANGE_VALID;                                   \
    T result = Checked##NAME(static_cast<Promotion>(lhs.ValueUnsafe()),       \
                             static_cast<Promotion>(rhs.ValueUnsafe()),       \
                             &validity);                                      \
    return CheckedNumeric<Promotion>(                                         \
        result,                                                               \
        GetRangeConstraint(validity | lhs.validity() | rhs.validity()));      \
  }                                                                           \
      \
  template <typename T>                                                       \
  template <typename Src>                                                     \
  CheckedNumeric<T>& CheckedNumeric<T>::operator COMPOUND_OP(Src rhs) {       \
    *this = CheckedNumeric<T>::cast(*this) OP CheckedNumeric<Src>::cast(rhs); \
    return *this;                                                             \
  }                                                                           \
        \
  template <typename T, typename Src>                                         \
  CheckedNumeric<typename ArithmeticPromotion<T, Src>::type> operator OP(     \
      const CheckedNumeric<Src>& lhs, const CheckedNumeric<T>& rhs) {         \
    typedef typename ArithmeticPromotion<T, Src>::type Promotion;             \
    if (IsIntegerArithmeticSafe<Promotion, T, Src>::value)                    \
      return CheckedNumeric<Promotion>(                                       \
          lhs.ValueUnsafe() OP rhs.ValueUnsafe(),                             \
          GetRangeConstraint(rhs.validity() | lhs.validity()));               \
    return CheckedNumeric<Promotion>::cast(lhs)                               \
        OP CheckedNumeric<Promotion>::cast(rhs);                              \
  }                                                                           \
   \
  template <typename T, typename Src>                                         \
  CheckedNumeric<typename ArithmeticPromotion<T, Src>::type> operator OP(     \
      const CheckedNumeric<T>& lhs, Src rhs) {                                \
    typedef typename ArithmeticPromotion<T, Src>::type Promotion;             \
    if (IsIntegerArithmeticSafe<Promotion, T, Src>::value)                    \
      return CheckedNumeric<Promotion>(lhs.ValueUnsafe() OP rhs,              \
                                       lhs.validity());                       \
    return CheckedNumeric<Promotion>::cast(lhs)                               \
        OP CheckedNumeric<Promotion>::cast(rhs);                              \
  }                                                                           \
   \
  template <typename T, typename Src>                                         \
  CheckedNumeric<typename ArithmeticPromotion<T, Src>::type> operator OP(     \
      Src lhs, const CheckedNumeric<T>& rhs) {                                \
    typedef typename ArithmeticPromotion<T, Src>::type Promotion;             \
    if (IsIntegerArithmeticSafe<Promotion, T, Src>::value)                    \
      return CheckedNumeric<Promotion>(lhs OP rhs.ValueUnsafe(),              \
                                       rhs.validity());                       \
    return CheckedNumeric<Promotion>::cast(lhs)                               \
        OP CheckedNumeric<Promotion>::cast(rhs);                              \
  }

BASE_NUMERIC_ARITHMETIC_OPERATORS(Add, +, += )
BASE_NUMERIC_ARITHMETIC_OPERATORS(Sub, -, -= )
BASE_NUMERIC_ARITHMETIC_OPERATORS(Mul, *, *= )
BASE_NUMERIC_ARITHMETIC_OPERATORS(Div, /, /= )
BASE_NUMERIC_ARITHMETIC_OPERATORS(Mod, %, %= )

#undef BASE_NUMERIC_ARITHMETIC_OPERATORS

}  

using internal::CheckedNumeric;

}  

#endif  

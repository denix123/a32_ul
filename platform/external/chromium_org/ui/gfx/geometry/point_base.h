// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_GEOMETRY_POINT_BASE_H_
#define UI_GFX_GEOMETRY_POINT_BASE_H_

#include <string>

#include "base/compiler_specific.h"
#include "build/build_config.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

template<typename Class, typename Type, typename VectorClass>
class GFX_EXPORT PointBase {
 public:
  Type x() const { return x_; }
  Type y() const { return y_; }

  void SetPoint(Type x, Type y) {
    x_ = x;
    y_ = y;
  }

  void set_x(Type x) { x_ = x; }
  void set_y(Type y) { y_ = y; }

  void Offset(Type delta_x, Type delta_y) {
    x_ += delta_x;
    y_ += delta_y;
  }

  void operator+=(const VectorClass& vector) {
    x_ += vector.x();
    y_ += vector.y();
  }

  void operator-=(const VectorClass& vector) {
    x_ -= vector.x();
    y_ -= vector.y();
  }

  void SetToMin(const Class& other) {
    x_ = x_ <= other.x_ ? x_ : other.x_;
    y_ = y_ <= other.y_ ? y_ : other.y_;
  }

  void SetToMax(const Class& other) {
    x_ = x_ >= other.x_ ? x_ : other.x_;
    y_ = y_ >= other.y_ ? y_ : other.y_;
  }

  bool IsOrigin() const {
    return x_ == 0 && y_ == 0;
  }

  VectorClass OffsetFromOrigin() const {
    return VectorClass(x_, y_);
  }

  
  
  
  
  
  
  bool operator<(const Class& rhs) const {
    return (y_ == rhs.y_) ? (x_ < rhs.x_) : (y_ < rhs.y_);
  }

 protected:
  PointBase(Type x, Type y) : x_(x), y_(y) {}
  
  
  ~PointBase() {}

 private:
  Type x_;
  Type y_;
};

}  

#endif  
// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_RECT_H_
#define PPAPI_CPP_RECT_H_

#include "ppapi/c/pp_rect.h"
#include "ppapi/cpp/point.h"
#include "ppapi/cpp/size.h"


namespace pp {

class Rect {
 public:

  
  
  Rect() {
    rect_.point.x = 0;
    rect_.point.y = 0;
    rect_.size.width = 0;
    rect_.size.height = 0;
  }

  
  
  
  
  
  Rect(const PP_Rect& rect) {  
    set_x(rect.point.x);
    set_y(rect.point.y);
    set_width(rect.size.width);
    set_height(rect.size.height);
  }

  
  
  
  
  
  
  Rect(int32_t w, int32_t h) {
    set_x(0);
    set_y(0);
    set_width(w);
    set_height(h);
  }

  
  
  
  
  
  
  
  
  Rect(int32_t x, int32_t y, int32_t w, int32_t h) {
    set_x(x);
    set_y(y);
    set_width(w);
    set_height(h);
  }

  
  
  
  
  
  explicit Rect(const Size& s) {
    set_x(0);
    set_y(0);
    set_size(s);
  }

  
  
  
  
  
  
  
  
  Rect(const Point& origin, const Size& size) {
    set_point(origin);
    set_size(size);
  }

  
  ~Rect() {
  }

  
  
  
  
  operator PP_Rect() const {
    return rect_;
  }

  
  
  
  const PP_Rect& pp_rect() const {
    return rect_;
  }

  
  
  
  PP_Rect& pp_rect() {
    return rect_;
  }


  
  
  
  int32_t x() const {
    return rect_.point.x;
  }

  
  
  
  void set_x(int32_t in_x) {
    rect_.point.x = in_x;
  }

  
  
  
  int32_t y() const {
    return rect_.point.y;
  }

  
  
  
  void set_y(int32_t in_y) {
    rect_.point.y = in_y;
  }

  
  
  
  int32_t width() const {
    return rect_.size.width;
  }

  
  
  
  void set_width(int32_t w) {
    if (w < 0) {
      PP_DCHECK(w >= 0);
      w = 0;
    }
    rect_.size.width = w;
  }

  
  
  
  int32_t height() const {
    return rect_.size.height;
  }

  
  
  
  void set_height(int32_t h) {
    if (h < 0) {
      PP_DCHECK(h >= 0);
      h = 0;
    }
    rect_.size.height = h;
  }

  
  
  
  Point point() const {
    return Point(rect_.point);
  }

  
  
  
  
  void set_point(const Point& origin) {
    rect_.point = origin;
  }

  
  
  
  Size size() const {
    return Size(rect_.size);
  }

  
  
  
  
  void set_size(const Size& s) {
    rect_.size.width = s.width();
    rect_.size.height = s.height();
  }

  
  
  
  
  
  
  
  int32_t right() const {
    return x() + width();
  }

  
  
  
  
  
  
  
  int32_t bottom() const {
    return y() + height();
  }

  
  
  
  
  
  
  void SetRect(int32_t x, int32_t y, int32_t w, int32_t h) {
    set_x(x);
    set_y(y);
    set_width(w);
    set_height(h);
  }

  
  
  
  void SetRect(const PP_Rect& rect) {
    rect_ = rect;
  }

  
  
  
  
  
  
  
  void Inset(int32_t horizontal, int32_t vertical) {
    Inset(horizontal, vertical, horizontal, vertical);
  }

  
  
  
  
  
  
  
  
  
  
  
  void Inset(int32_t left, int32_t top, int32_t right, int32_t bottom);

  
  
  
  
  
  
  void Offset(int32_t horizontal, int32_t vertical);

  
  
  
  
  void Offset(const Point& point) {
    Offset(point.x(), point.y());
  }

  
  
  
  
  bool IsEmpty() const {
    return rect_.size.width == 0 || rect_.size.height == 0;
  }

  
  
  
  
  
  
  
  
  bool Contains(int32_t point_x, int32_t point_y) const;

  
  
  
  
  
  
  bool Contains(const Point& point) const {
    return Contains(point.x(), point.y());
  }

  
  
  
  
  
  bool Contains(const Rect& rect) const;

  
  
  
  
  
  
  bool Intersects(const Rect& rect) const;

  
  
  
  
  
  
  Rect Intersect(const Rect& rect) const;

  
  
  
  
  
  
  Rect Union(const Rect& rect) const;

  
  
  
  
  
  
  
  
  
  Rect Subtract(const Rect& rect) const;

  
  
  
  
  
  
  
  
  
  
  Rect AdjustToFit(const Rect& rect) const;

  
  
  
  Point CenterPoint() const;

  
  
  
  
  
  
  
  bool SharesEdgeWith(const Rect& rect) const;

 private:
  PP_Rect rect_;
};

class FloatRect {
 public:

  
  
  FloatRect() {
    rect_.point.x = 0.0f;
    rect_.point.y = 0.0f;
    rect_.size.width = 0.0f;
    rect_.size.height = 0.0f;
  }

  
  
  
  
  
  FloatRect(const PP_FloatRect& rect) {  
    set_x(rect.point.x);
    set_y(rect.point.y);
    set_width(rect.size.width);
    set_height(rect.size.height);
  }

  
  
  
  
  
  
  FloatRect(float w, float h) {
    set_x(0);
    set_y(0);
    set_width(w);
    set_height(h);
  }

  
  
  
  
  
  
  
  
  FloatRect(float x, float y, float w, float h) {
    set_x(x);
    set_y(y);
    set_width(w);
    set_height(h);
  }

  
  
  
  
  
  explicit FloatRect(const FloatSize& s) {
    set_x(0);
    set_y(0);
    set_size(s);
  }

  
  
  
  
  
  
  
  
  FloatRect(const FloatPoint& origin, const FloatSize& size) {
    set_point(origin);
    set_size(size);
  }

  
  ~FloatRect() {
  }

  
  
  
  
  operator PP_FloatRect() const {
    return rect_;
  }

  
  
  
  
  
  const PP_FloatRect& pp_float_rect() const {
    return rect_;
  }

  
  
  
  
  PP_FloatRect& pp_float_rect() {
    return rect_;
  }


  
  
  
  float x() const {
    return rect_.point.x;
  }

  
  
  
  void set_x(float in_x) {
    rect_.point.x = in_x;
  }

  
  
  
  float y() const {
    return rect_.point.y;
  }

  
  
  
  void set_y(float in_y) {
    rect_.point.y = in_y;
  }

  
  
  
  float width() const {
    return rect_.size.width;
  }

  
  
  
  void set_width(float w) {
    if (w < 0.0f) {
      PP_DCHECK(w >= 0.0f);
      w = 0.0f;
    }
    rect_.size.width = w;
  }

  
  
  
  float height() const {
    return rect_.size.height;
  }

  
  
  
  void set_height(float h) {
    if (h < 0.0f) {
      PP_DCHECK(h >= 0.0f);
      h = 0.0f;
    }
    rect_.size.height = h;
  }

  
  
  
  FloatPoint point() const {
    return FloatPoint(rect_.point);
  }

  
  
  
  
  void set_point(const FloatPoint& origin) {
    rect_.point = origin;
  }

  
  
  
  FloatSize Floatsize() const {
    return FloatSize(rect_.size);
  }

  
  
  
  
  void set_size(const FloatSize& s) {
    rect_.size.width = s.width();
    rect_.size.height = s.height();
  }

  
  
  
  
  
  
  
  float right() const {
    return x() + width();
  }

  
  
  
  
  
  
  
  float bottom() const {
    return y() + height();
  }

  
  
  
  
  
  
  void SetRect(float x, float y, float w, float h) {
    set_x(x);
    set_y(y);
    set_width(w);
    set_height(h);
  }

  
  
  
  void SetRect(const PP_FloatRect& rect) {
    rect_ = rect;
  }

  
  
  
  
  
  
  
  void Inset(float horizontal, float vertical) {
    Inset(horizontal, vertical, horizontal, vertical);
  }

  
  
  
  
  
  
  
  
  
  
  
  void Inset(float left, float top, float right, float bottom);

  
  
  
  
  
  
  void Offset(float horizontal, float vertical);

  
  
  
  
  void Offset(const FloatPoint& point) {
    Offset(point.x(), point.y());
  }

  
  
  
  
  bool IsEmpty() const {
    return rect_.size.width == 0.0f || rect_.size.height == 0.0f;
  }

  
  
  
  
  
  
  
  
  bool Contains(float point_x, float point_y) const;

  
  
  
  
  
  
  bool Contains(const FloatPoint& point) const {
    return Contains(point.x(), point.y());
  }

  
  
  
  
  
  bool Contains(const FloatRect& rect) const;

  
  
  
  
  
  
  bool Intersects(const FloatRect& rect) const;

  
  
  
  
  
  
  FloatRect Intersect(const FloatRect& rect) const;

  
  
  
  
  
  
  FloatRect Union(const FloatRect& rect) const;

  
  
  
  
  
  
  
  
  
  FloatRect Subtract(const FloatRect& rect) const;

  
  
  
  
  
  
  
  
  
  
  FloatRect AdjustToFit(const FloatRect& rect) const;

  
  
  
  
  FloatPoint CenterPoint() const;

  
  
  
  
  
  
  
  bool SharesEdgeWith(const FloatRect& rect) const;

 private:
  PP_FloatRect rect_;
};

}  

inline bool operator==(const pp::Rect& lhs, const pp::Rect& rhs) {
  return lhs.x() == rhs.x() &&
         lhs.y() == rhs.y() &&
         lhs.width() == rhs.width() &&
         lhs.height() == rhs.height();
}

inline bool operator!=(const pp::Rect& lhs, const pp::Rect& rhs) {
  return !(lhs == rhs);
}

inline bool operator==(const pp::FloatRect& lhs, const pp::FloatRect& rhs) {
  return lhs.x() == rhs.x() &&
         lhs.y() == rhs.y() &&
         lhs.width() == rhs.width() &&
         lhs.height() == rhs.height();
}

inline bool operator!=(const pp::FloatRect& lhs, const pp::FloatRect& rhs) {
  return !(lhs == rhs);
}

#endif


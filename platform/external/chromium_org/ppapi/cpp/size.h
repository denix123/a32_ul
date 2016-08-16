// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_SIZE_H_
#define PPAPI_CPP_SIZE_H_

#include "ppapi/c/pp_size.h"
#include "ppapi/cpp/logging.h"


namespace pp {

class Size {
 public:

  
  Size() {
    size_.width = 0;
    size_.height = 0;
  }

  
  
  
  
  
  Size(const PP_Size& s) {  
    
    set_width(s.width);
    set_height(s.height);
  }

  
  
  
  
  
  Size(int w, int h) {
    
    set_width(w);
    set_height(h);
  }

  
  ~Size() {
  }

  
  
  
  
  operator PP_Size() {
    return size_;
  }

  
  
  
  const PP_Size& pp_size() const {
    return size_;
  }

  
  
  
  PP_Size& pp_size() {
    return size_;
  }

  
  
  
  int width() const {
    return size_.width;
  }

  
  
  
  void set_width(int w) {
    if (w < 0) {
      PP_DCHECK(w >= 0);
      w = 0;
    }
    size_.width = w;
  }

  
  
  
  int height() const {
    return size_.height;
  }

  
  
  
  void set_height(int h) {
    if (h < 0) {
      PP_DCHECK(h >= 0);
      h = 0;
    }
    size_.height = h;
  }

  
  
  
  int GetArea() const {
    return width() * height();
  }

  
  
  
  
  void SetSize(int w, int h) {
    set_width(w);
    set_height(h);
  }

  
  
  
  
  void Enlarge(int w, int h) {
    set_width(width() + w);
    set_height(height() + h);
  }

  
  
  
  bool IsEmpty() const {
    
    return (width() == 0) || (height() == 0);
  }

 private:
  PP_Size size_;
};

class FloatSize {
 public:

  
  FloatSize() {
    size_.width = 0.0f;
    size_.height = 0.0f;
  }

  
  
  
  
  
  FloatSize(const PP_FloatSize& s) {  
    
    set_width(s.width);
    set_height(s.height);
  }

  
  
  
  
  
  FloatSize(float w, float h) {
    
    set_width(w);
    set_height(h);
  }

  
  ~FloatSize() {
  }

  
  
  
  
  operator PP_FloatSize() {
    return size_;
  }

  
  
  
  
  
  const PP_FloatSize& pp_float_size() const {
    return size_;
  }

  
  
  
  
  PP_FloatSize& pp_float_size() {
    return size_;
  }

  
  
  
  float width() const {
    return size_.width;
  }

  
  
  
  void set_width(float w) {
    if (w < 0.0f) {
      PP_DCHECK(w >= 0.0f);
      w = 0.0f;
    }
    size_.width = w;
  }

  
  
  
  float height() const {
    return size_.height;
  }

  
  
  
  void set_height(float h) {
    if (h < 0.0f) {
      PP_DCHECK(h >= 0.0f);
      h = 0.0f;
    }
    size_.height = h;
  }

  
  
  
  float GetArea() const {
    return width() * height();
  }

  
  
  
  
  void SetSize(float w, float h) {
    set_width(w);
    set_height(h);
  }

  
  
  
  
  void Enlarge(float w, float h) {
    set_width(width() + w);
    set_height(height() + h);
  }

  
  
  
  bool IsEmpty() const {
    
    return (width() == 0.0f) || (height() == 0.0f);
  }

 private:
  PP_FloatSize size_;
};

}  

inline bool operator==(const pp::Size& lhs, const pp::Size& rhs) {
  return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

inline bool operator!=(const pp::Size& lhs, const pp::Size& rhs) {
  return !(lhs == rhs);
}

inline bool operator==(const pp::FloatSize& lhs, const pp::FloatSize& rhs) {
  return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

inline bool operator!=(const pp::FloatSize& lhs, const pp::FloatSize& rhs) {
  return !(lhs == rhs);
}

#endif  


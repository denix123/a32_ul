// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_GEOMETRY_CUBIC_BEZIER_H_
#define UI_GFX_GEOMETRY_CUBIC_BEZIER_H_

#include "base/macros.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class GFX_EXPORT CubicBezier {
 public:
  CubicBezier(double x1, double y1, double x2, double y2);
  ~CubicBezier();

  
  double Solve(double x) const;

  
  double Slope(double x) const;

  
  
  void Range(double* min, double* max) const;

 private:
  double x1_;
  double y1_;
  double x2_;
  double y2_;

  DISALLOW_ASSIGN(CubicBezier);
};

}  

#endif  

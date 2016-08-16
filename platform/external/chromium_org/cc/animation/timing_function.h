// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_ANIMATION_TIMING_FUNCTION_H_
#define CC_ANIMATION_TIMING_FUNCTION_H_

#include "cc/base/cc_export.h"
#include "ui/gfx/geometry/cubic_bezier.h"

namespace cc {

class CC_EXPORT TimingFunction {
 public:
  virtual ~TimingFunction();

  virtual float GetValue(double t) const = 0;
  virtual float Velocity(double time) const = 0;
  
  virtual void Range(float* min, float* max) const = 0;
  virtual scoped_ptr<TimingFunction> Clone() const = 0;

 protected:
  TimingFunction();

 private:
  DISALLOW_ASSIGN(TimingFunction);
};

class CC_EXPORT CubicBezierTimingFunction : public TimingFunction {
 public:
  static scoped_ptr<CubicBezierTimingFunction> Create(double x1, double y1,
                                                      double x2, double y2);
  virtual ~CubicBezierTimingFunction();

  
  virtual float GetValue(double time) const OVERRIDE;
  virtual float Velocity(double time) const OVERRIDE;
  virtual void Range(float* min, float* max) const OVERRIDE;
  virtual scoped_ptr<TimingFunction> Clone() const OVERRIDE;

 protected:
  CubicBezierTimingFunction(double x1, double y1, double x2, double y2);

  gfx::CubicBezier bezier_;

 private:
  DISALLOW_ASSIGN(CubicBezierTimingFunction);
};

class CC_EXPORT EaseTimingFunction {
 public:
  static scoped_ptr<TimingFunction> Create();

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(EaseTimingFunction);
};

class CC_EXPORT EaseInTimingFunction {
 public:
  static scoped_ptr<TimingFunction> Create();

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(EaseInTimingFunction);
};

class CC_EXPORT EaseOutTimingFunction {
 public:
  static scoped_ptr<TimingFunction> Create();

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(EaseOutTimingFunction);
};

class CC_EXPORT EaseInOutTimingFunction {
 public:
  static scoped_ptr<TimingFunction> Create();

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(EaseInOutTimingFunction);
};

}  

#endif  

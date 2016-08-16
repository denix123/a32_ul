// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_BASE_MATH_UTIL_H_
#define CC_BASE_MATH_UTIL_H_

#include <algorithm>
#include <cmath>
#include <vector>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"
#include "ui/gfx/box_f.h"
#include "ui/gfx/point3_f.h"
#include "ui/gfx/point_f.h"
#include "ui/gfx/size.h"
#include "ui/gfx/transform.h"

namespace base {
class Value;
namespace debug {
class TracedValue;
}
}

namespace gfx {
class QuadF;
class Rect;
class RectF;
class Transform;
class Vector2dF;
class Vector2d;
}

namespace cc {

struct HomogeneousCoordinate {
  HomogeneousCoordinate(SkMScalar x, SkMScalar y, SkMScalar z, SkMScalar w) {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;
  }

  bool ShouldBeClipped() const { return w() <= 0.0; }

  gfx::PointF CartesianPoint2d() const {
    if (w() == SK_MScalar1)
      return gfx::PointF(x(), y());

    
    
    DCHECK(w());
    SkMScalar inv_w = SK_MScalar1 / w();
    return gfx::PointF(x() * inv_w, y() * inv_w);
  }

  gfx::Point3F CartesianPoint3d() const {
    if (w() == SK_MScalar1)
      return gfx::Point3F(x(), y(), z());

    
    
    DCHECK(w());
    SkMScalar inv_w = SK_MScalar1 / w();
    return gfx::Point3F(x() * inv_w, y() * inv_w, z() * inv_w);
  }

  SkMScalar x() const { return vec[0]; }
  SkMScalar y() const { return vec[1]; }
  SkMScalar z() const { return vec[2]; }
  SkMScalar w() const { return vec[3]; }

  SkMScalar vec[4];
};

class CC_EXPORT MathUtil {
 public:
  static const double kPiDouble;
  static const float kPiFloat;

  static double Deg2Rad(double deg) { return deg * kPiDouble / 180.0; }
  static double Rad2Deg(double rad) { return rad * 180.0 / kPiDouble; }

  static float Deg2Rad(float deg) { return deg * kPiFloat / 180.0f; }
  static float Rad2Deg(float rad) { return rad * 180.0f / kPiFloat; }

  static float Round(float f) {
    return (f > 0.f) ? std::floor(f + 0.5f) : std::ceil(f - 0.5f);
  }
  static double Round(double d) {
    return (d > 0.0) ? std::floor(d + 0.5) : std::ceil(d - 0.5);
  }

  template <typename T> static T ClampToRange(T value, T min, T max) {
    return std::min(std::max(value, min), max);
  }

  
  
  
  
  
  
  
  
  static gfx::Rect MapEnclosingClippedRect(const gfx::Transform& transform,
                                           const gfx::Rect& rect);
  static gfx::RectF MapClippedRect(const gfx::Transform& transform,
                                   const gfx::RectF& rect);
  static gfx::Rect ProjectEnclosingClippedRect(const gfx::Transform& transform,
                                               const gfx::Rect& rect);
  static gfx::RectF ProjectClippedRect(const gfx::Transform& transform,
                                       const gfx::RectF& rect);

  
  
  static gfx::Rect MapEnclosedRectWith2dAxisAlignedTransform(
      const gfx::Transform& transform,
      const gfx::Rect& rect);

  
  
  
  
  
  static void MapClippedQuad(const gfx::Transform& transform,
                             const gfx::QuadF& src_quad,
                             gfx::PointF clipped_quad[8],
                             int* num_vertices_in_clipped_quad);
  static bool MapClippedQuad3d(const gfx::Transform& transform,
                               const gfx::QuadF& src_quad,
                               gfx::Point3F clipped_quad[8],
                               int* num_vertices_in_clipped_quad);

  static gfx::RectF ComputeEnclosingRectOfVertices(const gfx::PointF vertices[],
                                                   int num_vertices);
  static gfx::RectF ComputeEnclosingClippedRect(
      const HomogeneousCoordinate& h1,
      const HomogeneousCoordinate& h2,
      const HomogeneousCoordinate& h3,
      const HomogeneousCoordinate& h4);

  
  
  static gfx::QuadF MapQuad(const gfx::Transform& transform,
                            const gfx::QuadF& quad,
                            bool* clipped);
  static gfx::QuadF MapQuad3d(const gfx::Transform& transform,
                              const gfx::QuadF& q,
                              gfx::Point3F* p,
                              bool* clipped);
  static gfx::PointF MapPoint(const gfx::Transform& transform,
                              const gfx::PointF& point,
                              bool* clipped);
  static gfx::Point3F MapPoint(const gfx::Transform&,
                               const gfx::Point3F&,
                               bool* clipped);
  static gfx::QuadF ProjectQuad(const gfx::Transform& transform,
                                const gfx::QuadF& quad,
                                bool* clipped);
  static gfx::PointF ProjectPoint(const gfx::Transform& transform,
                                  const gfx::PointF& point,
                                  bool* clipped);
  
  
  static gfx::Point3F ProjectPoint3D(const gfx::Transform& transform,
                                     const gfx::PointF& point,
                                     bool* clipped);

  static gfx::Vector2dF ComputeTransform2dScaleComponents(const gfx::Transform&,
                                                          float fallbackValue);

  
  
  
  
  
  static gfx::RectF ScaleRectProportional(const gfx::RectF& input_outer_rect,
                                          const gfx::RectF& scale_outer_rect,
                                          const gfx::RectF& scale_inner_rect);

  
  
  static float SmallestAngleBetweenVectors(const gfx::Vector2dF& v1,
                                           const gfx::Vector2dF& v2);

  
  
  static gfx::Vector2dF ProjectVector(const gfx::Vector2dF& source,
                                      const gfx::Vector2dF& destination);

  
  static scoped_ptr<base::Value> AsValue(const gfx::Size& s);
  static scoped_ptr<base::Value> AsValue(const gfx::Rect& r);
  static bool FromValue(const base::Value*, gfx::Rect* out_rect);
  static scoped_ptr<base::Value> AsValue(const gfx::PointF& q);

  static void AddToTracedValue(const gfx::Size& s,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::SizeF& s,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::Rect& r,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::PointF& q,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::Point3F&,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::Vector2d& v,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::Vector2dF& v,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::QuadF& q,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::RectF& rect,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::Transform& transform,
                               base::debug::TracedValue* res);
  static void AddToTracedValue(const gfx::BoxF& box,
                               base::debug::TracedValue* res);

  
  
  static double AsDoubleSafely(double value);
  static float AsFloatSafely(float value);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_QUADS_DRAW_POLYGON_H_
#define CC_QUADS_DRAW_POLYGON_H_

#include <vector>

#include "cc/base/math_util.h"
#include "cc/output/bsp_compare_result.h"
#include "ui/gfx/point3_f.h"
#include "ui/gfx/quad_f.h"
#include "ui/gfx/rect_f.h"
#include "ui/gfx/transform.h"
#include "ui/gfx/vector3d_f.h"

namespace cc {

class DrawQuad;

class CC_EXPORT DrawPolygon {
 public:
  DrawPolygon();
  ~DrawPolygon();

  DrawPolygon(DrawQuad* original_ref,
              const std::vector<gfx::Point3F>& in_points,
              const gfx::Vector3dF& normal,
              int draw_order_index = 0);
  DrawPolygon(DrawQuad* original_ref,
              const gfx::RectF& visible_content_rect,
              const gfx::Transform& transform,
              int draw_order_index = 0);

  
  
  
  
  
  
  
  bool Split(const DrawPolygon& splitter,
             scoped_ptr<DrawPolygon>* front,
             scoped_ptr<DrawPolygon>* back);
  float SignedPointDistance(const gfx::Point3F& point) const;
  
  
  static BspCompareResult SideCompare(const DrawPolygon& a,
                                      const DrawPolygon& b);
  void ToQuads2D(std::vector<gfx::QuadF>* quads) const;
  void TransformToScreenSpace(const gfx::Transform& transform);
  void TransformToLayerSpace(const gfx::Transform& inverse_transform);

  const std::vector<gfx::Point3F>& points() const { return points_; }
  const gfx::Vector3dF& normal() const { return normal_; }
  const DrawQuad* original_ref() const { return original_ref_; }
  int order_index() const { return order_index_; }

  scoped_ptr<DrawPolygon> CreateCopy();

  static gfx::Vector3dF default_normal;

 private:
  void ApplyTransform(const gfx::Transform& transform);
  void ApplyTransformToNormal(const gfx::Transform& transform);

  std::vector<gfx::Point3F> points_;
  
  gfx::Vector3dF normal_;
  
  
  
  int order_index_;
  
  
  
  
  DrawQuad* original_ref_;
};

}  

#endif  

// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_DRAW_UTILS_H_
#define PDF_DRAW_UTILS_H_

#include <vector>

#include "base/basictypes.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/rect.h"

namespace chrome_pdf {

const uint8 kOpaqueAlpha = 0xFF;
const uint8 kTransparentAlpha = 0x00;

void AlphaBlend(const pp::ImageData& src, const pp::Rect& src_rc,
                pp::ImageData* dest, const pp::Point& dest_origin,
                uint8 alpha_adjustment);

void GradientFill(pp::ImageData* image,
                  const pp::Rect& rc,
                  uint32 start_color,
                  uint32 end_color,
                  bool horizontal);

void GradientFill(pp::Instance* instance,
                  pp::ImageData* image,
                  const pp::Rect& dirty_rc,
                  const pp::Rect& gradient_rc,
                  uint32 start_color,
                  uint32 end_color,
                  bool horizontal,
                  uint8 transparency);

void CopyImage(const pp::ImageData& src, const pp::Rect& src_rc,
               pp::ImageData* dest, const pp::Rect& dest_rc,
               bool stretch);

void FillRect(pp::ImageData* image, const pp::Rect& rc, uint32 color);

class ShadowMatrix {
 public:
  
  
  
  
  
  
  ShadowMatrix(uint32 depth, double factor, uint32 background);

  ~ShadowMatrix();

  uint32 GetValue(int32 x, int32 y) const { return matrix_[y * depth_ + x]; }

  uint32 depth() const { return depth_; }
  double factor() const { return factor_; }
  uint32 background() const { return background_; }

 private:
  uint32 depth_;
  double factor_;
  uint32 background_;
  std::vector<uint32> matrix_;
};

void DrawShadow(pp::ImageData* image,
                const pp::Rect& shadow_rc,
                const pp::Rect& object_rc,
                const pp::Rect& clip_rc,
                const ShadowMatrix& matrix);

}  

#endif  

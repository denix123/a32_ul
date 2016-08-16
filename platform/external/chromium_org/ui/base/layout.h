// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_LAYOUT_H_
#define UI_BASE_LAYOUT_H_

#include <vector>

#include "build/build_config.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {

enum ScaleFactor {
  SCALE_FACTOR_NONE = 0,
  SCALE_FACTOR_100P,
  SCALE_FACTOR_125P,
  SCALE_FACTOR_133P,
  SCALE_FACTOR_140P,
  SCALE_FACTOR_150P,
  SCALE_FACTOR_180P,
  SCALE_FACTOR_200P,
  SCALE_FACTOR_250P,
  SCALE_FACTOR_300P,

  NUM_SCALE_FACTORS  
};

UI_BASE_EXPORT void SetSupportedScaleFactors(
    const std::vector<ScaleFactor>& scale_factors);

UI_BASE_EXPORT const std::vector<ScaleFactor>& GetSupportedScaleFactors();

UI_BASE_EXPORT ScaleFactor GetSupportedScaleFactor(float image_scale);

UI_BASE_EXPORT float GetScaleFactorForNativeView(gfx::NativeView view);

UI_BASE_EXPORT float GetScaleForScaleFactor(ScaleFactor scale_factor);

namespace test {
class UI_BASE_EXPORT ScopedSetSupportedScaleFactors {
 public:
  explicit ScopedSetSupportedScaleFactors(
      const std::vector<ui::ScaleFactor>& new_scale_factors);
  ~ScopedSetSupportedScaleFactors();

 private:
  std::vector<ui::ScaleFactor>* original_scale_factors_;

  DISALLOW_COPY_AND_ASSIGN(ScopedSetSupportedScaleFactors);
};

}  

}  

#endif  

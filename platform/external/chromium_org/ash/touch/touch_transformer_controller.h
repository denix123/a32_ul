// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TOUCH_TOUCH_TRANSFORMER_CONTROLLER_H_
#define ASH_TOUCH_TOUCH_TRANSFORMER_CONTROLLER_H_

#include "ash/ash_export.h"
#include "ash/display/display_controller.h"
#include "ui/gfx/transform.h"

namespace ash {

class ASH_EXPORT TouchTransformerController
    : public DisplayController::Observer {
 public:
  TouchTransformerController();
  virtual ~TouchTransformerController();

  
  
  void UpdateTouchTransformer() const;

  
  virtual void OnDisplaysInitialized() OVERRIDE;
  virtual void OnDisplayConfigurationChanged() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(TouchTransformerControllerTest,
                           TouchTransformerMirrorModeLetterboxing);
  FRIEND_TEST_ALL_PREFIXES(TouchTransformerControllerTest,
                           TouchTransformerMirrorModePillarboxing);
  FRIEND_TEST_ALL_PREFIXES(TouchTransformerControllerTest,
                           TouchTransformerExtendedMode);
  FRIEND_TEST_ALL_PREFIXES(TouchTransformerControllerTest,
                           TouchRadiusScale);

  bool ShouldComputeMirrorModeTouchTransformer(
      const DisplayInfo& touch_display) const ;

  gfx::Transform GetMirrorModeTouchTransformer(
      const DisplayInfo& touch_display) const;

  gfx::Transform GetExtendedModeTouchTransformer(
      const DisplayInfo& touch_display, const gfx::Size& fb_size) const;

  double GetTouchResolutionScale(const DisplayInfo& touch_display) const;

  
  bool force_compute_mirror_mode_touch_transformer_;

  DISALLOW_COPY_AND_ASSIGN(TouchTransformerController);
};

}  

#endif  

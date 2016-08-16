// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_DISPLAY_INFO_H_
#define ASH_DISPLAY_DISPLAY_INFO_H_

#include <string>
#include <vector>

#include "ash/ash_export.h"
#include "ui/display/types/display_constants.h"
#include "ui/gfx/display.h"
#include "ui/gfx/insets.h"
#include "ui/gfx/rect.h"

namespace ash {

struct ASH_EXPORT DisplayMode {
  DisplayMode();
  DisplayMode(const gfx::Size& size,
              float refresh_rate,
              bool interlaced,
              bool native);

  
  gfx::Size GetSizeInDIP() const;

  
  bool IsEquivalent(const DisplayMode& other) const;

  gfx::Size size;      
  float refresh_rate;  
  bool interlaced;     
  bool native;         
  float ui_scale;      
  float device_scale_factor;  
};

class ASH_EXPORT DisplayInfo {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static DisplayInfo CreateFromSpec(const std::string& spec);

  
  static DisplayInfo CreateFromSpecWithID(const std::string& spec,
                                          int64 id);

  DisplayInfo();
  DisplayInfo(int64 id, const std::string& name, bool has_overscan);
  ~DisplayInfo();

  
  
  
  static void SetUse125DSFForUIScaling(bool enable);

  int64 id() const { return id_; }

  
  const std::string& name() const { return name_; }

  
  
  bool has_overscan() const { return has_overscan_; }

  void set_rotation(gfx::Display::Rotation rotation) { rotation_ = rotation; }
  gfx::Display::Rotation rotation() const { return rotation_; }

  void set_touch_support(gfx::Display::TouchSupport support) {
    touch_support_ = support;
  }
  gfx::Display::TouchSupport touch_support() const { return touch_support_; }

  void set_touch_device_id(int id) { touch_device_id_ = id; }
  int touch_device_id() const { return touch_device_id_; }

  
  float device_scale_factor() const { return device_scale_factor_; }
  void set_device_scale_factor(float scale) { device_scale_factor_ = scale; }

  
  
  
  const gfx::Rect& bounds_in_native() const {
    return bounds_in_native_;
  }

  
  const gfx::Size& size_in_pixel() const { return size_in_pixel_; }

  
  const gfx::Insets& overscan_insets_in_dip() const {
    return overscan_insets_in_dip_;
  }

  
  
  
  float configured_ui_scale() const { return configured_ui_scale_; }
  void set_configured_ui_scale(float scale) { configured_ui_scale_ = scale; }

  
  
  
  
  
  
  float GetEffectiveDeviceScaleFactor() const;

  
  
  float GetEffectiveUIScale() const;

  
  
  
  void Copy(const DisplayInfo& another_info);

  
  
  void SetBounds(const gfx::Rect& bounds_in_native);

  
  
  void UpdateDisplaySize();

  
  void SetOverscanInsets(const gfx::Insets& insets_in_dip);
  gfx::Insets GetOverscanInsetsInPixel() const;

  void set_native(bool native) { native_ = native; }
  bool native() const { return native_; }

  const std::vector<DisplayMode>& display_modes() const {
    return display_modes_;
  }
  void set_display_modes(std::vector<DisplayMode>& display_modes) {
    display_modes_.swap(display_modes);
  }

  
  
  gfx::Size GetNativeModeSize() const;

  ui::ColorCalibrationProfile color_profile() const {
    return color_profile_;
  }

  
  
  void SetColorProfile(ui::ColorCalibrationProfile profile);

  
  bool IsColorProfileAvailable(ui::ColorCalibrationProfile profile) const;

  const std::vector<ui::ColorCalibrationProfile>&
      available_color_profiles() const {
    return available_color_profiles_;
  }

  void set_available_color_profiles(
      const std::vector<ui::ColorCalibrationProfile>& profiles) {
    available_color_profiles_ = profiles;
  }

  bool is_aspect_preserving_scaling() const {
    return is_aspect_preserving_scaling_;
  }

  void set_is_aspect_preserving_scaling(bool value) {
    is_aspect_preserving_scaling_ = value;
  }

  
  
  std::string ToString() const;

  
  
  std::string ToFullString() const;

 private:
  int64 id_;
  std::string name_;
  bool has_overscan_;
  gfx::Display::Rotation rotation_;
  gfx::Display::TouchSupport touch_support_;

  
  
  int touch_device_id_;

  
  
  
  
  
  float device_scale_factor_;
  gfx::Rect bounds_in_native_;

  
  
  gfx::Size size_in_pixel_;
  gfx::Insets overscan_insets_in_dip_;

  
  
  
  
  
  
  float configured_ui_scale_;

  
  bool native_;

  
  
  
  bool is_aspect_preserving_scaling_;

  
  std::vector<DisplayMode> display_modes_;

  
  ui::ColorCalibrationProfile color_profile_;

  
  std::vector<ui::ColorCalibrationProfile> available_color_profiles_;
};

}  

#endif  

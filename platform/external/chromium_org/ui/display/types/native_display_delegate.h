// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_TYPES_NATIVE_DISPLAY_DELEGATE_H_
#define UI_DISPLAY_TYPES_NATIVE_DISPLAY_DELEGATE_H_

#include <stdint.h>

#include <vector>

#include "ui/display/types/display_constants.h"
#include "ui/display/types/display_types_export.h"

namespace gfx {
class Point;
class Size;
}

namespace ui {
class DisplayMode;
class DisplaySnapshot;

class NativeDisplayObserver;

class DISPLAY_TYPES_EXPORT NativeDisplayDelegate {
 public:
  virtual ~NativeDisplayDelegate() {}

  virtual void Initialize() = 0;

  
  
  virtual void GrabServer() = 0;

  
  virtual void UngrabServer() = 0;

  
  virtual void SyncWithServer() = 0;

  
  virtual void SetBackgroundColor(uint32_t color_argb) = 0;

  
  virtual void ForceDPMSOn() = 0;

  
  
  
  
  virtual std::vector<ui::DisplaySnapshot*> GetDisplays() = 0;

  
  virtual void AddMode(const ui::DisplaySnapshot& output,
                       const ui::DisplayMode* mode) = 0;

  
  
  
  virtual bool Configure(const ui::DisplaySnapshot& output,
                         const ui::DisplayMode* mode,
                         const gfx::Point& origin) = 0;

  
  virtual void CreateFrameBuffer(const gfx::Size& size) = 0;

  
  virtual bool GetHDCPState(const ui::DisplaySnapshot& output,
                            ui::HDCPState* state) = 0;

  
  virtual bool SetHDCPState(const ui::DisplaySnapshot& output,
                            ui::HDCPState state) = 0;

  
  virtual std::vector<ui::ColorCalibrationProfile>
      GetAvailableColorCalibrationProfiles(
          const ui::DisplaySnapshot& output) = 0;

  
  virtual bool SetColorCalibrationProfile(
      const ui::DisplaySnapshot& output,
      ui::ColorCalibrationProfile new_profile) = 0;

  virtual void AddObserver(NativeDisplayObserver* observer) = 0;

  virtual void RemoveObserver(NativeDisplayObserver* observer) = 0;
};

}  

#endif  

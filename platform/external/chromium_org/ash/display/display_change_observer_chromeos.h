// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_DISPLAY_CHANGE_OBSERVER_CHROMEOS_H
#define ASH_DISPLAY_DISPLAY_CHANGE_OBSERVER_CHROMEOS_H

#include "ash/ash_export.h"
#include "ash/shell_observer.h"
#include "base/basictypes.h"
#include "ui/display/chromeos/display_configurator.h"
#include "ui/events/input_device_event_observer.h"

namespace ash {

class DisplayInfo;
struct DisplayMode;

class DisplayChangeObserver : public ui::DisplayConfigurator::StateController,
                              public ui::DisplayConfigurator::Observer,
                              public ui::InputDeviceEventObserver,
                              public ShellObserver {
 public:
  
  ASH_EXPORT static std::vector<DisplayMode> GetInternalDisplayModeList(
      const DisplayInfo& display_info,
      const ui::DisplayConfigurator::DisplayState& output);

  
  ASH_EXPORT static std::vector<DisplayMode> GetExternalDisplayModeList(
      const ui::DisplayConfigurator::DisplayState& output);

  DisplayChangeObserver();
  virtual ~DisplayChangeObserver();

  
  virtual ui::MultipleDisplayState GetStateForDisplayIds(
      const std::vector<int64>& outputs) const OVERRIDE;
  virtual bool GetResolutionForDisplayId(int64 display_id,
                                         gfx::Size* size) const OVERRIDE;

  
  virtual void OnDisplayModeChanged(
      const ui::DisplayConfigurator::DisplayStateList& outputs) OVERRIDE;

  
  virtual void OnInputDeviceConfigurationChanged() OVERRIDE;

  
  virtual void OnAppTerminating() OVERRIDE;

  
  ASH_EXPORT static float FindDeviceScaleFactor(float dpi);

 private:
  DISALLOW_COPY_AND_ASSIGN(DisplayChangeObserver);
};

}  

#endif  

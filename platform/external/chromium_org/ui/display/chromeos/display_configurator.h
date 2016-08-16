// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_CHROMEOS_DISPLAY_CONFIGURATOR_H_
#define UI_DISPLAY_CHROMEOS_DISPLAY_CONFIGURATOR_H_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>

#include "base/event_types.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/timer/timer.h"
#include "third_party/cros_system_api/dbus/service_constants.h"
#include "ui/display/display_export.h"
#include "ui/display/types/display_constants.h"
#include "ui/display/types/native_display_observer.h"
#include "ui/gfx/geometry/size.h"

namespace gfx {
class Point;
class Size;
}

namespace ui {
class DisplayMode;
class DisplaySnapshot;
class NativeDisplayDelegate;

class DISPLAY_EXPORT DisplayConfigurator : public NativeDisplayObserver {
 public:
  typedef uint64_t ContentProtectionClientId;
  static const ContentProtectionClientId kInvalidClientId = 0;

  struct DisplayState {
    DisplayState();

    DisplaySnapshot* display;  

    
    const DisplayMode* selected_mode;

    
    const DisplayMode* mirror_mode;
  };

  typedef std::vector<DisplayState> DisplayStateList;

  class Observer {
   public:
    virtual ~Observer() {}

    
    
    
    
    virtual void OnDisplayModeChanged(
        const std::vector<DisplayState>& displays) {}

    
    
    virtual void OnDisplayModeChangeFailed(
        MultipleDisplayState failed_new_state) {}
  };

  
  
  class StateController {
   public:
    virtual ~StateController() {}

    
    virtual MultipleDisplayState GetStateForDisplayIds(
        const std::vector<int64_t>& display_ids) const = 0;

    
    
    virtual bool GetResolutionForDisplayId(int64_t display_id,
                                           gfx::Size* size) const = 0;
  };

  
  class SoftwareMirroringController {
   public:
    virtual ~SoftwareMirroringController() {}

    
    virtual void SetSoftwareMirroring(bool enabled) = 0;
    virtual bool SoftwareMirroringEnabled() const = 0;
  };

  
  class TestApi {
   public:
    TestApi(DisplayConfigurator* configurator) : configurator_(configurator) {}
    ~TestApi() {}

    
    
    bool TriggerConfigureTimeout() WARN_UNUSED_RESULT;

   private:
    DisplayConfigurator* configurator_;  

    DISALLOW_COPY_AND_ASSIGN(TestApi);
  };

  
  static const int kSetDisplayPowerNoFlags;
  
  static const int kSetDisplayPowerForceProbe;
  
  
  static const int kSetDisplayPowerOnlyIfSingleInternalDisplay;

  
  
  
  
  
  
  
  static const int kVerticalGap = 60;

  
  
  static const DisplayMode* FindDisplayModeMatchingSize(
      const DisplaySnapshot& display,
      const gfx::Size& size);

  DisplayConfigurator();
  virtual ~DisplayConfigurator();

  MultipleDisplayState display_state() const { return display_state_; }
  chromeos::DisplayPowerState requested_power_state() const {
    return requested_power_state_;
  }
  const gfx::Size framebuffer_size() const { return framebuffer_size_; }
  const std::vector<DisplayState>& cached_displays() const {
    return cached_displays_;
  }

  void set_state_controller(StateController* controller) {
    state_controller_ = controller;
  }
  void set_mirroring_controller(SoftwareMirroringController* controller) {
    mirroring_controller_ = controller;
  }

  
  
  void SetDelegateForTesting(
      scoped_ptr<NativeDisplayDelegate> display_delegate);

  
  void SetInitialDisplayPower(chromeos::DisplayPowerState power_state);

  
  
  void Init(bool is_panel_fitting_enabled);

  
  
  
  
  void ForceInitialConfigure(uint32_t background_color_argb);

  
  void PrepareForExit();

  
  
  
  
  
  bool SetDisplayPower(chromeos::DisplayPowerState power_state, int flags);

  
  
  
  bool SetDisplayMode(MultipleDisplayState new_state);

  
  virtual void OnConfigurationChanged() OVERRIDE;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  
  void SuspendDisplays();

  
  
  void ResumeDisplays();

  
  
  ContentProtectionClientId RegisterContentProtectionClient();

  
  void UnregisterContentProtectionClient(ContentProtectionClientId client_id);

  
  
  
  
  
  bool QueryContentProtectionStatus(ContentProtectionClientId client_id,
                                    int64_t display_id,
                                    uint32_t* link_mask,
                                    uint32_t* protection_mask);

  
  
  
  
  bool EnableContentProtection(ContentProtectionClientId client_id,
                               int64_t display_id,
                               uint32_t desired_protection_mask);

  
  
  std::vector<ui::ColorCalibrationProfile> GetAvailableColorCalibrationProfiles(
      int64_t display_id);

  
  bool SetColorCalibrationProfile(int64_t display_id,
                                  ui::ColorCalibrationProfile new_profile);

 private:
  
  typedef std::map<int64_t, uint32_t> ContentProtections;
  
  typedef std::map<ContentProtectionClientId, ContentProtections>
      ProtectionRequests;

  
  scoped_ptr<NativeDisplayDelegate> CreatePlatformNativeDisplayDelegate();

  
  
  
  
  void UpdateCachedDisplays();

  
  
  
  
  
  
  
  
  
  
  
  
  bool FindMirrorMode(DisplayState* internal_display,
                      DisplayState* external_display,
                      bool try_panel_fitting,
                      bool preserve_aspect);

  
  void ConfigureDisplays();

  
  void NotifyObservers(bool success, MultipleDisplayState attempted_state);

  
  
  
  
  
  
  bool EnterStateOrFallBackToSoftwareMirroring(
      MultipleDisplayState display_state,
      chromeos::DisplayPowerState power_state);

  
  
  
  bool EnterState(MultipleDisplayState display_state,
                  chromeos::DisplayPowerState power_state);

  
  
  MultipleDisplayState ChooseDisplayState(
      chromeos::DisplayPowerState power_state) const;

  
  
  float GetMirroredDisplayAreaRatio(const DisplayState& display);

  
  bool IsMirroring() const;

  
  bool ApplyProtections(const ContentProtections& requests);

  StateController* state_controller_;
  SoftwareMirroringController* mirroring_controller_;
  scoped_ptr<NativeDisplayDelegate> native_display_delegate_;

  
  bool is_panel_fitting_enabled_;

  
  
  
  
  
  bool configure_display_;

  
  MultipleDisplayState display_state_;

  gfx::Size framebuffer_size_;

  
  
  
  chromeos::DisplayPowerState requested_power_state_;
  chromeos::DisplayPowerState current_power_state_;

  
  
  DisplayStateList cached_displays_;

  ObserverList<Observer> observers_;

  
  
  
  base::OneShotTimer<DisplayConfigurator> configure_timer_;

  
  ContentProtectionClientId next_display_protection_client_id_;

  
  ProtectionRequests client_protection_requests_;

  DISALLOW_COPY_AND_ASSIGN(DisplayConfigurator);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_CHROMEOS_X11_NATIVE_DISPLAY_DELEGATE_X11_H_
#define UI_DISPLAY_CHROMEOS_X11_NATIVE_DISPLAY_DELEGATE_X11_H_

#include <stdint.h>

#include <map>
#include <vector>

#include "base/compiler_specific.h"
#include "base/event_types.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "ui/display/display_export.h"
#include "ui/display/types/native_display_delegate.h"
#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/size.h"

typedef unsigned long XID;
typedef XID RROutput;
typedef XID RRCrtc;
typedef XID RRMode;
typedef XID Window;

struct _XDisplay;
typedef struct _XDisplay Display;
struct _XRROutputInfo;
typedef _XRROutputInfo XRROutputInfo;
struct _XRRScreenResources;
typedef _XRRScreenResources XRRScreenResources;
struct _XRRCrtcGamma;
typedef _XRRCrtcGamma XRRCrtcGamma;

namespace ui {

class DisplayModeX11;
class DisplaySnapshotX11;
class NativeDisplayEventDispatcherX11;

class DISPLAY_EXPORT NativeDisplayDelegateX11 : public NativeDisplayDelegate {
 public:
  
  
  
  class HelperDelegate {
   public:
    virtual ~HelperDelegate() {}

    
    
    virtual void UpdateXRandRConfiguration(const base::NativeEvent& event) = 0;

    
    
    virtual const std::vector<DisplaySnapshot*>& GetCachedDisplays() const = 0;

    
    virtual void NotifyDisplayObservers() = 0;
  };

  NativeDisplayDelegateX11();
  virtual ~NativeDisplayDelegateX11();

  
  virtual void Initialize() OVERRIDE;
  virtual void GrabServer() OVERRIDE;
  virtual void UngrabServer() OVERRIDE;
  virtual void SyncWithServer() OVERRIDE;
  virtual void SetBackgroundColor(uint32_t color_argb) OVERRIDE;
  virtual void ForceDPMSOn() OVERRIDE;
  virtual std::vector<DisplaySnapshot*> GetDisplays() OVERRIDE;
  virtual void AddMode(const DisplaySnapshot& output,
                       const DisplayMode* mode) OVERRIDE;
  virtual bool Configure(const DisplaySnapshot& output,
                         const DisplayMode* mode,
                         const gfx::Point& origin) OVERRIDE;
  virtual void CreateFrameBuffer(const gfx::Size& size) OVERRIDE;
  virtual bool GetHDCPState(const DisplaySnapshot& output,
                            HDCPState* state) OVERRIDE;
  virtual bool SetHDCPState(const DisplaySnapshot& output,
                            HDCPState state) OVERRIDE;
  virtual std::vector<ColorCalibrationProfile>
      GetAvailableColorCalibrationProfiles(
          const DisplaySnapshot& output) OVERRIDE;
  virtual bool SetColorCalibrationProfile(
      const DisplaySnapshot& output,
      ColorCalibrationProfile new_profile) OVERRIDE;
  virtual void AddObserver(NativeDisplayObserver* observer) OVERRIDE;
  virtual void RemoveObserver(NativeDisplayObserver* observer) OVERRIDE;

 private:
  class HelperDelegateX11;

  
  void InitModes();

  
  
  DisplaySnapshotX11* InitDisplaySnapshot(RROutput id,
                                          XRROutputInfo* info,
                                          RRCrtc* last_used_crtc,
                                          int index);

  
  void DestroyUnusedCrtcs();

  
  
  
  
  void UpdateCrtcsForNewFramebuffer(const gfx::Size& min_screen_size);

  bool ConfigureCrtc(RRCrtc crtc, RRMode mode, RROutput output, int x, int y);

  
  bool IsOutputAspectPreservingScaling(RROutput id);

  
  
  XRRCrtcGamma* CreateGammaRampForProfile(
      const DisplaySnapshotX11& x11_output,
      ColorCalibrationProfile new_profile);

  void DrawBackground();

  Display* display_;
  Window window_;

  
  XRRScreenResources* screen_;

  std::map<RRMode, DisplayModeX11*> modes_;

  
  
  
  ScopedVector<DisplaySnapshot> cached_outputs_;

  scoped_ptr<HelperDelegate> helper_delegate_;

  
  
  scoped_ptr<NativeDisplayEventDispatcherX11> platform_event_dispatcher_;

  
  ObserverList<NativeDisplayObserver> observers_;

  
  uint32_t background_color_argb_;

  DISALLOW_COPY_AND_ASSIGN(NativeDisplayDelegateX11);
};

}  

#endif  

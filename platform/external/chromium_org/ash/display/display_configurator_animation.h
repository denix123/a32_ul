// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_DISPLAY_CONFIGURATOR_ANIMATION_H_
#define ASH_DISPLAY_DISPLAY_CONFIGURATOR_ANIMATION_H_

#include <map>

#include "ash/ash_export.h"
#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "ui/display/chromeos/display_configurator.h"

namespace aura {
class RootWindow;
class Window;
}  

namespace ui {
class Layer;
}  

namespace ash {

class ASH_EXPORT DisplayConfiguratorAnimation
    : public ui::DisplayConfigurator::Observer {
 public:
  DisplayConfiguratorAnimation();
  virtual ~DisplayConfiguratorAnimation();

  
  
  void StartFadeOutAnimation(base::Closure callback);

  
  
  void StartFadeInAnimation();

 protected:
  
  virtual void OnDisplayModeChanged(
      const ui::DisplayConfigurator::DisplayStateList& outputs) OVERRIDE;
  virtual void OnDisplayModeChangeFailed(
      ui::MultipleDisplayState failed_new_state) OVERRIDE;

 private:
  
  
  
  void ClearHidingLayers();

  std::map<aura::Window*, ui::Layer*> hiding_layers_;
  scoped_ptr<base::OneShotTimer<DisplayConfiguratorAnimation> > timer_;
  base::WeakPtrFactory<DisplayConfiguratorAnimation> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DisplayConfiguratorAnimation);
};

}  

#endif  

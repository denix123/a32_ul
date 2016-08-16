// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_PROJECTING_OBSERVER_CHROMEOS_H_
#define ASH_DISPLAY_PROJECTING_OBSERVER_CHROMEOS_H_

#include "ash/ash_export.h"
#include "ui/display/chromeos/display_configurator.h"

namespace ash {

class ASH_EXPORT ProjectingObserver : public ui::DisplayConfigurator::Observer {
 public:
  ProjectingObserver();
  virtual ~ProjectingObserver();

  
  void OnCastingSessionStartedOrStopped(bool started);

  
  virtual void OnDisplayModeChanged(
      const ui::DisplayConfigurator::DisplayStateList& outputs) OVERRIDE;

 private:
  
  void SetIsProjecting();

  
  
  bool has_internal_output_;

  
  int output_count_;

  
  int casting_session_count_;

  DISALLOW_COPY_AND_ASSIGN(ProjectingObserver);
};

}  

#endif  

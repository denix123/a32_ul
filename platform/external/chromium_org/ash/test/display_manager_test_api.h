// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_DISPLAY_MANAGER_TEST_API_H_
#define ASH_TEST_DISPLAY_MANAGER_TEST_API_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "ui/display/types/display_constants.h"

namespace ash {
class DisplayManager;

namespace test {

class DisplayManagerTestApi {
 public:
  explicit DisplayManagerTestApi(DisplayManager* display_manager);
  virtual ~DisplayManagerTestApi();

  
  
  
  
  void UpdateDisplay(const std::string& display_specs);

  
  
  int64 SetFirstDisplayAsInternalDisplay();

  
  void DisableChangeDisplayUponHostResize();

  
  void SetAvailableColorProfiles(
      int64 display_id,
      const std::vector<ui::ColorCalibrationProfile>& profiles);

 private:
  DisplayManager* display_manager_;  

  DISALLOW_COPY_AND_ASSIGN(DisplayManagerTestApi);
};

}  
}  

#endif  

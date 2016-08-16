// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WORKSPACE_TWO_STEP_EDGE_CYCLER_H_
#define ASH_WM_WORKSPACE_TWO_STEP_EDGE_CYCLER_H_

#include "ash/ash_export.h"
#include "base/basictypes.h"
#include "base/time/time.h"
#include "ui/gfx/point.h"

namespace ash {

class ASH_EXPORT TwoStepEdgeCycler {
 public:
  explicit TwoStepEdgeCycler(const gfx::Point& start);
  ~TwoStepEdgeCycler();

  
  
  void OnMove(const gfx::Point& location);

  bool use_second_mode() const { return second_mode_; }

 private:
  
  bool second_mode_;

  
  base::TimeTicks time_last_move_;

  
  int num_moves_;

  
  int start_x_;

  DISALLOW_COPY_AND_ASSIGN(TwoStepEdgeCycler);
};

}  

#endif  

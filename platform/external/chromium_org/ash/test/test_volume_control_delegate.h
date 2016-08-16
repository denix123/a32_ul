// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_TEST_VOLUME_CONTROL_DELEGATE_H_
#define ASH_TEST_TEST_VOLUME_CONTROL_DELEGATE_H_

#include "ash/volume_control_delegate.h"
#include "ui/base/accelerators/accelerator.h"

namespace ash {

class TestVolumeControlDelegate : public ash::VolumeControlDelegate {
 public:
  explicit TestVolumeControlDelegate(bool consume);
  virtual ~TestVolumeControlDelegate();

  int handle_volume_mute_count() const {
    return handle_volume_mute_count_;
  }

  int handle_volume_down_count() const {
    return handle_volume_down_count_;
  }

  int handle_volume_up_count() const {
    return handle_volume_up_count_;
  }

  const ui::Accelerator& last_accelerator() const {
    return last_accelerator_;
  }

  
  virtual bool HandleVolumeMute(const ui::Accelerator& accelerator) OVERRIDE;
  virtual bool HandleVolumeDown(const ui::Accelerator& accelerator) OVERRIDE;
  virtual bool HandleVolumeUp(const ui::Accelerator& accelerator) OVERRIDE;

 private:
  
  
  bool consume_;
  int handle_volume_mute_count_;
  int handle_volume_down_count_;
  int handle_volume_up_count_;
  ui::Accelerator last_accelerator_;

  DISALLOW_COPY_AND_ASSIGN(TestVolumeControlDelegate);
};

}  

#endif  

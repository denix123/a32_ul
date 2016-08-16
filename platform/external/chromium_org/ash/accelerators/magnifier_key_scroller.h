// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_ACCELERATORS_MAGNIFIER_KEY_SCROLLER_H_
#define ASH_ACCELERATORS_MAGNIFIER_KEY_SCROLLER_H_

#include "ash/accelerators/key_hold_detector.h"
#include "ash/ash_export.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/event_handler.h"

namespace ui {
class KeyEvent;
}

namespace ash {

class ASH_EXPORT MagnifierKeyScroller : public KeyHoldDetector::Delegate {
 public:
  static bool IsEnabled();
  static void SetEnabled(bool enabled);
  static scoped_ptr<ui::EventHandler> CreateHandler();

  
  class ScopedEnablerForTest {
   public:
    ScopedEnablerForTest() {
      SetEnabled(true);
    }
    ~ScopedEnablerForTest() {
      SetEnabled(false);
    }

   private:
    DISALLOW_COPY_AND_ASSIGN(ScopedEnablerForTest);
  };

 private:
  
  virtual bool ShouldProcessEvent(const ui::KeyEvent* event) const OVERRIDE;
  virtual bool IsStartEvent(const ui::KeyEvent* event) const OVERRIDE;
  virtual void OnKeyHold(const ui::KeyEvent* event) OVERRIDE;
  virtual void OnKeyUnhold(const ui::KeyEvent* event) OVERRIDE;

  MagnifierKeyScroller();
  virtual ~MagnifierKeyScroller();

  DISALLOW_COPY_AND_ASSIGN(MagnifierKeyScroller);
};

}  

#endif  

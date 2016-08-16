// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_ACCELERATOR_KEY_HOLD_DETECTOR_H_
#define ASH_ACCELERATOR_KEY_HOLD_DETECTOR_H_

#include "ash/ash_export.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/event_handler.h"

namespace ui {
class KeyEvent;
}

namespace ash {

class ASH_EXPORT KeyHoldDetector : public ui::EventHandler {
 public:
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    virtual bool ShouldProcessEvent(const ui::KeyEvent* event) const = 0;

    
    virtual bool IsStartEvent(const ui::KeyEvent* event) const = 0;

    
    virtual void OnKeyHold(const ui::KeyEvent* event) = 0;

    
    virtual void OnKeyUnhold(const ui::KeyEvent* event) = 0;
  };

  explicit KeyHoldDetector(scoped_ptr<Delegate> delegate);
  virtual ~KeyHoldDetector();

  
  virtual void OnKeyEvent(ui::KeyEvent* key_event) OVERRIDE;

 private:
  
  
  
  
  
  
  
  
  
  enum State {
    INITIAL,
    PRESSED,
    HOLD
  };

  State state_;
  scoped_ptr<Delegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(KeyHoldDetector);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_SCOPED_WINDOW_TARGETER_H_
#define UI_AURA_SCOPED_WINDOW_TARGETER_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/window_observer.h"

namespace ui {
class EventTargeter;
}

namespace aura {

class Window;

class AURA_EXPORT ScopedWindowTargeter : public WindowObserver {
 public:
  ScopedWindowTargeter(Window* window,
                       scoped_ptr<ui::EventTargeter> new_targeter);

  virtual ~ScopedWindowTargeter();

  ui::EventTargeter* old_targeter() {
    return old_targeter_.get();
  }

 private:
  
  virtual void OnWindowDestroyed(Window* window) OVERRIDE;

  Window* window_;
  scoped_ptr<ui::EventTargeter> old_targeter_;

  DISALLOW_COPY_AND_ASSIGN(ScopedWindowTargeter);
};

}  

#endif  

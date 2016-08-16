// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_TEST_DRAW_WAITER_H_
#define UI_COMPOSITOR_TEST_DRAW_WAITER_H_

#include "base/run_loop.h"
#include "ui/compositor/compositor_observer.h"

class Compositor;

namespace ui {

class DrawWaiterForTest : public CompositorObserver {
 public:
  
  
  
  static void Wait(Compositor* compositor);

  
  static void WaitForCommit(Compositor* compositor);

 private:
  DrawWaiterForTest();
  virtual ~DrawWaiterForTest();

  void WaitImpl(Compositor* compositor);

  
  virtual void OnCompositingDidCommit(Compositor* compositor) OVERRIDE;
  virtual void OnCompositingStarted(Compositor* compositor,
                                    base::TimeTicks start_time) OVERRIDE;
  virtual void OnCompositingEnded(Compositor* compositor) OVERRIDE;
  virtual void OnCompositingAborted(Compositor* compositor) OVERRIDE;
  virtual void OnCompositingLockStateChanged(Compositor* compositor) OVERRIDE;

  scoped_ptr<base::RunLoop> wait_run_loop_;

  bool wait_for_commit_;

  DISALLOW_COPY_AND_ASSIGN(DrawWaiterForTest);
};

}  

#endif  

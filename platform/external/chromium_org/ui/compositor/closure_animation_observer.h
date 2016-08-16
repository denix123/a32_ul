// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_CLOSURE_ANIMATION_OBSERVER_H_
#define UI_COMPOSITOR_CLOSURE_ANIMATION_OBSERVER_H_

#include "base/callback.h"
#include "base/macros.h"
#include "ui/compositor/compositor_export.h"
#include "ui/compositor/layer_animation_observer.h"

namespace ui {

class COMPOSITOR_EXPORT ClosureAnimationObserver
    : public ImplicitAnimationObserver {
 public:
  explicit ClosureAnimationObserver(const base::Closure& closure);

 private:
  virtual ~ClosureAnimationObserver();

  
  virtual void OnImplicitAnimationsCompleted() OVERRIDE;

  const base::Closure closure_;

  DISALLOW_COPY_AND_ASSIGN(ClosureAnimationObserver);
};

}  

#endif  

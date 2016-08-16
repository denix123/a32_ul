// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/views/views_export.h"
#include "ui/wm/core/masked_window_targeter.h"

namespace aura {
class Window;
}

namespace views {
class BubbleDelegateView;

class VIEWS_EXPORT BubbleWindowTargeter
    : public NON_EXPORTED_BASE(wm::MaskedWindowTargeter) {
 public:
  explicit BubbleWindowTargeter(BubbleDelegateView* bubble);
  virtual ~BubbleWindowTargeter();

 private:
  
  virtual bool GetHitTestMask(aura::Window* window,
                              gfx::Path* mask) const OVERRIDE;

  views::BubbleDelegateView* bubble_;

  DISALLOW_COPY_AND_ASSIGN(BubbleWindowTargeter);
};

}  

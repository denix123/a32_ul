// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_STICKY_KEYS_STICKY_KEYS_OVERLAY_H_
#define ASH_STICKY_KEYS_STICKY_KEYS_OVERLAY_H_

#include "ash/ash_export.h"
#include "ash/sticky_keys/sticky_keys_state.h"
#include "base/memory/scoped_ptr.h"
#include "ui/compositor/layer_animation_observer.h"
#include "ui/events/event_constants.h"
#include "ui/gfx/geometry/size.h"

namespace gfx {
class Rect;
}

namespace views {
class Widget;
}

namespace ash {

class StickyKeysOverlayView;

class ASH_EXPORT StickyKeysOverlay : public ui::LayerAnimationObserver {
 public:
  StickyKeysOverlay();
  virtual ~StickyKeysOverlay();

  
  void Show(bool visible);

  void SetModifierVisible(ui::EventFlags modifier, bool visible);

  bool GetModifierVisible(ui::EventFlags modifier);

  
  void SetModifierKeyState(ui::EventFlags modifier,
                           StickyKeyState state);

  
  StickyKeyState GetModifierKeyState(ui::EventFlags modifier);

  
  
  bool is_visible() { return is_visible_; }

 private:
  
  gfx::Rect CalculateOverlayBounds();

  
  virtual void OnLayerAnimationEnded(
      ui::LayerAnimationSequence* sequence) OVERRIDE;
  virtual void OnLayerAnimationAborted(
      ui::LayerAnimationSequence* sequence) OVERRIDE;
  virtual void OnLayerAnimationScheduled(
      ui::LayerAnimationSequence* sequence) OVERRIDE;

  bool is_visible_;
  scoped_ptr<views::Widget> overlay_widget_;
  
  StickyKeysOverlayView* overlay_view_;
  gfx::Size widget_size_;
};

}  

#endif  

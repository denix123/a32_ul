// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_SLIDER_H_
#define UI_VIEWS_CONTROLS_SLIDER_H_

#include "ui/gfx/animation/animation_delegate.h"
#include "ui/views/view.h"
#include "ui/views/views_export.h"

typedef unsigned int SkColor;

namespace gfx {
class ImageSkia;
class SlideAnimation;
}

namespace views {

namespace test {
class SliderTestApi;
}

class Slider;

enum SliderChangeReason {
  VALUE_CHANGED_BY_USER,  
  VALUE_CHANGED_BY_API,   
};

class VIEWS_EXPORT SliderListener {
 public:
  virtual void SliderValueChanged(Slider* sender,
                                  float value,
                                  float old_value,
                                  SliderChangeReason reason) = 0;

  
  
  virtual void SliderDragStarted(Slider* sender) {}
  virtual void SliderDragEnded(Slider* sender) {}

 protected:
  virtual ~SliderListener() {}
};

class VIEWS_EXPORT Slider : public View, public gfx::AnimationDelegate {
 public:
  enum Orientation {
    HORIZONTAL,
    VERTICAL
  };

  Slider(SliderListener* listener, Orientation orientation);
  virtual ~Slider();

  float value() const { return value_; }
  void SetValue(float value);

  
  void SetKeyboardIncrement(float increment);

  void SetAccessibleName(const base::string16& name);

  void set_enable_accessibility_events(bool enabled) {
    accessibility_events_enabled_ = enabled;
  }

  void set_focus_border_color(SkColor color) { focus_border_color_ = color; }

  
  void UpdateState(bool control_on);

 private:
  friend class test::SliderTestApi;

  void SetValueInternal(float value, SliderChangeReason reason);

  
  
  
  void PrepareForMove(const gfx::Point& point);

  
  void MoveButtonTo(const gfx::Point& point);

  void OnPaintFocus(gfx::Canvas* canvas);

  
  void OnSliderDragStarted();

  
  void OnSliderDragEnded();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;

  
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;

  void set_listener(SliderListener* listener) {
    listener_ = listener;
  }

  SliderListener* listener_;
  Orientation orientation_;

  scoped_ptr<gfx::SlideAnimation> move_animation_;

  float value_;
  float keyboard_increment_;
  float animating_value_;
  bool value_is_valid_;
  base::string16 accessible_name_;
  bool accessibility_events_enabled_;
  SkColor focus_border_color_;

  
  
  gfx::Point initial_button_offset_;

  const int* bar_active_images_;
  const int* bar_disabled_images_;
  const gfx::ImageSkia* thumb_;
  const gfx::ImageSkia* images_[4];
  int bar_height_;

  DISALLOW_COPY_AND_ASSIGN(Slider);
};

}  

#endif  

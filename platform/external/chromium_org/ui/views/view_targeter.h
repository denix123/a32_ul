// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_VIEW_TARGETER_H_
#define UI_VIEWS_VIEW_TARGETER_H_

#include "ui/events/event_targeter.h"
#include "ui/views/views_export.h"

namespace views {

namespace internal {
class RootView;
}  

class View;
class ViewTargeterDelegate;

class VIEWS_EXPORT ViewTargeter : public ui::EventTargeter {
 public:
  explicit ViewTargeter(ViewTargeterDelegate* delegate);
  virtual ~ViewTargeter();

  
  bool DoesIntersectRect(const View* target, const gfx::Rect& rect) const;

  
  View* TargetForRect(View* root, const gfx::Rect& rect) const;

 protected:
  
  virtual ui::EventTarget* FindTargetForEvent(ui::EventTarget* root,
                                              ui::Event* event) OVERRIDE;
  virtual ui::EventTarget* FindNextBestTarget(ui::EventTarget* previous_target,
                                              ui::Event* event) OVERRIDE;
  virtual bool SubtreeCanAcceptEvent(
      ui::EventTarget* target,
      const ui::LocatedEvent& event) const OVERRIDE;
  virtual bool EventLocationInsideBounds(
      ui::EventTarget* target,
      const ui::LocatedEvent& event) const OVERRIDE;

 private:
  
  
  friend class internal::RootView;

  View* FindTargetForKeyEvent(View* root, const ui::KeyEvent& key);
  View* FindTargetForScrollEvent(View* root, const ui::ScrollEvent& scroll);

  virtual View* FindTargetForGestureEvent(View* root,
                                          const ui::GestureEvent& gesture);
  virtual ui::EventTarget* FindNextBestTargetForGestureEvent(
      ui::EventTarget* previous_target,
      const ui::GestureEvent& gesture);

  
  
  ViewTargeterDelegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(ViewTargeter);
};

}  

#endif  

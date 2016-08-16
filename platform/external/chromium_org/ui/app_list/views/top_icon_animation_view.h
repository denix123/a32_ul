// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_TOP_ICON_ANIMATION_VIEW_H_
#define UI_APP_LIST_VIEWS_TOP_ICON_ANIMATION_VIEW_H_

#include "base/observer_list.h"
#include "ui/compositor/layer_animation_observer.h"
#include "ui/views/view.h"

namespace views {
class ImageView;
}

namespace app_list {

class TopIconAnimationObserver {
 public:
  
  virtual void OnTopIconAnimationsComplete() {}

 protected:
  TopIconAnimationObserver() {}
  virtual ~TopIconAnimationObserver() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(TopIconAnimationObserver);
};

class TopIconAnimationView : public views::View,
                             public ui::ImplicitAnimationObserver {
 public:
  
  
  
  
  TopIconAnimationView(const gfx::ImageSkia& icon,
                       const gfx::Rect& scaled_rect,
                       bool open_folder);
  virtual ~TopIconAnimationView();

  void AddObserver(TopIconAnimationObserver* observer);
  void RemoveObserver(TopIconAnimationObserver* observer);

  
  
  
  
  void TransformView();

 private:
  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;

  
  virtual void OnImplicitAnimationsCompleted() OVERRIDE;
  virtual bool RequiresNotificationWhenAnimatorDestroyed() const OVERRIDE;

  gfx::Size icon_size_;
  views::ImageView* icon_;  
  
  gfx::Rect scaled_rect_;
  
  bool open_folder_;

  ObserverList<TopIconAnimationObserver> observers_;

  DISALLOW_COPY_AND_ASSIGN(TopIconAnimationView);
};

}  

#endif  

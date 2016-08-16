// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_HOME_PUBLIC_HOME_CARD_H_
#define ATHENA_HOME_PUBLIC_HOME_CARD_H_

#include "athena/athena_export.h"

namespace app_list {
class SearchProvider;
}

namespace gfx {
class Rect;
}

namespace athena {
class AppModelBuilder;

class ATHENA_EXPORT HomeCard {
 public:
  enum State {
    
    HIDDEN,

    
    VISIBLE_CENTERED,

    
    
    VISIBLE_BOTTOM,

    
    
    VISIBLE_MINIMIZED,
  };

  
  
  static HomeCard* Create(AppModelBuilder* model_builder);
  static void Shutdown();
  static HomeCard* Get();

  virtual ~HomeCard() {}

  
  virtual void SetState(State state) = 0;
  virtual State GetState() = 0;

  
  
  virtual void RegisterSearchProvider(
      app_list::SearchProvider* search_provider) = 0;

  
  
  virtual void UpdateVirtualKeyboardBounds(
      const gfx::Rect& bounds) = 0;
};

}  

#endif  

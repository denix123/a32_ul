// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_TEST_SLIDER_TEST_API_H_
#define UI_VIEWS_TEST_SLIDER_TEST_API_H_

#include "base/basictypes.h"

namespace views {

class Slider;
class SliderListener;

namespace test {

class SliderTestApi {
 public:
  explicit SliderTestApi(Slider* slider);
  virtual ~SliderTestApi();

  
  void SetListener(SliderListener* listener);

 private:
  Slider* slider_;

  DISALLOW_COPY_AND_ASSIGN(SliderTestApi);
};

}  

}  

#endif  

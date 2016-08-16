// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_TEST_VIEWS_TEST_HELPER_H_
#define UI_VIEWS_TEST_VIEWS_TEST_HELPER_H_

#include "ui/gfx/native_widget_types.h"

namespace base {
class MessageLoopForUI;
}

namespace ui {
class ContextFactory;
}

namespace views {

class ViewsTestHelper {
 public:
  explicit ViewsTestHelper();
  virtual ~ViewsTestHelper();

  
  static ViewsTestHelper* Create(base::MessageLoopForUI* message_loop,
                                 ui::ContextFactory* context_factory);

  
  virtual void SetUp();

  
  virtual void TearDown();

  
  
  virtual gfx::NativeWindow GetContext();

 private:
  DISALLOW_COPY_AND_ASSIGN(ViewsTestHelper);
};

}  

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_TEST_TEST_VIEWS_DELEGATE_H_
#define UI_VIEWS_TEST_TEST_VIEWS_DELEGATE_H_

#include "base/memory/scoped_ptr.h"
#include "ui/views/views_delegate.h"

namespace wm {
class WMState;
}

namespace views {

class TestViewsDelegate : public ViewsDelegate {
 public:
  TestViewsDelegate();
  virtual ~TestViewsDelegate();

  
  
  
  void set_use_desktop_native_widgets(bool desktop) {
    use_desktop_native_widgets_ = desktop;
  }

  void set_use_transparent_windows(bool transparent) {
    use_transparent_windows_ = transparent;
  }

  
  virtual void OnBeforeWidgetInit(
      Widget::InitParams* params,
      internal::NativeWidgetDelegate* delegate) OVERRIDE;

 private:
  bool use_desktop_native_widgets_;

  bool use_transparent_windows_;

#if defined(USE_AURA)
  scoped_ptr<wm::WMState> wm_state_;

  ui::ContextFactory* context_factory_;
#endif

  DISALLOW_COPY_AND_ASSIGN(TestViewsDelegate);
};

}  

#endif  

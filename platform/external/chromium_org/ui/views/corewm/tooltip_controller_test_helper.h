// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_COREWM_TOOLTIP_CONTROLLER_TEST_HELPER_H_
#define UI_VIEWS_COREWM_TOOLTIP_CONTROLLER_TEST_HELPER_H_

#include "base/logging.h"
#include "base/strings/string16.h"
#include "ui/views/view.h"
#include "ui/views/views_export.h"

namespace aura {
class Window;
}

namespace views {
namespace corewm {

class TooltipController;

namespace test {

class TooltipControllerTestHelper {
 public:
  explicit TooltipControllerTestHelper(TooltipController* controller);
  ~TooltipControllerTestHelper();

  TooltipController* controller() { return controller_; }

  
  base::string16 GetTooltipText();
  aura::Window* GetTooltipWindow();
  void FireTooltipTimer();
  bool IsTooltipTimerRunning();
  void FireTooltipShownTimer();
  bool IsTooltipShownTimerRunning();
  bool IsTooltipVisible();

 private:
  TooltipController* controller_;

  DISALLOW_COPY_AND_ASSIGN(TooltipControllerTestHelper);
};

class TooltipTestView : public views::View {
 public:
  TooltipTestView();
  virtual ~TooltipTestView();

  void set_tooltip_text(base::string16 tooltip_text) {
    tooltip_text_ = tooltip_text;
  }

  
  virtual bool GetTooltipText(const gfx::Point& p,
                              base::string16* tooltip) const OVERRIDE;

 private:
  base::string16 tooltip_text_;

  DISALLOW_COPY_AND_ASSIGN(TooltipTestView);
};


}  
}  
}  

#endif  
// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_VIEW_EVENT_TEST_PLATFORM_PART_H_
#define CHROME_TEST_BASE_VIEW_EVENT_TEST_PLATFORM_PART_H_

#include "base/macros.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {
class ContextFactory;
}

class ViewEventTestPlatformPart {
 public:
  virtual ~ViewEventTestPlatformPart() {}

  
  
  static ViewEventTestPlatformPart* Create(ui::ContextFactory* context_factory);

  
  
  virtual gfx::NativeWindow GetContext() = 0;

 protected:
  ViewEventTestPlatformPart() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(ViewEventTestPlatformPart);
};

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_X_X11_ERROR_TRACKER_H_
#define UI_GFX_X_X11_ERROR_TRACKER_H_

#include <X11/Xlib.h>

#include "base/basictypes.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class GFX_EXPORT X11ErrorTracker {
 public:
  X11ErrorTracker();
  ~X11ErrorTracker();

  
  
  
  bool FoundNewError();

 private:
  XErrorHandler old_handler_;

  DISALLOW_COPY_AND_ASSIGN(X11ErrorTracker);
};

}  

#endif  

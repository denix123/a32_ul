// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_LINUX_FONT_DELEGATE_H_
#define UI_GFX_LINUX_FONT_DELEGATE_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "ui/gfx/font_render_params.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class ScopedPangoFontDescription;

class GFX_EXPORT LinuxFontDelegate {
 public:
  virtual ~LinuxFontDelegate() {}

  
  
  
  static void SetInstance(LinuxFontDelegate* instance);

  
  
  
  
  
  static const LinuxFontDelegate* instance();

  
  virtual FontRenderParams GetDefaultFontRenderParams() const = 0;

  
  virtual scoped_ptr<ScopedPangoFontDescription>
      GetDefaultPangoFontDescription() const = 0;

  
  
  virtual double GetFontDPI() const = 0;
};

}  

#endif  

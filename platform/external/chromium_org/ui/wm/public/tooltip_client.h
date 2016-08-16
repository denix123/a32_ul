// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_PUBLIC_TOOLTIP_CLIENT_H_
#define UI_WM_PUBLIC_TOOLTIP_CLIENT_H_

#include "ui/aura/aura_export.h"
#include "ui/gfx/font.h"

namespace aura {
class Window;
namespace client {

class ScopedTooltipDisabler;

class AURA_EXPORT TooltipClient {
 public:
  
  virtual void UpdateTooltip(Window* target) = 0;

  
  
  virtual void SetTooltipShownTimeout(Window* target, int timeout_in_ms) = 0;

 protected:
  
  
  virtual void SetTooltipsEnabled(bool enable) = 0;

 private:
  friend class ScopedTooltipDisabler;
};

AURA_EXPORT void SetTooltipClient(Window* root_window,
                                  TooltipClient* client);
AURA_EXPORT TooltipClient* GetTooltipClient(Window* root_window);

AURA_EXPORT void SetTooltipText(Window* window,
                                base::string16* tooltip_text);
AURA_EXPORT void SetTooltipId(Window* window, void* id);
AURA_EXPORT const base::string16 GetTooltipText(Window* window);
AURA_EXPORT const void* GetTooltipId(Window* window);

}  
}  

#endif  

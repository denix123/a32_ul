// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_L10N_FONT_UTIL_H_
#define UI_BASE_L10N_FONT_UTIL_H_

#include "ui/base/ui_base_export.h"
#include "ui/gfx/size.h"

namespace gfx {
class Font;
}

namespace ui {

UI_BASE_EXPORT int GetLocalizedContentsWidthForFont(int col_resource_id,
                                                    const gfx::Font& font);
UI_BASE_EXPORT int GetLocalizedContentsHeightForFont(int row_resource_id,
                                                     const gfx::Font& font);
UI_BASE_EXPORT gfx::Size GetLocalizedContentsSizeForFont(int col_resource_id,
                                                         int row_resource_id,
                                                         const gfx::Font& font);

}  

#endif  
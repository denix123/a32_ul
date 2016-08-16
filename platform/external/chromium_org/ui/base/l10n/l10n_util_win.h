// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_L10N_L10N_UTIL_WIN_H_
#define UI_BASE_L10N_L10N_UTIL_WIN_H_

#include <windows.h>
#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "ui/base/ui_base_export.h"

namespace l10n_util {

UI_BASE_EXPORT int GetExtendedStyles();

UI_BASE_EXPORT int GetExtendedTooltipStyles();

UI_BASE_EXPORT void HWNDSetRTLLayout(HWND hwnd);


UI_BASE_EXPORT bool NeedOverrideDefaultUIFont(
    base::string16* override_font_family,
    double* font_size_scaler);

UI_BASE_EXPORT void AdjustUIFont(LOGFONT* logfont);

UI_BASE_EXPORT void AdjustUIFontForDIP(float dpi_scale, LOGFONT* logfont);

UI_BASE_EXPORT void AdjustUIFontForWindow(HWND hwnd);

UI_BASE_EXPORT void OverrideLocaleWithUILanguageList();

const std::vector<std::string>& GetLocaleOverrides();

}  

#endif  

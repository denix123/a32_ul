// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_WIN_SHELL_H_
#define UI_BASE_WIN_SHELL_H_

#include <windows.h>

#include "base/strings/string16.h"
#include "ui/base/ui_base_export.h"

namespace base {
class FilePath;
}

namespace ui {
namespace win {

UI_BASE_EXPORT bool OpenItemViaShell(const base::FilePath& full_path);

UI_BASE_EXPORT bool OpenAnyViaShell(const base::string16& full_path,
                                    const base::string16& directory,
                                    const base::string16& args,
                                    DWORD mask);

UI_BASE_EXPORT bool PreventWindowFromPinning(HWND hwnd);

UI_BASE_EXPORT void SetAppDetailsForWindow(
    const base::string16& app_id,
    const base::string16& app_icon,
    const base::string16& relaunch_command,
    const base::string16& relaunch_display_name,
    HWND hwnd);

UI_BASE_EXPORT void SetAppIdForWindow(const base::string16& app_id, HWND hwnd);

UI_BASE_EXPORT void SetAppIconForWindow(const base::string16& app_icon,
                                        HWND hwnd);

UI_BASE_EXPORT void SetRelaunchDetailsForWindow(
    const base::string16& relaunch_command,
    const base::string16& display_name,
    HWND hwnd);

UI_BASE_EXPORT bool IsAeroGlassEnabled();

}  
}  

#endif  

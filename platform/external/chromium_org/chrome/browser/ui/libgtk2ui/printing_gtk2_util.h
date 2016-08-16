// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_PRINTING_GTK2_UTIL_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_PRINTING_GTK2_UTIL_H_

#include "ui/gfx/geometry/size.h"

namespace printing {
class PrintingContextLinux;
class PrintSettings;
}

typedef struct _GtkPrintSettings GtkPrintSettings;
typedef struct _GtkPageSetup GtkPageSetup;

gfx::Size GetPdfPaperSizeDeviceUnitsGtk(
    printing::PrintingContextLinux* context);

void InitPrintSettingsGtk(GtkPrintSettings* settings,
                          GtkPageSetup* page_setup,
                          printing::PrintSettings* print_settings);

#endif  
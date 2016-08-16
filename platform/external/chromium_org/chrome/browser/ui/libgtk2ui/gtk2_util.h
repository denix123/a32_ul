// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_GTK2_UTIL_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_GTK2_UTIL_H_

#include <gtk/gtk.h>
#include <string>

#include "ui/native_theme/native_theme.h"

class SkBitmap;

namespace aura {
class Window;
}

namespace base {
class CommandLine;
class Environment;
}

namespace ui {
class Accelerator;
}

namespace libgtk2ui {

void GtkInitFromCommandLine(const base::CommandLine& command_line);

std::string GetDesktopName(base::Environment* env);

void SetAlwaysShowImage(GtkWidget* image_menu_item);

guint GetGdkKeyCodeForAccelerator(const ui::Accelerator& accelerator);

GdkModifierType GetGdkModifierForAccelerator(
    const ui::Accelerator& accelerator);

int EventFlagsFromGdkState(guint state);

void SetGtkTransientForAura(GtkWidget* dialog, aura::Window* parent);

aura::Window* GetAuraTransientParent(GtkWidget* dialog);

void ClearAuraTransientParent(GtkWidget* dialog);

GtkStateType GetGtkState(ui::NativeTheme::State state);

}  

#endif  

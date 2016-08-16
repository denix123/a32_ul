// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_UI_EXTENSIONS_ACCELERATOR_PRIORITY_H_
#define CHROME_BROWSER_UI_EXTENSIONS_ACCELERATOR_PRIORITY_H_

#include <string>

#include "ui/base/accelerators/accelerator_manager.h"

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;
}

namespace ui {
class Accelerator;
}

ui::AcceleratorManager::HandlerPriority GetAcceleratorPriority(
    const ui::Accelerator& accelerator,
    const extensions::Extension* extension);

ui::AcceleratorManager::HandlerPriority GetAcceleratorPriorityById(
    const ui::Accelerator& accelerator,
    const std::string& extension_id,
    content::BrowserContext* browser_context);

#endif  

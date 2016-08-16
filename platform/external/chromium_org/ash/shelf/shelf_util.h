// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELF_SHELF_UTIL_H_
#define ASH_SHELF_SHELF_UTIL_H_

#include "ash/ash_export.h"
#include "ash/shelf/shelf_item_types.h"
#include "base/strings/string16.h"
#include "ui/aura/window.h"

namespace aura {
class Window;
}

namespace ash {

extern const aura::WindowProperty<ShelfID>* const kShelfID;

extern const aura::WindowProperty<ShelfItemDetails*>* const
    kShelfItemDetailsKey;

ASH_EXPORT void SetShelfIDForWindow(ShelfID id, aura::Window* window);

ASH_EXPORT ShelfID GetShelfIDForWindow(const aura::Window* window);

ASH_EXPORT void SetShelfItemDetailsForWindow(aura::Window* window,
                                             const ShelfItemDetails& details);

ASH_EXPORT void SetShelfItemDetailsForDialogWindow(aura::Window* window,
                                                   int image_resource_id,
                                                   const base::string16& title);

ASH_EXPORT void ClearShelfItemDetailsForWindow(aura::Window* window);

ASH_EXPORT const ShelfItemDetails* GetShelfItemDetailsForWindow(
    aura::Window* window);

}  

#endif  

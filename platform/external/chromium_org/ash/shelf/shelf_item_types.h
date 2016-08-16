// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELF_SHELF_ITEM_TYPES_H_
#define ASH_SHELF_SHELF_ITEM_TYPES_H_

#include <vector>

#include "ash/ash_export.h"
#include "base/strings/string16.h"
#include "ui/gfx/image/image_skia.h"

namespace ash {

typedef int ShelfID;

enum ShelfItemType {
  
  TYPE_APP_PANEL,

  
  TYPE_APP_SHORTCUT,

  
  TYPE_APP_LIST,

  
  TYPE_BROWSER_SHORTCUT,

  
  TYPE_PLATFORM_APP,

  
  TYPE_WINDOWED_APP,

  
  TYPE_DIALOG,

  
  TYPE_UNDEFINED,
};

enum ShelfItemStatus {
  
  STATUS_CLOSED,
  
  STATUS_RUNNING,
  
  STATUS_ACTIVE,
  
  STATUS_ATTENTION,
};

struct ASH_EXPORT ShelfItem {
  ShelfItem();
  ~ShelfItem();

  ShelfItemType type;

  
  gfx::ImageSkia image;

  
  ShelfID id;

  
  ShelfItemStatus status;
};

typedef std::vector<ShelfItem> ShelfItems;

struct ASH_EXPORT ShelfItemDetails {
  ShelfItemDetails();
  ~ShelfItemDetails();

  ShelfItemType type;

  
  int image_resource_id;

  
  base::string16 title;
};

}  

#endif  

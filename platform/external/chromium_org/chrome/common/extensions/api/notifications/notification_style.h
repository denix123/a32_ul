// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_API_NOTIFICATIONS_NOTIFICATION_STYLE_H_
#define CHROME_COMMON_EXTENSIONS_API_NOTIFICATIONS_NOTIFICATION_STYLE_H_

#include "ui/gfx/size.h"

struct NotificationBitmapSizes {
  NotificationBitmapSizes();
  ~NotificationBitmapSizes();

  gfx::Size image_size;
  gfx::Size icon_size;
  gfx::Size button_icon_size;
  gfx::Size app_icon_mask_size;
};

NotificationBitmapSizes GetNotificationBitmapSizes();

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_CONVERSION_HELPER_H_
#define CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_CONVERSION_HELPER_H_

#include "chrome/browser/notifications/notification.h"
#include "ui/message_center/notification_types.h"

namespace extensions {
namespace api {
namespace notifications {
struct NotificationOptions;
struct NotificationBitmap;
}  
}  
}  

namespace gfx {
class Image;
}

class NotificationConversionHelper {
 public:
  
  
  static void NotificationToNotificationOptions(
      const Notification& notification,
      extensions::api::notifications::NotificationOptions* options);

  
  
  static void GfxImageToNotificationBitmap(
      const gfx::Image* gfx_image,
      extensions::api::notifications::NotificationBitmap* return_image_args);

  
  
  static bool NotificationBitmapToGfxImage(
      float max_scale,
      const gfx::Size& target_size_dips,
      extensions::api::notifications::NotificationBitmap* notification_bitmap,
      gfx::Image* return_image);

 private:
  
  
  static std::string MapTypeToString(message_center::NotificationType type);
};

#endif  

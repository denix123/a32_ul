// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_UI_IDLE_APP_NAME_NOTIFICATION_VIEW_H_
#define CHROME_BROWSER_CHROMEOS_UI_IDLE_APP_NAME_NOTIFICATION_VIEW_H_

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"

namespace extensions {
class Extension;
}  

namespace views {
class Widget;
}  

namespace chromeos {

class IdleAppNameNotificationDelegateView;

class IdleAppNameNotificationView {
 public:
  
  
  
  IdleAppNameNotificationView(int message_visibility_time_in_ms,
                              int animation_time_ms,
                              const extensions::Extension* extension);
  virtual ~IdleAppNameNotificationView();

  
  void CloseMessage();

  
  bool IsVisible();

  
  base::string16 GetShownTextForTest();

 private:
  
  void ShowMessage(int message_visibility_time_in_ms,
                   int animation_time_ms,
                   const extensions::Extension* extension);

  
  IdleAppNameNotificationDelegateView* view_;

  DISALLOW_COPY_AND_ASSIGN(IdleAppNameNotificationView);
};

}  

#endif  

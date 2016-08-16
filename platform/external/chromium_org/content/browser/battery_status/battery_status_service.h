// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_BATTERY_STATUS_BATTERY_STATUS_SERVICE_H_
#define CONTENT_BROWSER_BATTERY_STATUS_BATTERY_STATUS_SERVICE_H_

#include "base/callback_list.h"
#include "base/memory/singleton.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebBatteryStatus.h"

namespace content {
class BatteryStatusManager;

class CONTENT_EXPORT BatteryStatusService {
 public:
  typedef base::Callback<void(const blink::WebBatteryStatus&)>
      BatteryUpdateCallback;
  typedef base::CallbackList<void(const blink::WebBatteryStatus&)>
      BatteryUpdateCallbackList;
  typedef BatteryUpdateCallbackList::Subscription BatteryUpdateSubscription;

  
  static BatteryStatusService* GetInstance();

  
  
  scoped_ptr<BatteryUpdateSubscription> AddCallback(
      const BatteryUpdateCallback& callback);

  
  void Shutdown();

  
  
  void SetBatteryManagerForTesting(BatteryStatusManager* test_battery_manager);

  
  const BatteryUpdateCallback& GetUpdateCallbackForTesting() const;

 private:
  friend struct DefaultSingletonTraits<BatteryStatusService>;

  BatteryStatusService();
  virtual ~BatteryStatusService();

  
  
  void UpdateBatteryStatus(const blink::WebBatteryStatus& status);
  void NotifyConsumers(const blink::WebBatteryStatus& status);
  void ConsumersChanged();

  scoped_ptr<BatteryStatusManager> battery_fetcher_;
  BatteryUpdateCallbackList callback_list_;
  BatteryUpdateCallback update_callback_;
  blink::WebBatteryStatus status_;
  bool status_updated_;
  bool is_shutdown_;

  DISALLOW_COPY_AND_ASSIGN(BatteryStatusService);
};

}  

#endif  

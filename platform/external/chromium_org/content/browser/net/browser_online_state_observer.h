// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_NET_BROWSER_ONLINE_STATE_OBSERVER_H_
#define CONTENT_BROWSER_NET_BROWSER_ONLINE_STATE_OBSERVER_H_

#include "base/basictypes.h"
#include "net/base/network_change_notifier.h"

namespace content {

class BrowserOnlineStateObserver
    : public net::NetworkChangeNotifier::ConnectionTypeObserver {
 public:
  BrowserOnlineStateObserver();
  virtual ~BrowserOnlineStateObserver();

  
  virtual void OnConnectionTypeChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(BrowserOnlineStateObserver);
};

}  

#endif  
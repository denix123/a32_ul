// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_CONNECTION_OBSERVER_H_
#define COMPONENTS_GCM_DRIVER_GCM_CONNECTION_OBSERVER_H_

#include "base/basictypes.h"

namespace net {
class IPEndPoint;
}

namespace gcm {

class GCMConnectionObserver {
 public:
  GCMConnectionObserver();
  virtual ~GCMConnectionObserver();

  
  
  
  
  virtual void OnConnected(const net::IPEndPoint& ip_endpoint);

  
  
  virtual void OnDisconnected();
};

}  

#endif  

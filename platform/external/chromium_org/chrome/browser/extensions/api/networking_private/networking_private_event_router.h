// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_EVENT_ROUTER_H_
#define CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_EVENT_ROUTER_H_

#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/event_router.h"

class Profile;

namespace extensions {

class NetworkingPrivateEventRouter : public KeyedService,
                                     public EventRouter::Observer {
 public:
  static NetworkingPrivateEventRouter* Create(Profile* profile);

 protected:
  NetworkingPrivateEventRouter() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateEventRouter);
};

}  

#endif  


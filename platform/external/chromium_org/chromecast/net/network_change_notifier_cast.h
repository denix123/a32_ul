// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_NET_NETWORK_CHANGE_NOTIFIER_CAST_H_
#define CHROMECAST_NET_NETWORK_CHANGE_NOTIFIER_CAST_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "net/base/network_change_notifier.h"

namespace chromecast {

class NetworkChangeNotifierCast : public net::NetworkChangeNotifier {
 public:
  NetworkChangeNotifierCast();
  virtual ~NetworkChangeNotifierCast();

  
  virtual net::NetworkChangeNotifier::ConnectionType
      GetCurrentConnectionType() const OVERRIDE;

 private:
  friend class NetworkChangeNotifierCastTest;

  DISALLOW_COPY_AND_ASSIGN(NetworkChangeNotifierCast);
};

}  

#endif  

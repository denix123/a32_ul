// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_RENDERER_P2P_NETWORK_LIST_MANAGER_H_
#define CONTENT_RENDERER_P2P_NETWORK_LIST_MANAGER_H_

namespace content {

class NetworkListObserver;

class CONTENT_EXPORT NetworkListManager {
 public:
  
  
  
  
  virtual void AddNetworkListObserver(
      NetworkListObserver* network_list_observer) = 0;

  
  
  virtual void RemoveNetworkListObserver(
      NetworkListObserver* network_list_observer) = 0;

 protected:
  
  
  virtual ~NetworkListManager() {}
};

}  

#endif  

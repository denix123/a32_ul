// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_SHELL_BROWSER_SHELL_NETWORK_CONTROLLER_CHROMEOS_H_
#define EXTENSIONS_SHELL_BROWSER_SHELL_NETWORK_CONTROLLER_CHROMEOS_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "chromeos/network/network_state_handler_observer.h"

namespace extensions {

class ShellNetworkController : public chromeos::NetworkStateHandlerObserver {
 public:
  
  
  explicit ShellNetworkController(const std::string& preferred_network_name);
  virtual ~ShellNetworkController();

  
  virtual void NetworkListChanged() OVERRIDE;
  virtual void NetworkConnectionStateChanged(
      const chromeos::NetworkState* state) OVERRIDE;

 private:
  
  enum State {
    
    STATE_IDLE = 0,
    
    STATE_WAITING_FOR_PREFERRED_RESULT,
    
    
    STATE_WAITING_FOR_NON_PREFERRED_RESULT,
  };

  
  
  const chromeos::NetworkState* GetActiveWiFiNetwork();

  
  void SetScanningEnabled(bool enabled);

  
  void RequestScan();

  
  
  
  void ConnectIfUnconnected();

  
  void HandleConnectionSuccess();
  void HandleConnectionError(const std::string& error_name,
                             scoped_ptr<base::DictionaryValue> error_data);

  
  
  
  State state_;

  
  base::RepeatingTimer<ShellNetworkController> scan_timer_;

  
  std::string preferred_network_name_;

  
  bool preferred_network_is_active_;

  base::WeakPtrFactory<ShellNetworkController> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ShellNetworkController);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_DISCOVERY_SESSION_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_DISCOVERY_SESSION_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"

namespace device {

class BluetoothAdapter;

class BluetoothDiscoverySession {
 public:
  
  typedef base::Closure ErrorCallback;

  
  
  
  
  
  
  virtual ~BluetoothDiscoverySession();

  
  
  
  
  
  
  virtual bool IsActive() const;

  
  
  
  
  
  
  
  
  virtual void Stop(const base::Closure& callback,
                    const ErrorCallback& error_callback);

 protected:
  explicit BluetoothDiscoverySession(scoped_refptr<BluetoothAdapter> adapter);

 private:
  friend class BluetoothAdapter;

  
  void OnStop(const base::Closure& callback);

  
  
  
  void MarkAsInactive();

  
  bool active_;

  
  scoped_refptr<BluetoothAdapter> adapter_;

  
  
  base::WeakPtrFactory<BluetoothDiscoverySession> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothDiscoverySession);
};

}  

#endif  

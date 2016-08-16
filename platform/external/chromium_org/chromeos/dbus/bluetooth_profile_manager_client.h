// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_PROFILE_MANAGER_CLIENT_H_
#define CHROMEOS_DBUS_BLUETOOTH_PROFILE_MANAGER_CLIENT_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothProfileManagerClient : public DBusClient {
 public:
  
  
  
  enum ProfileRole {
    SYMMETRIC,
    CLIENT,
    SERVER
  };

  
  struct CHROMEOS_EXPORT Options {
    Options();
    ~Options();

    
    scoped_ptr<std::string> name;

    
    scoped_ptr<std::string> service;

    
    enum ProfileRole role;

    
    scoped_ptr<uint16> channel;

    
    scoped_ptr<uint16> psm;

    
    scoped_ptr<bool> require_authentication;

    
    scoped_ptr<bool> require_authorization;

    
    scoped_ptr<bool> auto_connect;

    
    scoped_ptr<std::string> service_record;

    
    scoped_ptr<uint16> version;

    
    scoped_ptr<uint16> features;
  };

  virtual ~BluetoothProfileManagerClient();

  
  
  
  typedef base::Callback<void(const std::string& error_name,
                              const std::string& error_message)> ErrorCallback;

  
  
  
  
  virtual void RegisterProfile(const dbus::ObjectPath& profile_path,
                               const std::string& uuid,
                               const Options& options,
                               const base::Closure& callback,
                               const ErrorCallback& error_callback) = 0;

  
  
  virtual void UnregisterProfile(const dbus::ObjectPath& profile_path,
                                 const base::Closure& callback,
                                 const ErrorCallback& error_callback) = 0;


  
  static BluetoothProfileManagerClient* Create();

  
  static const char kNoResponseError[];

 protected:
  BluetoothProfileManagerClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothProfileManagerClient);
};

}  

#endif  

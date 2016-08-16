// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_EASY_UNLOCK_CLIENT_H_
#define CHROMEOS_DBUS_EASY_UNLOCK_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client.h"

namespace chromeos {

class CHROMEOS_EXPORT EasyUnlockClient : public DBusClient {
 public:
  virtual ~EasyUnlockClient();

  typedef base::Callback<void(const std::string& data)> DataCallback;

  
  typedef base::Callback<void(const std::string& private_key,
                              const std::string& public_key)>
      KeyPairCallback;

  
  
  virtual void GenerateEcP256KeyPair(const KeyPairCallback& callback) = 0;

  
  struct CreateSecureMessageOptions {
    CreateSecureMessageOptions();
    ~CreateSecureMessageOptions();

    
    
    std::string key;

    
    
    
    std::string associated_data;

    
    std::string public_metadata;

    
    
    
    std::string verification_key_id;

    
    
    std::string decryption_key_id;

    
    std::string encryption_type;

    
    std::string signature_type;

   private:
    DISALLOW_COPY_AND_ASSIGN(CreateSecureMessageOptions);
  };

  
  struct UnwrapSecureMessageOptions {
    UnwrapSecureMessageOptions();
    ~UnwrapSecureMessageOptions();

    
    
    std::string key;

    
    
    std::string associated_data;

    
    std::string encryption_type;

    
    std::string signature_type;

   private:
    DISALLOW_COPY_AND_ASSIGN(UnwrapSecureMessageOptions);
  };

  
  
  
  
  
  virtual void PerformECDHKeyAgreement(const std::string& private_key,
                                       const std::string& public_key,
                                       const DataCallback& callback) = 0;

  
  
  
  
  
  
  virtual void CreateSecureMessage(const std::string& payload,
                                   const CreateSecureMessageOptions& options,
                                   const DataCallback& callback) = 0;

  
  
  
  
  
  
  
  virtual void UnwrapSecureMessage(const std::string& message,
                                   const UnwrapSecureMessageOptions& options,
                                   const DataCallback& callback) = 0;

  
  
  static EasyUnlockClient* Create();

 protected:
  
  EasyUnlockClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(EasyUnlockClient);
};

}  

#endif  

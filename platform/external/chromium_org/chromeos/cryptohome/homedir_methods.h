// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_CRYPTOHOME_HOMEDIR_METHODS_H_
#define CHROMEOS_CRYPTOHOME_HOMEDIR_METHODS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/cryptohome/cryptohome_parameters.h"
#include "chromeos/dbus/cryptohome_client.h"
#include "third_party/cros_system_api/dbus/service_constants.h"

namespace cryptohome {

class CHROMEOS_EXPORT HomedirMethods {
 public:
  
  
  typedef base::Callback<void(bool success, MountError return_code)> Callback;
  typedef base::Callback<void(
      bool success,
      MountError return_code,
      const std::vector<KeyDefinition>& key_definitions)> GetKeyDataCallback;
  typedef base::Callback<
      void(bool success, MountError return_code, const std::string& mount_hash)>
      MountCallback;

  virtual ~HomedirMethods() {}

  
  
  
  virtual void GetKeyDataEx(const Identification& id,
                            const std::string& label,
                            const GetKeyDataCallback& callback) = 0;

  
  
  virtual void CheckKeyEx(const Identification& id,
                          const Authorization& auth,
                          const Callback& callback) = 0;

  
  
  
  
  
  
  virtual void MountEx(const Identification& id,
                       const Authorization& auth,
                       const MountParameters& request,
                       const MountCallback& callback) = 0;

  
  
  
  
  
  
  
  virtual void AddKeyEx(const Identification& id,
                        const Authorization& auth,
                        const KeyDefinition& key,
                        bool clobber_if_exist,
                        const Callback& callback) = 0;

  
  
  
  
  
  
  virtual void UpdateKeyEx(const Identification& id,
                           const Authorization& auth,
                           const KeyDefinition& key,
                           const std::string& signature,
                           const Callback& callback) = 0;

  
  
  virtual void RemoveKeyEx(const Identification& id,
                           const Authorization& auth,
                           const std::string& label,
                           const Callback& callback) = 0;

  
  static void Initialize();

  
  
  
  
  static void InitializeForTesting(HomedirMethods* homedir_methods);

  
  static void Shutdown();

  
  
  static HomedirMethods* GetInstance();
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_CRYPTOHOME_CRYPTOHOME_PARAMETERS_H_
#define CHROMEOS_CRYPTOHOME_CRYPTOHOME_PARAMETERS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "chromeos/chromeos_export.h"

namespace cryptohome {

enum AuthKeyPrivileges {
  PRIV_MOUNT = 1 << 0,              
  PRIV_ADD = 1 << 1,                
  PRIV_REMOVE = 1 << 2,             
  PRIV_MIGRATE = 1 << 3,            
  PRIV_AUTHORIZED_UPDATE = 1 << 4,  
  PRIV_DEFAULT = PRIV_MOUNT | PRIV_ADD | PRIV_REMOVE | PRIV_MIGRATE
};

struct CHROMEOS_EXPORT Identification {
  explicit Identification(const std::string& user_id);

  bool operator==(const Identification& other) const;

  std::string user_id;
};

struct CHROMEOS_EXPORT KeyDefinition {
  enum Type {
    TYPE_PASSWORD = 0
  };

  struct AuthorizationData {
    enum Type {
      TYPE_HMACSHA256 = 0,
      TYPE_AES256CBC_HMACSHA256
    };

    struct Secret {
      Secret();
      Secret(bool encrypt,
             bool sign,
             const std::string& symmetric_key,
             const std::string& public_key,
             bool wrapped);

      bool operator==(const Secret& other) const;

      bool encrypt;
      bool sign;
      std::string symmetric_key;
      std::string public_key;
      bool wrapped;
    };

    AuthorizationData();
    AuthorizationData(bool encrypt,
                      bool sign,
                      const std::string& symmetric_key);
    ~AuthorizationData();

    bool operator==(const AuthorizationData& other) const;

    Type type;
    std::vector<Secret> secrets;
  };

  
  
  
  
  
  
  struct ProviderData {
    ProviderData();
    explicit ProviderData(const std::string& name);
    explicit ProviderData(const ProviderData& other);
    ProviderData(const std::string& name, int64 number);
    ProviderData(const std::string& name, const std::string& bytes);
    void operator=(const ProviderData& other);
    ~ProviderData();

    bool operator==(const ProviderData& other) const;

    std::string name;
    scoped_ptr<int64> number;
    scoped_ptr<std::string> bytes;
  };

  KeyDefinition();
  KeyDefinition(const std::string& secret,
                const std::string& label,
                int privileges);
  ~KeyDefinition();

  bool operator==(const KeyDefinition& other) const;

  Type type;
  std::string label;
  
  int privileges;
  int revision;
  std::string secret;

  std::vector<AuthorizationData> authorization_data;
  std::vector<ProviderData> provider_data;
};

struct CHROMEOS_EXPORT Authorization {
  Authorization(const std::string& key, const std::string& label);
  explicit Authorization(const KeyDefinition& key);

  bool operator==(const Authorization& other) const;

  std::string key;
  std::string label;
};

class CHROMEOS_EXPORT MountParameters {
 public:
  explicit MountParameters(bool ephemeral);
  ~MountParameters();

  bool operator==(const MountParameters& other) const;

  
  
  
  bool ephemeral;

  
  std::vector<KeyDefinition> create_keys;
};

}  

#endif  

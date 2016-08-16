// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OWNERSHIP_OWNER_SETTINGS_SERVICE_H_
#define COMPONENTS_OWNERSHIP_OWNER_SETTINGS_SERVICE_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/ownership/ownership_export.h"
#include "policy/proto/device_management_backend.pb.h"

namespace base {
class TaskRunner;
}

namespace ownership {
class OwnerKeyUtil;
class PrivateKey;
class PublicKey;

class OWNERSHIP_EXPORT OwnerSettingsService : public KeyedService {
 public:
  typedef base::Callback<void(std::string policy_blob)>
      AssembleAndSignPolicyAsyncCallback;

  typedef base::Callback<void(bool is_owner)> IsOwnerCallback;

  explicit OwnerSettingsService(
      const scoped_refptr<ownership::OwnerKeyUtil>& owner_key_util);
  virtual ~OwnerSettingsService();

  base::WeakPtr<OwnerSettingsService> as_weak_ptr() {
    return weak_factory_.GetWeakPtr();
  }

  
  
  
  bool IsOwner();

  
  
  void IsOwnerAsync(const IsOwnerCallback& callback);

  
  
  bool AssembleAndSignPolicyAsync(
      base::TaskRunner* task_runner,
      scoped_ptr<enterprise_management::PolicyData> policy,
      const AssembleAndSignPolicyAsyncCallback& callback);

  
  
  
  virtual void SignAndStorePolicyAsync(
      scoped_ptr<enterprise_management::PolicyData> policy,
      const base::Closure& callback) = 0;

 protected:
  void ReloadKeypair();

  void OnKeypairLoaded(const scoped_refptr<PublicKey>& public_key,
                       const scoped_refptr<PrivateKey>& private_key);

  
  virtual void ReloadKeypairImpl(const base::Callback<
      void(const scoped_refptr<PublicKey>& public_key,
           const scoped_refptr<PrivateKey>& private_key)>& callback) = 0;

  
  virtual void OnPostKeypairLoadedActions() = 0;

  scoped_refptr<ownership::PublicKey> public_key_;

  scoped_refptr<ownership::PrivateKey> private_key_;

  scoped_refptr<ownership::OwnerKeyUtil> owner_key_util_;

  std::vector<IsOwnerCallback> pending_is_owner_callbacks_;

  base::ThreadChecker thread_checker_;

 private:
  base::WeakPtrFactory<OwnerSettingsService> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(OwnerSettingsService);
};

}  

#endif  

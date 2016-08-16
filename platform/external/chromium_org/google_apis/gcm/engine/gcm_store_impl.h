// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_GCM_STORE_IMPL_H_
#define GOOGLE_APIS_GCM_ENGINE_GCM_STORE_IMPL_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "google_apis/gcm/base/gcm_export.h"
#include "google_apis/gcm/engine/gcm_store.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}  

namespace gcm {

class Encryptor;

class GCM_EXPORT GCMStoreImpl : public GCMStore {
 public:
  GCMStoreImpl(const base::FilePath& path,
               scoped_refptr<base::SequencedTaskRunner> blocking_task_runner,
               scoped_ptr<Encryptor> encryptor);
  virtual ~GCMStoreImpl();

  
  virtual void Load(const LoadCallback& callback) OVERRIDE;

  
  virtual void Close() OVERRIDE;

  
  
  
  
  
  virtual void Destroy(const UpdateCallback& callback) OVERRIDE;

  
  virtual void SetDeviceCredentials(uint64 device_android_id,
                                    uint64 device_security_token,
                                    const UpdateCallback& callback) OVERRIDE;

  
  virtual void AddRegistration(const std::string& app_id,
                               const linked_ptr<RegistrationInfo>& registration,
                               const UpdateCallback& callback) OVERRIDE;
  virtual void RemoveRegistration(const std::string& app_id,
                                  const UpdateCallback& callback) OVERRIDE;

  
  virtual void AddIncomingMessage(const std::string& persistent_id,
                                  const UpdateCallback& callback) OVERRIDE;
  virtual void RemoveIncomingMessage(const std::string& persistent_id,
                                     const UpdateCallback& callback) OVERRIDE;
  virtual void RemoveIncomingMessages(const PersistentIdList& persistent_ids,
                                      const UpdateCallback& callback) OVERRIDE;

  
  virtual bool AddOutgoingMessage(const std::string& persistent_id,
                                  const MCSMessage& message,
                                  const UpdateCallback& callback) OVERRIDE;
  virtual void OverwriteOutgoingMessage(const std::string& persistent_id,
                                        const MCSMessage& message,
                                        const UpdateCallback& callback)
      OVERRIDE;
  virtual void RemoveOutgoingMessage(const std::string& persistent_id,
                                     const UpdateCallback& callback) OVERRIDE;
  virtual void RemoveOutgoingMessages(const PersistentIdList& persistent_ids,
                                      const UpdateCallback& callback) OVERRIDE;

  
  virtual void SetLastCheckinInfo(const base::Time& time,
                                  const std::set<std::string>& accounts,
                                  const UpdateCallback& callback) OVERRIDE;

  
  virtual void SetGServicesSettings(
      const std::map<std::string, std::string>& settings,
      const std::string& settings_digest,
      const UpdateCallback& callback) OVERRIDE;

  
  virtual void AddAccountMapping(const AccountMapping& account_mapping,
                                 const UpdateCallback& callback) OVERRIDE;
  virtual void RemoveAccountMapping(const std::string& account_id,
                                    const UpdateCallback& callback) OVERRIDE;

 private:
  typedef std::map<std::string, int> AppIdToMessageCountMap;

  
  void LoadContinuation(const LoadCallback& callback,
                        scoped_ptr<LoadResult> result);

  
  
  void AddOutgoingMessageContinuation(const UpdateCallback& callback,
                                      const std::string& app_id,
                                      bool success);

  
  
  
  
  void RemoveOutgoingMessagesContinuation(
      const UpdateCallback& callback,
      bool success,
      const std::map<std::string, int>& removed_message_counts);

  class Backend;

  
  AppIdToMessageCountMap app_message_counts_;

  scoped_refptr<Backend> backend_;
  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;

  base::WeakPtrFactory<GCMStoreImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GCMStoreImpl);
};

}  

#endif  

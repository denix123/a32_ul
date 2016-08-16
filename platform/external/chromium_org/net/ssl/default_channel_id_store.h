// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_DEFAULT_CHANNEL_ID_STORE_H_
#define NET_SSL_DEFAULT_CHANNEL_ID_STORE_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "net/base/net_export.h"
#include "net/ssl/channel_id_store.h"

namespace net {

class NET_EXPORT DefaultChannelIDStore : public ChannelIDStore {
 public:
  class PersistentStore;

  
  
  typedef std::map<std::string, ChannelID*> ChannelIDMap;

  
  
  
  
  
  explicit DefaultChannelIDStore(PersistentStore* store);

  virtual ~DefaultChannelIDStore();

  
  virtual int GetChannelID(
      const std::string& server_identifier,
      base::Time* expiration_time,
      std::string* private_key_result,
      std::string* cert_result,
      const GetChannelIDCallback& callback) OVERRIDE;
  virtual void SetChannelID(
      const std::string& server_identifier,
      base::Time creation_time,
      base::Time expiration_time,
      const std::string& private_key,
      const std::string& cert) OVERRIDE;
  virtual void DeleteChannelID(
      const std::string& server_identifier,
      const base::Closure& callback) OVERRIDE;
  virtual void DeleteAllCreatedBetween(
      base::Time delete_begin,
      base::Time delete_end,
      const base::Closure& callback) OVERRIDE;
  virtual void DeleteAll(const base::Closure& callback) OVERRIDE;
  virtual void GetAllChannelIDs(
      const GetChannelIDListCallback& callback) OVERRIDE;
  virtual int GetChannelIDCount() OVERRIDE;
  virtual void SetForceKeepSessionState() OVERRIDE;

 private:
  class Task;
  class GetChannelIDTask;
  class SetChannelIDTask;
  class DeleteChannelIDTask;
  class DeleteAllCreatedBetweenTask;
  class GetAllChannelIDsTask;

  
  void DeleteAllInMemory();

  
  
  
  
  
  void InitIfNecessary() {
    if (!initialized_) {
      if (store_.get()) {
        InitStore();
      } else {
        loaded_ = true;
      }
      initialized_ = true;
    }
  }

  
  
  void InitStore();

  
  void OnLoaded(scoped_ptr<ScopedVector<ChannelID> > certs);

  
  
  void SyncSetChannelID(
      const std::string& server_identifier,
      base::Time creation_time,
      base::Time expiration_time,
      const std::string& private_key,
      const std::string& cert);
  void SyncDeleteChannelID(const std::string& server_identifier);
  void SyncDeleteAllCreatedBetween(base::Time delete_begin,
                                   base::Time delete_end);
  void SyncGetAllChannelIDs(ChannelIDList* channel_id_list);

  
  void EnqueueTask(scoped_ptr<Task> task);
  
  
  void RunOrEnqueueTask(scoped_ptr<Task> task);

  
  
  
  void InternalDeleteChannelID(const std::string& server);

  
  
  
  void InternalInsertChannelID(const std::string& server_identifier,
                               ChannelID* channel_id);

  
  
  bool initialized_;

  
  
  bool loaded_;

  
  ScopedVector<Task> waiting_tasks_;
  base::TimeTicks waiting_tasks_start_time_;

  scoped_refptr<PersistentStore> store_;

  ChannelIDMap channel_ids_;

  base::WeakPtrFactory<DefaultChannelIDStore> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DefaultChannelIDStore);
};

typedef base::RefCountedThreadSafe<DefaultChannelIDStore::PersistentStore>
    RefcountedPersistentStore;

class NET_EXPORT DefaultChannelIDStore::PersistentStore
    : public RefcountedPersistentStore {
 public:
  typedef base::Callback<void(scoped_ptr<ScopedVector<ChannelID> >)>
      LoadedCallback;

  
  
  
  
  virtual void Load(const LoadedCallback& loaded_callback) = 0;

  virtual void AddChannelID(const ChannelID& channel_id) = 0;

  virtual void DeleteChannelID(const ChannelID& channel_id) = 0;

  
  
  virtual void SetForceKeepSessionState() = 0;

 protected:
  friend class base::RefCountedThreadSafe<PersistentStore>;

  PersistentStore();
  virtual ~PersistentStore();

 private:
  DISALLOW_COPY_AND_ASSIGN(PersistentStore);
};

}  

#endif  

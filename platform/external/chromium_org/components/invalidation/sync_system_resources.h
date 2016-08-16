// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_SYNC_SYSTEM_RESOURCES_H_
#define COMPONENTS_INVALIDATION_SYNC_SYSTEM_RESOURCES_H_

#include <set>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/threading/non_thread_safe.h"
#include "base/values.h"
#include "components/invalidation/invalidation_export.h"
#include "components/invalidation/invalidator_state.h"
#include "components/invalidation/state_writer.h"
#include "google/cacheinvalidation/include/system-resources.h"
#include "jingle/notifier/base/notifier_options.h"

namespace syncer {

class GCMNetworkChannelDelegate;

class SyncLogger : public invalidation::Logger {
 public:
  SyncLogger();

  virtual ~SyncLogger();

  
  virtual void Log(LogLevel level, const char* file, int line,
                   const char* format, ...) OVERRIDE;

  virtual void SetSystemResources(
      invalidation::SystemResources* resources) OVERRIDE;
};

class SyncInvalidationScheduler : public invalidation::Scheduler {
 public:
  SyncInvalidationScheduler();

  virtual ~SyncInvalidationScheduler();

  
  void Start();
  void Stop();

  
  virtual void Schedule(invalidation::TimeDelta delay,
                        invalidation::Closure* task) OVERRIDE;

  virtual bool IsRunningOnThread() const OVERRIDE;

  virtual invalidation::Time GetCurrentTime() const OVERRIDE;

  virtual void SetSystemResources(
      invalidation::SystemResources* resources) OVERRIDE;

 private:
  
  void RunPostedTask(invalidation::Closure* task);

  
  std::set<invalidation::Closure*> posted_tasks_;

  const base::MessageLoop* created_on_loop_;
  bool is_started_;
  bool is_stopped_;

  base::WeakPtrFactory<SyncInvalidationScheduler> weak_factory_;
};

class INVALIDATION_EXPORT_PRIVATE SyncNetworkChannel
    : public NON_EXPORTED_BASE(invalidation::NetworkChannel) {
 public:
  class Observer {
   public:
    
    
    
    
    virtual void OnNetworkChannelStateChanged(
        InvalidatorState invalidator_state) = 0;
  };

  SyncNetworkChannel();

  virtual ~SyncNetworkChannel();

  
  
  
  virtual void SetMessageReceiver(
      invalidation::MessageCallback* incoming_receiver) OVERRIDE;
  virtual void AddNetworkStatusReceiver(
      invalidation::NetworkStatusCallback* network_status_receiver) OVERRIDE;
  virtual void SetSystemResources(
      invalidation::SystemResources* resources) OVERRIDE;

  
  
  virtual void UpdateCredentials(const std::string& email,
      const std::string& token) = 0;

  
  
  
  virtual int GetInvalidationClientType() = 0;

  
  
  virtual void RequestDetailedStatus(
      base::Callback<void(const base::DictionaryValue&)> callback) = 0;

  
  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  static scoped_ptr<SyncNetworkChannel> CreatePushClientChannel(
      const notifier::NotifierOptions& notifier_options);
  static scoped_ptr<SyncNetworkChannel> CreateGCMNetworkChannel(
      scoped_refptr<net::URLRequestContextGetter> request_context_getter,
      scoped_ptr<GCMNetworkChannelDelegate> delegate);

  
  int GetReceivedMessagesCount() const;

 protected:
  
  
  
  void NotifyNetworkStatusChange(bool online);

  
  
  
  
  void NotifyChannelStateChange(InvalidatorState invalidator_state);

  
  
  bool DeliverIncomingMessage(const std::string& message);

 private:
  typedef std::vector<invalidation::NetworkStatusCallback*>
      NetworkStatusReceiverList;

  
  scoped_ptr<invalidation::MessageCallback> incoming_receiver_;
  NetworkStatusReceiverList network_status_receivers_;

  
  bool last_network_status_;

  int received_messages_count_;

  ObserverList<Observer> observers_;
};

class SyncStorage : public invalidation::Storage {
 public:
  SyncStorage(StateWriter* state_writer, invalidation::Scheduler* scheduler);

  virtual ~SyncStorage();

  void SetInitialState(const std::string& value) {
    cached_state_ = value;
  }

  
  virtual void WriteKey(const std::string& key, const std::string& value,
                        invalidation::WriteKeyCallback* done) OVERRIDE;

  virtual void ReadKey(const std::string& key,
                       invalidation::ReadKeyCallback* done) OVERRIDE;

  virtual void DeleteKey(const std::string& key,
                         invalidation::DeleteKeyCallback* done) OVERRIDE;

  virtual void ReadAllKeys(
      invalidation::ReadAllKeysCallback* key_callback) OVERRIDE;

  virtual void SetSystemResources(
      invalidation::SystemResources* resources) OVERRIDE;

 private:
  
  void RunAndDeleteWriteKeyCallback(
      invalidation::WriteKeyCallback* callback);

  
  void RunAndDeleteReadKeyCallback(
      invalidation::ReadKeyCallback* callback, const std::string& value);

  StateWriter* state_writer_;
  invalidation::Scheduler* scheduler_;
  std::string cached_state_;
};

class INVALIDATION_EXPORT_PRIVATE SyncSystemResources
    : public NON_EXPORTED_BASE(invalidation::SystemResources) {
 public:
  SyncSystemResources(SyncNetworkChannel* sync_network_channel,
                      StateWriter* state_writer);

  virtual ~SyncSystemResources();

  
  virtual void Start() OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual bool IsStarted() const OVERRIDE;
  virtual void set_platform(const std::string& platform);
  virtual std::string platform() const OVERRIDE;
  virtual SyncLogger* logger() OVERRIDE;
  virtual SyncStorage* storage() OVERRIDE;
  virtual SyncNetworkChannel* network() OVERRIDE;
  virtual SyncInvalidationScheduler* internal_scheduler() OVERRIDE;
  virtual SyncInvalidationScheduler* listener_scheduler() OVERRIDE;

 private:
  bool is_started_;
  std::string platform_;
  scoped_ptr<SyncLogger> logger_;
  scoped_ptr<SyncInvalidationScheduler> internal_scheduler_;
  scoped_ptr<SyncInvalidationScheduler> listener_scheduler_;
  scoped_ptr<SyncStorage> storage_;
  
  SyncNetworkChannel* sync_network_channel_;
};

}  

#endif  

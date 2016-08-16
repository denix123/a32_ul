// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_STORE_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_STORE_H_

#include <vector>

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list_threadsafe.h"
#include "base/threading/thread.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "components/password_manager/core/browser/password_store_change.h"
#include "components/password_manager/core/browser/password_store_sync.h"
#include "sync/api/syncable_service.h"

class Task;

namespace autofill {
struct PasswordForm;
}

namespace browser_sync {
class PasswordChangeProcessor;
class PasswordDataTypeController;
class PasswordModelAssociator;
class PasswordModelWorker;
}

namespace password_manager {
class PasswordStore;
}  

namespace passwords_helper {
void AddLogin(password_manager::PasswordStore* store,
              const autofill::PasswordForm& form);
void RemoveLogin(password_manager::PasswordStore* store,
                 const autofill::PasswordForm& form);
void UpdateLogin(password_manager::PasswordStore* store,
                 const autofill::PasswordForm& form);
}

namespace syncer {
class SyncableService;
}

namespace password_manager {

class PasswordStoreConsumer;
class PasswordSyncableService;

class PasswordStore : protected PasswordStoreSync,
                      public base::RefCountedThreadSafe<PasswordStore> {
 public:
  
  
  enum AuthorizationPromptPolicy {
    ALLOW_PROMPT,
    DISALLOW_PROMPT
  };

  
  
  
  class GetLoginsRequest {
   public:
    explicit GetLoginsRequest(PasswordStoreConsumer* consumer);
    virtual ~GetLoginsRequest();

    void set_ignore_logins_cutoff(base::Time cutoff) {
      ignore_logins_cutoff_ = cutoff;
    }

    
    void ApplyIgnoreLoginsCutoff();

    
    void ForwardResult();

    std::vector<autofill::PasswordForm*>* result() const {
      return result_.get();
    }

   private:
    
    base::Time ignore_logins_cutoff_;

    base::WeakPtr<PasswordStoreConsumer> consumer_weak_;

    
    
    
    
    scoped_ptr< std::vector<autofill::PasswordForm*> > result_;

    base::ThreadChecker thread_checker_;
    scoped_refptr<base::MessageLoopProxy> origin_loop_;

    DISALLOW_COPY_AND_ASSIGN(GetLoginsRequest);
  };

  
  
  
  class Observer {
   public:
    
    
    virtual void OnLoginsChanged(const PasswordStoreChangeList& changes) = 0;

   protected:
    virtual ~Observer() {}
  };

  PasswordStore(
      scoped_refptr<base::SingleThreadTaskRunner> main_thread_runner,
      scoped_refptr<base::SingleThreadTaskRunner> db_thread_runner);

  
  
  virtual bool Init(const syncer::SyncableService::StartSyncFlare& flare,
                    const std::string& sync_username);

  
  virtual void AddLogin(const autofill::PasswordForm& form);

  
  virtual void UpdateLogin(const autofill::PasswordForm& form);

  
  virtual void RemoveLogin(const autofill::PasswordForm& form);

  
  virtual void RemoveLoginsCreatedBetween(base::Time delete_begin,
                                          base::Time delete_end);

  
  virtual void RemoveLoginsSyncedBetween(base::Time delete_begin,
                                         base::Time delete_end);

  
  
  
  
  
  
  
  virtual void GetLogins(
      const autofill::PasswordForm& form,
      AuthorizationPromptPolicy prompt_policy,
      PasswordStoreConsumer* consumer);

  
  
  
  virtual void GetAutofillableLogins(PasswordStoreConsumer* consumer);

  
  
  
  virtual void GetBlacklistLogins(PasswordStoreConsumer* consumer);

  
  virtual void ReportMetrics(const std::string& sync_username);

  
  void AddObserver(Observer* observer);

  
  void RemoveObserver(Observer* observer);

  
  bool ScheduleTask(const base::Closure& task);

  
  
  virtual void Shutdown();

#if defined(PASSWORD_MANAGER_ENABLE_SYNC)
  base::WeakPtr<syncer::SyncableService> GetPasswordSyncableService();
#endif

 protected:
  friend class base::RefCountedThreadSafe<PasswordStore>;
  FRIEND_TEST_ALL_PREFIXES(PasswordStoreTest, IgnoreOldWwwGoogleLogins);

  typedef base::Callback<PasswordStoreChangeList(void)> ModificationTask;

  virtual ~PasswordStore();

  
  
  
  virtual scoped_refptr<base::SingleThreadTaskRunner> GetBackgroundTaskRunner();

  
  
  virtual void ReportMetricsImpl(const std::string& sync_username) = 0;

  
  
  
  virtual PasswordStoreChangeList AddLoginImpl(
      const autofill::PasswordForm& form) = 0;
  virtual PasswordStoreChangeList UpdateLoginImpl(
      const autofill::PasswordForm& form) = 0;
  virtual PasswordStoreChangeList RemoveLoginImpl(
      const autofill::PasswordForm& form) = 0;

  
  virtual PasswordStoreChangeList RemoveLoginsCreatedBetweenImpl(
      base::Time delete_begin,
      base::Time delete_end) = 0;

  
  virtual PasswordStoreChangeList RemoveLoginsSyncedBetweenImpl(
      base::Time delete_begin,
      base::Time delete_end) = 0;

  typedef base::Callback<void(const std::vector<autofill::PasswordForm*>&)>
      ConsumerCallbackRunner;  

  
  
  
  virtual void GetLoginsImpl(
      const autofill::PasswordForm& form,
      AuthorizationPromptPolicy prompt_policy,
      const ConsumerCallbackRunner& callback_runner) = 0;

  
  virtual void GetAutofillableLoginsImpl(GetLoginsRequest* request) = 0;

  
  virtual void GetBlacklistLoginsImpl(GetLoginsRequest* request) = 0;

  
  
  virtual void ForwardLoginsResult(GetLoginsRequest* request);

  
  void LogStatsForBulkDeletion(int num_deletions);

  
  
  
  
  virtual void NotifyLoginsChanged(
      const PasswordStoreChangeList& changes) OVERRIDE;

  
  scoped_refptr<base::SingleThreadTaskRunner> main_thread_runner_;

  
  
  scoped_refptr<base::SingleThreadTaskRunner> db_thread_runner_;

 private:
  
  
  template<typename BackendFunc>
  void Schedule(BackendFunc func, PasswordStoreConsumer* consumer);

  
  
  
  
  
  virtual void WrapModificationTask(ModificationTask task);

  
  
  
  
  void CopyAndForwardLoginsResult(
      PasswordStore::GetLoginsRequest* request,
      const std::vector<autofill::PasswordForm*>& matched_forms);

#if defined(PASSWORD_MANAGER_ENABLE_SYNC)
  
  void InitSyncableService(
      const syncer::SyncableService::StartSyncFlare& flare);

  
  void DestroySyncableService();
#endif

  
  scoped_refptr<ObserverListThreadSafe<Observer> > observers_;

  scoped_ptr<PasswordSyncableService> syncable_service_;

  bool shutdown_called_;

  DISALLOW_COPY_AND_ASSIGN(PasswordStore);
};

}  

#endif  

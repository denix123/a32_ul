// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_STORAGE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_STORAGE_H_

#include <deque>
#include <map>
#include <set>
#include <vector>

#include "base/bind.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/service_worker/service_worker_database.h"
#include "content/browser/service_worker/service_worker_version.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "url/gurl.h"

namespace base {
class SequencedTaskRunner;
class SingleThreadTaskRunner;
}

namespace storage {
class QuotaManagerProxy;
}

namespace content {

class ServiceWorkerContextCore;
class ServiceWorkerDiskCache;
class ServiceWorkerRegistration;
class ServiceWorkerRegistrationInfo;
class ServiceWorkerResponseReader;
class ServiceWorkerResponseWriter;

class CONTENT_EXPORT ServiceWorkerStorage
    : NON_EXPORTED_BASE(public ServiceWorkerVersion::Listener) {
 public:
  typedef std::vector<ServiceWorkerDatabase::ResourceRecord> ResourceList;
  typedef base::Callback<void(ServiceWorkerStatusCode status)> StatusCallback;
  typedef base::Callback<void(ServiceWorkerStatusCode status,
                              const scoped_refptr<ServiceWorkerRegistration>&
                                  registration)> FindRegistrationCallback;
  typedef base::Callback<
      void(const std::vector<ServiceWorkerRegistrationInfo>& registrations)>
          GetAllRegistrationInfosCallback;
  typedef base::Callback<
      void(ServiceWorkerStatusCode status, bool are_equal)>
          CompareCallback;

  virtual ~ServiceWorkerStorage();

  static scoped_ptr<ServiceWorkerStorage> Create(
      const base::FilePath& path,
      base::WeakPtr<ServiceWorkerContextCore> context,
      const scoped_refptr<base::SequencedTaskRunner>& database_task_runner,
      const scoped_refptr<base::SingleThreadTaskRunner>& disk_cache_thread,
      storage::QuotaManagerProxy* quota_manager_proxy);

  
  static scoped_ptr<ServiceWorkerStorage> Create(
      base::WeakPtr<ServiceWorkerContextCore> context,
      ServiceWorkerStorage* old_storage);

  
  
  
  
  
  
  
  
  
  void FindRegistrationForDocument(const GURL& document_url,
                                   const FindRegistrationCallback& callback);
  void FindRegistrationForPattern(const GURL& scope,
                                  const FindRegistrationCallback& callback);
  void FindRegistrationForId(int64 registration_id,
                             const GURL& origin,
                             const FindRegistrationCallback& callback);

  ServiceWorkerRegistration* GetUninstallingRegistration(const GURL& scope);

  
  void GetAllRegistrations(const GetAllRegistrationInfosCallback& callback);

  
  
  
  
  void StoreRegistration(
      ServiceWorkerRegistration* registration,
      ServiceWorkerVersion* version,
      const StatusCallback& callback);

  
  void UpdateToActiveState(
      ServiceWorkerRegistration* registration,
      const StatusCallback& callback);

  
  
  void UpdateLastUpdateCheckTime(ServiceWorkerRegistration* registration);

  
  
  
  void DeleteRegistration(int64 registration_id,
                          const GURL& origin,
                          const StatusCallback& callback);

  scoped_ptr<ServiceWorkerResponseReader> CreateResponseReader(
      int64 response_id);
  scoped_ptr<ServiceWorkerResponseWriter> CreateResponseWriter(
      int64 response_id);

  
  
  void StoreUncommittedResponseId(int64 id);

  
  
  void DoomUncommittedResponse(int64 id);

  
  void CompareScriptResources(int64 lhs_id, int64 rhs_id,
                              const CompareCallback& callback);

  
  void DeleteAndStartOver(const StatusCallback& callback);

  
  int64 NewRegistrationId();
  int64 NewVersionId();
  int64 NewResourceId();

  
  
  void NotifyInstallingRegistration(
      ServiceWorkerRegistration* registration);
  void NotifyDoneInstallingRegistration(
      ServiceWorkerRegistration* registration,
      ServiceWorkerVersion* version,
      ServiceWorkerStatusCode status);
  void NotifyUninstallingRegistration(ServiceWorkerRegistration* registration);
  void NotifyDoneUninstallingRegistration(
      ServiceWorkerRegistration* registration);

  void Disable();
  bool IsDisabled() const;

  
  void PurgeResources(const ResourceList& resources);

 private:
  friend class ServiceWorkerResourceStorageTest;
  friend class ServiceWorkerControlleeRequestHandlerTest;
  friend class ServiceWorkerContextRequestHandlerTest;
  friend class ServiceWorkerRequestHandlerTest;
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerResourceStorageTest,
                           DeleteRegistration_NoLiveVersion);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerResourceStorageTest,
                           DeleteRegistration_WaitingVersion);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerResourceStorageTest,
                           DeleteRegistration_ActiveVersion);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerResourceStorageTest,
                           UpdateRegistration);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerResourceStorageDiskTest,
                           CleanupOnRestart);

  struct InitialData {
    int64 next_registration_id;
    int64 next_version_id;
    int64 next_resource_id;
    std::set<GURL> origins;

    InitialData();
    ~InitialData();
  };

  
  struct DidDeleteRegistrationParams {
    int64 registration_id;
    GURL origin;
    StatusCallback callback;

    DidDeleteRegistrationParams();
    ~DidDeleteRegistrationParams();
  };

  typedef std::vector<ServiceWorkerDatabase::RegistrationData> RegistrationList;
  typedef std::map<int64, scoped_refptr<ServiceWorkerRegistration> >
      RegistrationRefsById;
  typedef base::Callback<void(
      InitialData* data,
      ServiceWorkerDatabase::Status status)> InitializeCallback;
  typedef base::Callback<
      void(const GURL& origin,
           int64 deleted_version_id,
           const std::vector<int64>& newly_purgeable_resources,
           ServiceWorkerDatabase::Status status)> WriteRegistrationCallback;
  typedef base::Callback<
      void(bool origin_is_deletable,
           int64 version_id,
           const std::vector<int64>& newly_purgeable_resources,
           ServiceWorkerDatabase::Status status)> DeleteRegistrationCallback;
  typedef base::Callback<void(
      const ServiceWorkerDatabase::RegistrationData& data,
      const ResourceList& resources,
      ServiceWorkerDatabase::Status status)> FindInDBCallback;
  typedef base::Callback<void(const std::vector<int64>& resource_ids,
                              ServiceWorkerDatabase::Status status)>
      GetResourcesCallback;

  ServiceWorkerStorage(
      const base::FilePath& path,
      base::WeakPtr<ServiceWorkerContextCore> context,
      const scoped_refptr<base::SequencedTaskRunner>& database_task_runner,
      const scoped_refptr<base::SingleThreadTaskRunner>& disk_cache_thread,
      storage::QuotaManagerProxy* quota_manager_proxy);

  base::FilePath GetDatabasePath();
  base::FilePath GetDiskCachePath();

  bool LazyInitialize(
      const base::Closure& callback);
  void DidReadInitialData(
      InitialData* data,
      ServiceWorkerDatabase::Status status);
  void DidFindRegistrationForDocument(
      const GURL& document_url,
      const FindRegistrationCallback& callback,
      const ServiceWorkerDatabase::RegistrationData& data,
      const ResourceList& resources,
      ServiceWorkerDatabase::Status status);
  void DidFindRegistrationForPattern(
      const GURL& scope,
      const FindRegistrationCallback& callback,
      const ServiceWorkerDatabase::RegistrationData& data,
      const ResourceList& resources,
      ServiceWorkerDatabase::Status status);
  void DidFindRegistrationForId(
      const FindRegistrationCallback& callback,
      const ServiceWorkerDatabase::RegistrationData& data,
      const ResourceList& resources,
      ServiceWorkerDatabase::Status status);
  void DidGetAllRegistrations(
      const GetAllRegistrationInfosCallback& callback,
      RegistrationList* registrations,
      ServiceWorkerDatabase::Status status);
  void DidStoreRegistration(const StatusCallback& callback,
                            const GURL& origin,
                            int64 deleted_version_id,
                            const std::vector<int64>& newly_purgeable_resources,
                            ServiceWorkerDatabase::Status status);
  void DidUpdateToActiveState(
      const StatusCallback& callback,
      ServiceWorkerDatabase::Status status);
  void DidDeleteRegistration(
      const DidDeleteRegistrationParams& params,
      bool origin_is_deletable,
      int64 version_id,
      const std::vector<int64>& newly_purgeable_resources,
      ServiceWorkerDatabase::Status status);
  void ReturnFoundRegistration(
      const FindRegistrationCallback& callback,
      const ServiceWorkerDatabase::RegistrationData& data,
      const ResourceList& resources);

  scoped_refptr<ServiceWorkerRegistration> GetOrCreateRegistration(
      const ServiceWorkerDatabase::RegistrationData& data,
      const ResourceList& resources);
  ServiceWorkerRegistration* FindInstallingRegistrationForDocument(
      const GURL& document_url);
  ServiceWorkerRegistration* FindInstallingRegistrationForPattern(
      const GURL& scope);
  ServiceWorkerRegistration* FindInstallingRegistrationForId(
      int64 registration_id);

  
  ServiceWorkerDiskCache* disk_cache();
  void OnDiskCacheInitialized(int rv);

  void StartPurgingResources(const std::vector<int64>& ids);
  void StartPurgingResources(const ResourceList& resources);
  void ContinuePurgingResources();
  void PurgeResource(int64 id);
  void OnResourcePurged(int64 id, int rv);

  
  
  
  void DeleteStaleResources();
  void DidCollectStaleResources(const std::vector<int64>& stale_resource_ids,
                                ServiceWorkerDatabase::Status status);

  
  static void CollectStaleResourcesFromDB(
      ServiceWorkerDatabase* database,
      scoped_refptr<base::SequencedTaskRunner> original_task_runner,
      const GetResourcesCallback& callback);
  static void ReadInitialDataFromDB(
      ServiceWorkerDatabase* database,
      scoped_refptr<base::SequencedTaskRunner> original_task_runner,
      const InitializeCallback& callback);
  static void DeleteRegistrationFromDB(
      ServiceWorkerDatabase* database,
      scoped_refptr<base::SequencedTaskRunner> original_task_runner,
      int64 registration_id,
      const GURL& origin,
      const DeleteRegistrationCallback& callback);
  static void WriteRegistrationInDB(
      ServiceWorkerDatabase* database,
      scoped_refptr<base::SequencedTaskRunner> original_task_runner,
      const ServiceWorkerDatabase::RegistrationData& registration,
      const ResourceList& resources,
      const WriteRegistrationCallback& callback);
  static void FindForDocumentInDB(
      ServiceWorkerDatabase* database,
      scoped_refptr<base::SequencedTaskRunner> original_task_runner,
      const GURL& document_url,
      const FindInDBCallback& callback);
  static void FindForPatternInDB(
      ServiceWorkerDatabase* database,
      scoped_refptr<base::SequencedTaskRunner> original_task_runner,
      const GURL& scope,
      const FindInDBCallback& callback);
  static void FindForIdInDB(
      ServiceWorkerDatabase* database,
      scoped_refptr<base::SequencedTaskRunner> original_task_runner,
      int64 registration_id,
      const GURL& origin,
      const FindInDBCallback& callback);

  void ScheduleDeleteAndStartOver();
  void DidDeleteDatabase(
      const StatusCallback& callback,
      ServiceWorkerDatabase::Status status);
  void DidDeleteDiskCache(
      const StatusCallback& callback,
      bool result);

  
  RegistrationRefsById installing_registrations_;
  RegistrationRefsById uninstalling_registrations_;

  
  std::set<GURL> registered_origins_;

  
  std::vector<base::Closure> pending_tasks_;

  int64 next_registration_id_;
  int64 next_version_id_;
  int64 next_resource_id_;

  enum State {
    UNINITIALIZED,
    INITIALIZING,
    INITIALIZED,
    DISABLED,
  };
  State state_;

  base::FilePath path_;
  base::WeakPtr<ServiceWorkerContextCore> context_;

  
  scoped_ptr<ServiceWorkerDatabase> database_;

  scoped_refptr<base::SequencedTaskRunner> database_task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> disk_cache_thread_;
  scoped_refptr<storage::QuotaManagerProxy> quota_manager_proxy_;
  scoped_ptr<ServiceWorkerDiskCache> disk_cache_;
  std::deque<int64> purgeable_resource_ids_;
  bool is_purge_pending_;
  bool has_checked_for_stale_resources_;
  std::set<int64> pending_deletions_;

  base::WeakPtrFactory<ServiceWorkerStorage> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerStorage);
};

}  

#endif  

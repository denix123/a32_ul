// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_DATABASE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_DATABASE_H_

#include <map>
#include <set>
#include <vector>

#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/sequence_checker.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "url/gurl.h"

namespace leveldb {
class DB;
class Env;
class Status;
class WriteBatch;
}

namespace content {

class CONTENT_EXPORT ServiceWorkerDatabase {
 public:
  
  explicit ServiceWorkerDatabase(const base::FilePath& path);
  ~ServiceWorkerDatabase();

  
  enum Status {
    STATUS_OK,
    STATUS_ERROR_NOT_FOUND,
    STATUS_ERROR_IO_ERROR,
    STATUS_ERROR_CORRUPTED,
    STATUS_ERROR_FAILED,
    STATUS_ERROR_MAX,
  };

  struct CONTENT_EXPORT RegistrationData {
    
    int64 registration_id;
    GURL scope;

    
    
    
    GURL script;
    int64 version_id;
    bool is_active;
    bool has_fetch_handler;
    base::Time last_update_check;

    RegistrationData();
    ~RegistrationData();
  };

  struct ResourceRecord {
    int64 resource_id;
    GURL url;

    ResourceRecord() {}
    ResourceRecord(int64 id, GURL url) : resource_id(id), url(url) {}
  };

  
  
  
  Status GetNextAvailableIds(
      int64* next_avail_registration_id,
      int64* next_avail_version_id,
      int64* next_avail_resource_id);

  
  
  
  Status GetOriginsWithRegistrations(std::set<GURL>* origins);

  
  
  Status GetRegistrationsForOrigin(
      const GURL& origin,
      std::vector<RegistrationData>* registrations);

  
  
  Status GetAllRegistrations(std::vector<RegistrationData>* registrations);

  
  
  
  

  
  
  
  Status ReadRegistration(
      int64 registration_id,
      const GURL& origin,
      RegistrationData* registration,
      std::vector<ResourceRecord>* resources);

  
  
  
  
  
  
  
  
  // Returns OK they are successfully written. Otherwise, returns an error.
  Status WriteRegistration(const RegistrationData& registration,
                           const std::vector<ResourceRecord>& resources,
                           int64* deleted_version_id,
                           std::vector<int64>* newly_purgeable_resources);

  
  
  Status UpdateVersionToActive(
      int64 registration_id,
      const GURL& origin);

  
  
  Status UpdateLastCheckTime(
      int64 registration_id,
      const GURL& origin,
      const base::Time& time);

  
  
  
  
  
  
  Status DeleteRegistration(int64 registration_id,
                            const GURL& origin,
                            int64* version_id,
                            std::vector<int64>* newly_purgeable_resources);

  
  
  
  
  
  

  
  
  Status GetUncommittedResourceIds(std::set<int64>* ids);

  
  
  Status WriteUncommittedResourceIds(const std::set<int64>& ids);

  
  
  Status ClearUncommittedResourceIds(const std::set<int64>& ids);

  
  
  Status GetPurgeableResourceIds(std::set<int64>* ids);

  
  
  Status WritePurgeableResourceIds(const std::set<int64>& ids);

  
  
  Status ClearPurgeableResourceIds(const std::set<int64>& ids);

  
  
  Status PurgeUncommittedResourceIds(const std::set<int64>& ids);

  
  
  
  
  Status DeleteAllDataForOrigin(
      const GURL& origin,
      std::vector<int64>* newly_purgeable_resources);

  
  
  Status DestroyDatabase();

 private:
  
  
  
  
  Status LazyOpen(bool create_if_missing);

  
  
  
  bool IsNewOrNonexistentDatabase(Status status);

  
  
  
  Status ReadNextAvailableId(
      const char* id_key,
      int64* next_avail_id);

  
  
  Status ReadRegistrationData(
      int64 registration_id,
      const GURL& origin,
      RegistrationData* registration);

  
  
  
  Status ReadResourceRecords(
      int64 version_id,
      std::vector<ResourceRecord>* resources);

  
  
  
  Status DeleteResourceRecords(
      int64 version_id,
      std::vector<int64>* newly_purgeable_resources,
      leveldb::WriteBatch* batch);

  
  
  
  Status ReadResourceIds(
      const char* id_key_prefix,
      std::set<int64>* ids);

  
  
  Status WriteResourceIds(
      const char* id_key_prefix,
      const std::set<int64>& ids);
  Status WriteResourceIdsInBatch(
      const char* id_key_prefix,
      const std::set<int64>& ids,
      leveldb::WriteBatch* batch);

  
  
  
  Status DeleteResourceIds(
      const char* id_key_prefix,
      const std::set<int64>& ids);
  Status DeleteResourceIdsInBatch(
      const char* id_key_prefix,
      const std::set<int64>& ids,
      leveldb::WriteBatch* batch);

  
  // been written anything yet, sets |db_version| to 0 and returns OK.
  Status ReadDatabaseVersion(int64* db_version);

  
  
  
  Status WriteBatch(leveldb::WriteBatch* batch);

  
  
  void BumpNextRegistrationIdIfNeeded(
      int64 used_id,
      leveldb::WriteBatch* batch);
  void BumpNextResourceIdIfNeeded(
      int64 used_id,
      leveldb::WriteBatch* batch);
  void BumpNextVersionIdIfNeeded(
      int64 used_id,
      leveldb::WriteBatch* batch);

  bool IsOpen();

  void Disable(
      const tracked_objects::Location& from_here,
      Status status);
  void HandleOpenResult(
      const tracked_objects::Location& from_here,
      Status status);
  void HandleReadResult(
      const tracked_objects::Location& from_here,
      Status status);
  void HandleWriteResult(
      const tracked_objects::Location& from_here,
      Status status);

  base::FilePath path_;
  scoped_ptr<leveldb::Env> env_;
  scoped_ptr<leveldb::DB> db_;

  int64 next_avail_registration_id_;
  int64 next_avail_resource_id_;
  int64 next_avail_version_id_;

  enum State {
    UNINITIALIZED,
    INITIALIZED,
    DISABLED,
  };
  State state_;

  base::SequenceChecker sequence_checker_;

  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerDatabaseTest, OpenDatabase);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerDatabaseTest, OpenDatabase_InMemory);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerDatabaseTest, DatabaseVersion);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerDatabaseTest, GetNextAvailableIds);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerDatabaseTest, DestroyDatabase);

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerDatabase);
};

}  

#endif  

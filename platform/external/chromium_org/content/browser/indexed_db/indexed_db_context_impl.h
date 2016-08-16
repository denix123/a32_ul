// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_CONTEXT_IMPL_H_
#define CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_CONTEXT_IMPL_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/browser_main_loop.h"
#include "content/browser/indexed_db/indexed_db_factory.h"
#include "content/public/browser/indexed_db_context.h"
#include "storage/common/quota/quota_types.h"
#include "url/gurl.h"

class GURL;

namespace base {
class ListValue;
class FilePath;
class SequencedTaskRunner;
}

namespace storage {
class QuotaManagerProxy;
class SpecialStoragePolicy;
}

namespace content {

class IndexedDBConnection;

class CONTENT_EXPORT IndexedDBContextImpl
    : NON_EXPORTED_BASE(public IndexedDBContext) {
 public:
  
  enum ForceCloseReason {
    FORCE_CLOSE_DELETE_ORIGIN = 0,
    FORCE_CLOSE_BACKING_STORE_FAILURE,
    FORCE_CLOSE_INTERNALS_PAGE,
    FORCE_CLOSE_REASON_MAX
  };

  
  static const base::FilePath::CharType kIndexedDBDirectory[];

  
  IndexedDBContextImpl(const base::FilePath& data_path,
                       storage::SpecialStoragePolicy* special_storage_policy,
                       storage::QuotaManagerProxy* quota_manager_proxy,
                       base::SequencedTaskRunner* task_runner);

  IndexedDBFactory* GetIDBFactory();

  
  void SetForceKeepSessionState() { force_keep_session_state_ = true; }

  
  virtual base::SequencedTaskRunner* TaskRunner() const OVERRIDE;
  virtual std::vector<IndexedDBInfo> GetAllOriginsInfo() OVERRIDE;
  virtual int64 GetOriginDiskUsage(const GURL& origin_url) OVERRIDE;
  virtual void DeleteForOrigin(const GURL& origin_url) OVERRIDE;
  virtual base::FilePath GetFilePathForTesting(
      const std::string& origin_id) const OVERRIDE;
  virtual void SetTaskRunnerForTesting(base::SequencedTaskRunner* task_runner)
      OVERRIDE;

  
  void ConnectionOpened(const GURL& origin_url, IndexedDBConnection* db);
  void ConnectionClosed(const GURL& origin_url, IndexedDBConnection* db);
  void TransactionComplete(const GURL& origin_url);
  void DatabaseDeleted(const GURL& origin_url);
  bool WouldBeOverQuota(const GURL& origin_url, int64 additional_bytes);
  bool IsOverQuota(const GURL& origin_url);

  storage::QuotaManagerProxy* quota_manager_proxy();

  std::vector<GURL> GetAllOrigins();
  base::Time GetOriginLastModified(const GURL& origin_url);
  base::ListValue* GetAllOriginsDetails();

  
  
  void ForceClose(const GURL origin_url, ForceCloseReason reason);

  base::FilePath GetFilePath(const GURL& origin_url) const;
  base::FilePath data_path() const { return data_path_; }
  bool IsInOriginSet(const GURL& origin_url) {
    std::set<GURL>* set = GetOriginSet();
    return set->find(origin_url) != set->end();
  }
  size_t GetConnectionCount(const GURL& origin_url);

  
  void set_data_path_for_testing(const base::FilePath& data_path) {
    data_path_ = data_path;
  }

  bool is_incognito() const { return data_path_.empty(); }

 protected:
  virtual ~IndexedDBContextImpl();

 private:
  FRIEND_TEST_ALL_PREFIXES(IndexedDBTest, ClearLocalState);
  FRIEND_TEST_ALL_PREFIXES(IndexedDBTest, ClearSessionOnlyDatabases);
  FRIEND_TEST_ALL_PREFIXES(IndexedDBTest, SetForceKeepSessionState);
  FRIEND_TEST_ALL_PREFIXES(IndexedDBTest, ForceCloseOpenDatabasesOnDelete);
  friend class IndexedDBQuotaClientTest;

  typedef std::map<GURL, int64> OriginToSizeMap;
  class IndexedDBGetUsageAndQuotaCallback;

  base::FilePath GetIndexedDBFilePath(const std::string& origin_id) const;
  int64 ReadUsageFromDisk(const GURL& origin_url) const;
  void EnsureDiskUsageCacheInitialized(const GURL& origin_url);
  void QueryDiskAndUpdateQuotaUsage(const GURL& origin_url);
  void GotUsageAndQuota(const GURL& origin_url,
                        storage::QuotaStatusCode,
                        int64 usage,
                        int64 quota);
  void GotUpdatedQuota(const GURL& origin_url, int64 usage, int64 quota);
  void QueryAvailableQuota(const GURL& origin_url);

  std::set<GURL>* GetOriginSet();
  bool AddToOriginSet(const GURL& origin_url) {
    return GetOriginSet()->insert(origin_url).second;
  }
  void RemoveFromOriginSet(const GURL& origin_url) {
    GetOriginSet()->erase(origin_url);
  }

  
  void ResetCaches();

  scoped_refptr<IndexedDBFactory> factory_;
  base::FilePath data_path_;
  
  bool force_keep_session_state_;
  scoped_refptr<storage::SpecialStoragePolicy> special_storage_policy_;
  scoped_refptr<storage::QuotaManagerProxy> quota_manager_proxy_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  scoped_ptr<std::set<GURL> > origin_set_;
  OriginToSizeMap origin_size_map_;
  OriginToSizeMap space_available_map_;

  DISALLOW_COPY_AND_ASSIGN(IndexedDBContextImpl);
};

}  

#endif  

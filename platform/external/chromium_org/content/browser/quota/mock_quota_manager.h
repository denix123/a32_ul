// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_QUOTA_MOCK_QUOTA_MANAGER_H_
#define CONTENT_BROWSER_QUOTA_MOCK_QUOTA_MANAGER_H_

#include <map>
#include <set>
#include <utility>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "storage/browser/quota/quota_client.h"
#include "storage/browser/quota/quota_manager.h"
#include "storage/browser/quota/quota_task.h"
#include "storage/common/quota/quota_types.h"
#include "url/gurl.h"

using storage::GetOriginsCallback;
using storage::QuotaClient;
using storage::QuotaManager;
using storage::QuotaStatusCode;
using storage::SpecialStoragePolicy;
using storage::StatusCallback;
using storage::StorageType;

namespace content {

class MockQuotaManager : public QuotaManager {
 public:
  MockQuotaManager(
      bool is_incognito,
      const base::FilePath& profile_path,
      const scoped_refptr<base::SingleThreadTaskRunner>& io_thread,
      const scoped_refptr<base::SequencedTaskRunner>& db_thread,
      const scoped_refptr<SpecialStoragePolicy>& special_storage_policy);

  
  
  
  
  virtual void GetUsageAndQuota(
      const GURL& origin,
      storage::StorageType type,
      const GetUsageAndQuotaCallback& callback) OVERRIDE;

  
  
  
  virtual void GetOriginsModifiedSince(
      StorageType type,
      base::Time modified_since,
      const GetOriginsCallback& callback) OVERRIDE;

  
  
  
  
  
  
  virtual void DeleteOriginData(const GURL& origin,
                                StorageType type,
                                int quota_client_mask,
                                const StatusCallback& callback) OVERRIDE;

  
  void SetQuota(const GURL& origin, StorageType type, int64 quota);

  
  
  
  
  
  bool AddOrigin(const GURL& origin,
                 StorageType type,
                 int quota_client_mask,
                 base::Time modified);

  
  
  
  
  bool OriginHasData(const GURL& origin,
                     StorageType type,
                     QuotaClient::ID quota_client) const;

 protected:
  virtual ~MockQuotaManager();

 private:
  friend class MockQuotaManagerProxy;

  
  
  
  struct OriginInfo {
    OriginInfo(const GURL& origin,
               StorageType type,
               int quota_client_mask,
               base::Time modified);
    ~OriginInfo();

    GURL origin;
    StorageType type;
    int quota_client_mask;
    base::Time modified;
  };

  
  
  
  
  struct StorageInfo {
    StorageInfo();
    ~StorageInfo();
    int64 usage;
    int64 quota;
  };

  typedef std::pair<GURL, StorageType> OriginAndType;
  typedef std::map<OriginAndType, StorageInfo> UsageAndQuotaMap;

  
  void UpdateUsage(const GURL& origin, StorageType type, int64 delta);
  void DidGetModifiedSince(const GetOriginsCallback& callback,
                           std::set<GURL>* origins,
                           StorageType storage_type);
  void DidDeleteOriginData(const StatusCallback& callback,
                           QuotaStatusCode status);

  
  std::vector<OriginInfo> origins_;
  UsageAndQuotaMap usage_and_quota_map_;
  base::WeakPtrFactory<MockQuotaManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MockQuotaManager);
};

}  

#endif  

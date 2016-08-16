// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_QUOTA_MOCK_QUOTA_MANAGER_PROXY_H_
#define CONTENT_BROWSER_QUOTA_MOCK_QUOTA_MANAGER_PROXY_H_

#include "content/browser/quota/mock_quota_manager.h"
#include "storage/browser/quota/quota_client.h"
#include "storage/browser/quota/quota_manager_proxy.h"
#include "storage/common/quota/quota_types.h"
#include "url/gurl.h"

using storage::QuotaManagerProxy;

namespace content {

class MockQuotaManager;

class MockQuotaManagerProxy : public QuotaManagerProxy {
 public:
  
  MockQuotaManagerProxy(MockQuotaManager* quota_manager,
                        base::SingleThreadTaskRunner* task_runner);

  virtual void RegisterClient(QuotaClient* client) OVERRIDE;

  void SimulateQuotaManagerDestroyed();

  
  virtual void NotifyOriginInUse(const GURL& origin) OVERRIDE {}
  virtual void NotifyOriginNoLongerInUse(const GURL& origin) OVERRIDE {}
  virtual void SetUsageCacheEnabled(QuotaClient::ID client_id,
                                    const GURL& origin,
                                    StorageType type,
                                    bool enabled) OVERRIDE {}
  virtual void GetUsageAndQuota(
      base::SequencedTaskRunner* original_task_runner,
      const GURL& origin,
      StorageType type,
      const QuotaManager::GetUsageAndQuotaCallback& callback) OVERRIDE {}

  
  
  
  
  virtual void NotifyStorageAccessed(QuotaClient::ID client_id,
                                     const GURL& origin,
                                     StorageType type) OVERRIDE;

  
  
  
  
  virtual void NotifyStorageModified(QuotaClient::ID client_id,
                                     const GURL& origin,
                                     StorageType type,
                                     int64 delta) OVERRIDE;

  int notify_storage_accessed_count() const { return storage_accessed_count_; }
  int notify_storage_modified_count() const { return storage_modified_count_; }
  GURL last_notified_origin() const { return last_notified_origin_; }
  StorageType last_notified_type() const { return last_notified_type_; }
  int64 last_notified_delta() const { return last_notified_delta_; }

 protected:
  virtual ~MockQuotaManagerProxy();

 private:
  MockQuotaManager* mock_manager() const {
    return static_cast<MockQuotaManager*>(quota_manager());
  }

  int storage_accessed_count_;
  int storage_modified_count_;
  GURL last_notified_origin_;
  StorageType last_notified_type_;
  int64 last_notified_delta_;

  QuotaClient* registered_client_;

  DISALLOW_COPY_AND_ASSIGN(MockQuotaManagerProxy);
};

}  

#endif  

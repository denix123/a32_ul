// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_CALLBACKS_H_
#define CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_CALLBACKS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "content/browser/indexed_db/indexed_db_database_error.h"
#include "content/browser/indexed_db/indexed_db_dispatcher_host.h"
#include "content/common/indexed_db/indexed_db_key.h"
#include "content/common/indexed_db/indexed_db_key_path.h"
#include "url/gurl.h"

namespace content {
class IndexedDBBlobInfo;
class IndexedDBConnection;
class IndexedDBCursor;
class IndexedDBDatabase;
class IndexedDBDatabaseCallbacks;
struct IndexedDBDatabaseMetadata;
struct IndexedDBValue;

class CONTENT_EXPORT IndexedDBCallbacks
    : public base::RefCounted<IndexedDBCallbacks> {
 public:
  
  IndexedDBCallbacks(IndexedDBDispatcherHost* dispatcher_host,
                     int32 ipc_thread_id,
                     int32 ipc_callbacks_id);

  
  IndexedDBCallbacks(IndexedDBDispatcherHost* dispatcher_host,
                     int32 ipc_thread_id,
                     int32 ipc_callbacks_id,
                     int32 ipc_cursor_id);

  
  IndexedDBCallbacks(IndexedDBDispatcherHost* dispatcher_host,
                     int32 ipc_thread_id,
                     int32 ipc_callbacks_id,
                     int32 ipc_database_callbacks_id,
                     int64 host_transaction_id,
                     const GURL& origin_url);

  virtual void OnError(const IndexedDBDatabaseError& error);

  
  virtual void OnSuccess(const std::vector<base::string16>& string);

  
  virtual void OnBlocked(int64 existing_version);

  
  virtual void OnDataLoss(blink::WebIDBDataLoss data_loss,
                          std::string data_loss_message);
  virtual void OnUpgradeNeeded(
      int64 old_version,
      scoped_ptr<IndexedDBConnection> connection,
      const content::IndexedDBDatabaseMetadata& metadata);
  virtual void OnSuccess(scoped_ptr<IndexedDBConnection> connection,
                         const content::IndexedDBDatabaseMetadata& metadata);

  
  virtual void OnSuccess(scoped_refptr<IndexedDBCursor> cursor,
                         const IndexedDBKey& key,
                         const IndexedDBKey& primary_key,
                         IndexedDBValue* value);

  
  virtual void OnSuccess(const IndexedDBKey& key,
                         const IndexedDBKey& primary_key,
                         IndexedDBValue* value);

  
  virtual void OnSuccessWithPrefetch(
      const std::vector<IndexedDBKey>& keys,
      const std::vector<IndexedDBKey>& primary_keys,
      std::vector<IndexedDBValue>* values);

  
  virtual void OnSuccess(IndexedDBValue* value,
                         const IndexedDBKey& key,
                         const IndexedDBKeyPath& key_path);

  
  virtual void OnSuccess(IndexedDBValue* value);

  
  virtual void OnSuccess(const IndexedDBKey& key);

  
  
  virtual void OnSuccess(int64 value);

  
  
  virtual void OnSuccess();

  blink::WebIDBDataLoss data_loss() const { return data_loss_; }

  void SetConnectionOpenStartTime(const base::TimeTicks& start_time);

 protected:
  virtual ~IndexedDBCallbacks();

 private:
  void RegisterBlobsAndSend(const std::vector<IndexedDBBlobInfo>& blob_info,
                            const base::Closure& callback);

  friend class base::RefCounted<IndexedDBCallbacks>;

  
  scoped_refptr<IndexedDBDispatcherHost> dispatcher_host_;
  int32 ipc_callbacks_id_;
  int32 ipc_thread_id_;

  
  int32 ipc_cursor_id_;

  
  int64 host_transaction_id_;
  GURL origin_url_;
  int32 ipc_database_id_;
  int32 ipc_database_callbacks_id_;

  
  blink::WebIDBDataLoss data_loss_;
  std::string data_loss_message_;

  
  bool sent_blocked_;
  base::TimeTicks connection_open_start_time_;
  DISALLOW_COPY_AND_ASSIGN(IndexedDBCallbacks);
};

}  

#endif  

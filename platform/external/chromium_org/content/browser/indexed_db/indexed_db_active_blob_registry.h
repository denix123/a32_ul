// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_ACTIVE_BLOB_REGISTRY_H_
#define CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_ACTIVE_BLOB_REGISTRY_H_

#include <map>
#include <set>
#include <utility>
#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "content/common/content_export.h"
#include "storage/common/blob/shareable_file_reference.h"

namespace content {

class IndexedDBBackingStore;

class CONTENT_EXPORT IndexedDBActiveBlobRegistry {
 public:
  explicit IndexedDBActiveBlobRegistry(IndexedDBBackingStore* backing_store);
  ~IndexedDBActiveBlobRegistry();

  
  
  
  

  
  bool MarkDeletedCheckIfUsed(int64 database_id, int64 blob_key);

  storage::ShareableFileReference::FinalReleaseCallback GetFinalReleaseCallback(
      int64 database_id,
      int64 blob_key);
  
  
  base::Closure GetAddBlobRefCallback(int64 database_id, int64 blob_key);
  
  
  
  void ForceShutdown();

 private:
  
  
  typedef std::map<int64, bool> SingleDBMap;
  
  typedef std::map<int64, SingleDBMap> AllDBsMap;
  typedef std::set<int64> DeletedDBSet;

  void AddBlobRef(int64 database_id, int64 blob_key);
  void ReleaseBlobRef(int64 database_id, int64 blob_key);
  static void ReleaseBlobRefThreadSafe(
      scoped_refptr<base::TaskRunner> task_runner,
      base::WeakPtr<IndexedDBActiveBlobRegistry> weak_ptr,
      int64 database_id,
      int64 blob_key,
      const base::FilePath& unused);

  AllDBsMap use_tracker_;
  DeletedDBSet deleted_dbs_;
  
  
  
  IndexedDBBackingStore* backing_store_;
  base::WeakPtrFactory<IndexedDBActiveBlobRegistry> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(IndexedDBActiveBlobRegistry);
};

}  

#endif  

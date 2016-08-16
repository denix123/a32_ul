// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_DISK_CACHE_BLOCKFILE_BACKEND_WORKER_V3_H_
#define NET_DISK_CACHE_BLOCKFILE_BACKEND_WORKER_V3_H_

#include "base/containers/hash_tables.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "net/disk_cache/blockfile/addr.h"
#include "net/disk_cache/blockfile/backend_impl_v3.h"
#include "net/disk_cache/blockfile/block_files.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace disk_cache {

class BackendImplV3::Worker : public base::RefCountedThreadSafe<Worker> {
 public:
  Worker(const base::FilePath& path,
         const scoped_refptr<base::SingleThreadTaskRunner>& main_thread);

  
  int Init(const CompletionCallback& callback);

 private:
  friend class base::RefCountedThreadSafe<Worker>;

  ~Worker();
  void CleanupCache();

  
  base::FilePath GetFileName(Addr address) const;

  
  bool CreateBackingStore(disk_cache::File* file);
  bool InitBackingStore(bool* file_created);

  
  bool CheckIndex();

  base::FilePath path_;  
  BlockFiles block_files_;  
  bool init_;  

  DISALLOW_COPY_AND_ASSIGN(Worker);
};

}  

#endif  

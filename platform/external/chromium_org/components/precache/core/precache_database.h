// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PRECACHE_CORE_PRECACHE_DATABASE_H_
#define COMPONENTS_PRECACHE_CORE_PRECACHE_DATABASE_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "components/precache/core/precache_url_table.h"

class GURL;

namespace base {
class FilePath;
class Time;
}

namespace sql {
class Connection;
}

namespace precache {

class PrecacheDatabase : public base::RefCountedThreadSafe<PrecacheDatabase> {
 public:
  
  PrecacheDatabase();

  
  
  bool Init(const base::FilePath& db_path);

  
  
  void DeleteExpiredPrecacheHistory(const base::Time& current_time);

  
  
  void RecordURLPrecached(const GURL& url, const base::Time& fetch_time,
                          int64 size, bool was_cached);

  
  
  
  void RecordURLFetched(const GURL& url, const base::Time& fetch_time,
                        int64 size, bool was_cached,
                        bool is_connection_cellular);

 private:
  friend class base::RefCountedThreadSafe<PrecacheDatabase>;
  friend class PrecacheDatabaseTest;

  ~PrecacheDatabase();

  bool IsDatabaseAccessible() const;

  
  
  
  void Flush();

  
  
  void PostedFlush();

  
  
  
  void MaybePostFlush();

  scoped_ptr<sql::Connection> db_;

  
  
  
  PrecacheURLTable precache_url_table_;

  
  std::vector<base::Closure> buffered_writes_;

  
  
  base::hash_set<std::string> buffered_urls_;

  
  
  bool is_flush_posted_;

  
  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(PrecacheDatabase);
};

}  

#endif  

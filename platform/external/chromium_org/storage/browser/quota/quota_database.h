// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_QUOTA_QUOTA_DATABASE_H_
#define STORAGE_BROWSER_QUOTA_QUOTA_DATABASE_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/quota/quota_types.h"
#include "url/gurl.h"

namespace content {
class QuotaDatabaseTest;
}

namespace sql {
class Connection;
class MetaTable;
}

class GURL;

namespace storage {

class SpecialStoragePolicy;

class STORAGE_EXPORT_PRIVATE QuotaDatabase {
 public:
  
  static const char kDesiredAvailableSpaceKey[];
  static const char kTemporaryQuotaOverrideKey[];

  
  explicit QuotaDatabase(const base::FilePath& path);
  ~QuotaDatabase();

  void CloseConnection();

  bool GetHostQuota(const std::string& host, StorageType type, int64* quota);
  bool SetHostQuota(const std::string& host, StorageType type, int64 quota);
  bool DeleteHostQuota(const std::string& host, StorageType type);

  bool SetOriginLastAccessTime(const GURL& origin,
                               StorageType type,
                               base::Time last_access_time);

  bool SetOriginLastModifiedTime(const GURL& origin,
                                 StorageType type,
                                 base::Time last_modified_time);

  
  
  
  bool RegisterInitialOriginInfo(
      const std::set<GURL>& origins, StorageType type);

  bool DeleteOriginInfo(const GURL& origin, StorageType type);

  bool GetQuotaConfigValue(const char* key, int64* value);
  bool SetQuotaConfigValue(const char* key, int64 value);

  
  
  
  
  bool GetLRUOrigin(StorageType type,
                    const std::set<GURL>& exceptions,
                    SpecialStoragePolicy* special_storage_policy,
                    GURL* origin);

  
  
  bool GetOriginsModifiedSince(StorageType type,
                               std::set<GURL>* origins,
                               base::Time modified_since);

  
  
  
  bool IsOriginDatabaseBootstrapped();
  bool SetOriginDatabaseBootstrapped(bool bootstrap_flag);

 private:
  struct STORAGE_EXPORT_PRIVATE QuotaTableEntry {
    QuotaTableEntry();
    QuotaTableEntry(
        const std::string& host,
        StorageType type,
        int64 quota);
    std::string host;
    StorageType type;
    int64 quota;
  };
  friend STORAGE_EXPORT_PRIVATE bool operator <(
      const QuotaTableEntry& lhs, const QuotaTableEntry& rhs);

  struct STORAGE_EXPORT_PRIVATE OriginInfoTableEntry {
    OriginInfoTableEntry();
    OriginInfoTableEntry(
        const GURL& origin,
        StorageType type,
        int used_count,
        const base::Time& last_access_time,
        const base::Time& last_modified_time);
    GURL origin;
    StorageType type;
    int used_count;
    base::Time last_access_time;
    base::Time last_modified_time;
  };
  friend STORAGE_EXPORT_PRIVATE bool operator <(
      const OriginInfoTableEntry& lhs, const OriginInfoTableEntry& rhs);

  
  struct TableSchema {
    const char* table_name;
    const char* columns;
  };
  struct IndexSchema {
    const char* index_name;
    const char* table_name;
    const char* columns;
    bool unique;
  };

  typedef base::Callback<bool (const QuotaTableEntry&)> QuotaTableCallback;
  typedef base::Callback<bool (const OriginInfoTableEntry&)>
      OriginInfoTableCallback;

  struct QuotaTableImporter;

  
  
  
  
  void Commit();
  void ScheduleCommit();

  bool FindOriginUsedCount(const GURL& origin,
                           StorageType type,
                           int* used_count);

  bool LazyOpen(bool create_if_needed);
  bool EnsureDatabaseVersion();
  bool ResetSchema();
  bool UpgradeSchema(int current_version);

  static bool CreateSchema(
      sql::Connection* database,
      sql::MetaTable* meta_table,
      int schema_version, int compatible_version,
      const TableSchema* tables, size_t tables_size,
      const IndexSchema* indexes, size_t indexes_size);

  
  bool DumpQuotaTable(const QuotaTableCallback& callback);
  bool DumpOriginInfoTable(const OriginInfoTableCallback& callback);

  base::FilePath db_file_path_;

  scoped_ptr<sql::Connection> db_;
  scoped_ptr<sql::MetaTable> meta_table_;
  bool is_recreating_;
  bool is_disabled_;

  base::OneShotTimer<QuotaDatabase> timer_;

  friend class content::QuotaDatabaseTest;
  friend class QuotaManager;

  static const TableSchema kTables[];
  static const IndexSchema kIndexes[];

  DISALLOW_COPY_AND_ASSIGN(QuotaDatabase);
};

}  

#endif  

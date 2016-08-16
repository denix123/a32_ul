// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_KEYWORD_TABLE_H_
#define COMPONENTS_SEARCH_ENGINES_KEYWORD_TABLE_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "components/search_engines/template_url_id.h"
#include "components/webdata/common/web_database_table.h"

struct TemplateURLData;
class WebDatabase;

namespace sql {
class Statement;
}  

class KeywordTable : public WebDatabaseTable {
 public:
  enum OperationType {
    ADD,
    REMOVE,
    UPDATE,
  };

  typedef std::pair<OperationType, TemplateURLData> Operation;
  typedef std::vector<Operation> Operations;
  typedef std::vector<TemplateURLData> Keywords;

  

  static const char kDefaultSearchProviderKey[];

  KeywordTable();
  virtual ~KeywordTable();

  
  static KeywordTable* FromWebDatabase(WebDatabase* db);

  virtual WebDatabaseTable::TypeKey GetTypeKey() const OVERRIDE;
  virtual bool CreateTablesIfNecessary() OVERRIDE;
  virtual bool IsSyncable() OVERRIDE;
  virtual bool MigrateToVersion(int version,
                                bool* update_compatible_version) OVERRIDE;

  
  
  
  
  bool PerformOperations(const Operations& operations);

  
  
  
  bool GetKeywords(Keywords* keywords);

  
  bool SetDefaultSearchProviderID(int64 id);
  int64 GetDefaultSearchProviderID();

  
  bool SetBuiltinKeywordVersion(int version);
  int GetBuiltinKeywordVersion();

  
  
  static std::string GetKeywordColumns();

  
  bool MigrateToVersion21AutoGenerateKeywordColumn();
  bool MigrateToVersion25AddLogoIDColumn();
  bool MigrateToVersion26AddCreatedByPolicyColumn();
  bool MigrateToVersion28SupportsInstantColumn();
  bool MigrateToVersion29InstantURLToSupportsInstant();
  bool MigrateToVersion38AddLastModifiedColumn();
  bool MigrateToVersion39AddSyncGUIDColumn();
  bool MigrateToVersion44AddDefaultSearchProviderBackup();
  bool MigrateToVersion45RemoveLogoIDAndAutogenerateColumns();
  bool MigrateToVersion47AddAlternateURLsColumn();
  bool MigrateToVersion48RemoveKeywordsBackup();
  bool MigrateToVersion49AddSearchTermsReplacementKeyColumn();
  bool MigrateToVersion52AddImageSearchAndPOSTSupport();
  bool MigrateToVersion53AddNewTabURLColumn();

 private:
  friend class KeywordTableTest;
  FRIEND_TEST_ALL_PREFIXES(WebDatabaseMigrationTest, MigrateVersion44ToCurrent);

  
  
  

  
  
  
  static bool GetKeywordDataFromStatement(const sql::Statement& s,
                                          TemplateURLData* data);

  
  
  bool AddKeyword(const TemplateURLData& data);

  
  
  bool RemoveKeyword(TemplateURLID id);

  
  
  bool UpdateKeyword(const TemplateURLData& data);

  
  
  
  bool GetKeywordAsString(TemplateURLID id,
                          const std::string& table_name,
                          std::string* result);

  
  
  bool MigrateKeywordsTableForVersion45(const std::string& name);

  DISALLOW_COPY_AND_ASSIGN(KeywordTable);
};

#endif  

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_SHORTCUTS_DATABASE_H_
#define CHROME_BROWSER_HISTORY_SHORTCUTS_DATABASE_H_

#include <map>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "sql/connection.h"
#include "sql/meta_table.h"
#include "url/gurl.h"

namespace history {

class ShortcutsDatabase : public base::RefCountedThreadSafe<ShortcutsDatabase> {
 public:
  
  struct Shortcut {
    
    struct MatchCore {
      MatchCore(const base::string16& fill_into_edit,
                const GURL& destination_url,
                const base::string16& contents,
                const std::string& contents_class,
                const base::string16& description,
                const std::string& description_class,
                int transition,
                int type,
                const base::string16& keyword);
      ~MatchCore();

      base::string16 fill_into_edit;
      GURL destination_url;
      base::string16 contents;
      
      
      
      std::string contents_class;
      base::string16 description;
      std::string description_class;
      int transition;
      int type;
      base::string16 keyword;
    };

    Shortcut(const std::string& id,
             const base::string16& text,
             const MatchCore& match_core,
             const base::Time& last_access_time,
             int number_of_hits);
    
    Shortcut();
    ~Shortcut();

    std::string id;  
    base::string16 text;   
    MatchCore match_core;
    base::Time last_access_time;  
    int number_of_hits;           
  };

  typedef std::vector<std::string> ShortcutIDs;
  typedef std::map<std::string, Shortcut> GuidToShortcutMap;

  explicit ShortcutsDatabase(const base::FilePath& database_path);

  bool Init();

  
  bool AddShortcut(const Shortcut& shortcut);

  
  bool UpdateShortcut(const Shortcut& shortcut);

  
  bool DeleteShortcutsWithIDs(const ShortcutIDs& shortcut_ids);

  
  bool DeleteShortcutsWithURL(const std::string& shortcut_url_spec);

  
  bool DeleteAllShortcuts();

  
  void LoadShortcuts(GuidToShortcutMap* shortcuts);

 private:
  friend class base::RefCountedThreadSafe<ShortcutsDatabase>;
  friend class ShortcutsDatabaseTest;
  FRIEND_TEST_ALL_PREFIXES(ShortcutsDatabaseTest, AddShortcut);
  FRIEND_TEST_ALL_PREFIXES(ShortcutsDatabaseTest, UpdateShortcut);
  FRIEND_TEST_ALL_PREFIXES(ShortcutsDatabaseTest, DeleteShortcutsWithIds);
  FRIEND_TEST_ALL_PREFIXES(ShortcutsDatabaseTest, DeleteShortcutsWithURL);
  FRIEND_TEST_ALL_PREFIXES(ShortcutsDatabaseTest, LoadShortcuts);

  virtual ~ShortcutsDatabase();

  
  bool EnsureTable();

  
  sql::Connection db_;
  base::FilePath database_path_;

  sql::MetaTable meta_table_;

  static const base::FilePath::CharType kShortcutsDatabaseName[];

  DISALLOW_COPY_AND_ASSIGN(ShortcutsDatabase);
};

}  

#endif  

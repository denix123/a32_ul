// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_VALUE_STORE_LEVELDB_VALUE_STORE_H_
#define EXTENSIONS_BROWSER_VALUE_STORE_LEVELDB_VALUE_STORE_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/browser/value_store/value_store.h"
#include "third_party/leveldatabase/src/include/leveldb/db.h"

class LeveldbValueStore : public ValueStore {
 public:
  
  
  
  
  
  
  explicit LeveldbValueStore(const base::FilePath& path);

  
  virtual ~LeveldbValueStore();

  
  virtual size_t GetBytesInUse(const std::string& key) OVERRIDE;
  virtual size_t GetBytesInUse(const std::vector<std::string>& keys) OVERRIDE;
  virtual size_t GetBytesInUse() OVERRIDE;
  virtual ReadResult Get(const std::string& key) OVERRIDE;
  virtual ReadResult Get(const std::vector<std::string>& keys) OVERRIDE;
  virtual ReadResult Get() OVERRIDE;
  virtual WriteResult Set(
      WriteOptions options,
      const std::string& key,
      const base::Value& value) OVERRIDE;
  virtual WriteResult Set(
      WriteOptions options, const base::DictionaryValue& values) OVERRIDE;
  virtual WriteResult Remove(const std::string& key) OVERRIDE;
  virtual WriteResult Remove(const std::vector<std::string>& keys) OVERRIDE;
  virtual WriteResult Clear() OVERRIDE;
  virtual bool Restore() OVERRIDE;
  virtual bool RestoreKey(const std::string& key) OVERRIDE;

  
  
  bool WriteToDbForTest(leveldb::WriteBatch* batch);

 private:
  
  scoped_ptr<ValueStore::Error> EnsureDbIsOpen();

  
  scoped_ptr<ValueStore::Error> ReadFromDb(
      leveldb::ReadOptions options,
      const std::string& key,
      
      scoped_ptr<base::Value>* setting);

  
  
  scoped_ptr<ValueStore::Error> AddToBatch(ValueStore::WriteOptions options,
                                           const std::string& key,
                                           const base::Value& value,
                                           leveldb::WriteBatch* batch,
                                           ValueStoreChangeList* changes);

  
  scoped_ptr<ValueStore::Error> WriteToDb(leveldb::WriteBatch* batch);

  
  
  scoped_ptr<ValueStore::Error> ToValueStoreError(
      const leveldb::Status& status,
      scoped_ptr<std::string> key);

  
  
  void DeleteDbFile();

  
  bool IsEmpty();

  
  const base::FilePath db_path_;

  
  scoped_ptr<leveldb::DB> db_;

  DISALLOW_COPY_AND_ASSIGN(LeveldbValueStore);
};

#endif  

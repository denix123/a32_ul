// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_LEVELDB_WRAPPER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_LEVELDB_WRAPPER_H_

#include <map>
#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "third_party/leveldatabase/src/include/leveldb/slice.h"

namespace leveldb {
class DB;
class Iterator;
class Slice;
class Status;
class WriteBatch;
}

namespace sync_file_system {
namespace drive_backend {

class SliceComparator {
 public:
  bool operator()(const leveldb::Slice& a, const leveldb::Slice& b) const {
    return a.compare(b) < 0;
  }
};

// and also data on disk.  Those data on memory are written down on disk when
class LevelDBWrapper {
 private:
  enum Operation {
    PUT_OPERATION,
    DELETE_OPERATION,
  };
  typedef std::pair<Operation, std::string> Transaction;
  typedef std::map<std::string, Transaction, SliceComparator>
      PendingOperationMap;

 public:
  class Iterator {
   public:
    explicit Iterator(LevelDBWrapper* db);
    ~Iterator();

    bool Valid();
    void Seek(const std::string& target);
    void SeekToFirst();
    void SeekToLast();
    void Next();
    void Delete();
    leveldb::Slice key();
    leveldb::Slice value();

   private:
    
    void AdvanceIterators();

    LevelDBWrapper* db_;  
    scoped_ptr<leveldb::Iterator> db_iterator_;
    PendingOperationMap::iterator map_iterator_;

    DISALLOW_COPY_AND_ASSIGN(Iterator);
  };

  explicit LevelDBWrapper(scoped_ptr<leveldb::DB> db);
  ~LevelDBWrapper();

  
  void Put(const std::string& key, const std::string& value);
  void Delete(const std::string& key);

  
  leveldb::Status Get(const std::string& key, std::string* value);
  scoped_ptr<Iterator> NewIterator();

  
  
  leveldb::Status Commit();

  
  void Clear();

  
  
  
  int64 num_puts() { return num_puts_; }
  int64 num_deletes() { return num_deletes_; }

  
  
  
  leveldb::DB* GetLevelDB();

 private:
  scoped_ptr<leveldb::DB> db_;

  PendingOperationMap pending_;
  int64 num_puts_;
  int64 num_deletes_;

  DISALLOW_COPY_AND_ASSIGN(LevelDBWrapper);
};

}  
}  

#endif  

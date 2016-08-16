// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_LEVELDB_PROTO_LEVELDB_DATABASE_H_
#define COMPONENTS_LEVELDB_PROTO_LEVELDB_DATABASE_H_

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_split.h"
#include "base/threading/thread_collision_warner.h"

namespace leveldb {
class DB;
}  

namespace leveldb_proto {

class LevelDB {
 public:
  LevelDB();
  virtual ~LevelDB();

  virtual bool Init(const base::FilePath& database_dir);
  virtual bool Save(const base::StringPairs& pairs_to_save,
                    const std::vector<std::string>& keys_to_remove);
  virtual bool Load(std::vector<std::string>* entries);

 private:
  DFAKE_MUTEX(thread_checker_);
  scoped_ptr<leveldb::DB> db_;
};

}  

#endif  

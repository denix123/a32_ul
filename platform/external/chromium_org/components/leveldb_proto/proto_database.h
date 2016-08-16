// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_LEVELDB_PROTO_PROTO_DATABASE_H_
#define COMPONENTS_LEVELDB_PROTO_PROTO_DATABASE_H_

#include <string>
#include <utility>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"

namespace leveldb_proto {

template <typename T>
class ProtoDatabase {
 public:
  typedef base::Callback<void(bool success)> InitCallback;
  typedef base::Callback<void(bool success)> UpdateCallback;
  typedef base::Callback<void(bool success, scoped_ptr<std::vector<T> >)>
      LoadCallback;
  
  typedef std::vector<std::pair<std::string, T> > KeyEntryVector;

  virtual ~ProtoDatabase() {}

  
  
  virtual void Init(const base::FilePath& database_dir,
                    InitCallback callback) = 0;

  
  
  
  virtual void UpdateEntries(
      scoped_ptr<KeyEntryVector> entries_to_save,
      scoped_ptr<std::vector<std::string> > keys_to_remove,
      UpdateCallback callback) = 0;

  
  
  virtual void LoadEntries(LoadCallback callback) = 0;
};

}  

#endif  

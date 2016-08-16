// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_COMMON_BLOB_SCOPED_FILE_H_
#define STORAGE_COMMON_BLOB_SCOPED_FILE_H_

#include <map>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/move.h"
#include "storage/common/storage_common_export.h"

namespace base {
class TaskRunner;
}

namespace storage {

class STORAGE_COMMON_EXPORT ScopedFile {
  
  
  
  MOVE_ONLY_TYPE_FOR_CPP_03(ScopedFile, RValue)

 public:
  typedef base::Callback<void(const base::FilePath&)> ScopeOutCallback;
  typedef std::pair<ScopeOutCallback, scoped_refptr<base::TaskRunner> >
      ScopeOutCallbackPair;
  typedef std::vector<ScopeOutCallbackPair> ScopeOutCallbackList;

  enum ScopeOutPolicy {
    DELETE_ON_SCOPE_OUT,
    DONT_DELETE_ON_SCOPE_OUT,
  };

  ScopedFile();

  
  
  ScopedFile(const base::FilePath& path,
             ScopeOutPolicy policy,
             const scoped_refptr<base::TaskRunner>& file_task_runner);

  
  
  ScopedFile(RValue other);
  ScopedFile& operator=(RValue rhs) {
    MoveFrom(*rhs.object);
    return *this;
  }

  ~ScopedFile();

  
  
  
  
  void AddScopeOutCallback(const ScopeOutCallback& callback,
                           base::TaskRunner* callback_runner);

  
  const base::FilePath& path() const { return path_; }

  
  
  
  
  base::FilePath Release();

  void Reset();

 private:
  
  void MoveFrom(ScopedFile& other);

  base::FilePath path_;
  ScopeOutPolicy scope_out_policy_;
  scoped_refptr<base::TaskRunner> file_task_runner_;
  ScopeOutCallbackList scope_out_callbacks_;
};

}  

#endif  

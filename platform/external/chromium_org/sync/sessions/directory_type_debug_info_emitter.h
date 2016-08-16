// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_SESSIONS_DIRECTORY_TYPE_DEBUG_INFO_EMITTER_H_
#define SYNC_SESSIONS_DIRECTORY_TYPE_DEBUG_INFO_EMITTER_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/values.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/sessions/commit_counters.h"
#include "sync/internal_api/public/sessions/update_counters.h"
#include "sync/syncable/directory.h"

namespace syncer {

class DirectoryCommitContributor;
class TypeDebugInfoObserver;

class SYNC_EXPORT_PRIVATE DirectoryTypeDebugInfoEmitter {
 public:
  
  
  
  
  
  DirectoryTypeDebugInfoEmitter(
      syncable::Directory* directory,
      syncer::ModelType type,
      ObserverList<TypeDebugInfoObserver>* observers);

  
  DirectoryTypeDebugInfoEmitter(
      ModelType type,
      ObserverList<TypeDebugInfoObserver>* observers);

  virtual ~DirectoryTypeDebugInfoEmitter();

  
  scoped_ptr<base::ListValue> GetAllNodes();

  
  const CommitCounters& GetCommitCounters() const;

  
  CommitCounters* GetMutableCommitCounters();

  
  void EmitCommitCountersUpdate();

  
  const UpdateCounters& GetUpdateCounters() const;

  
  UpdateCounters* GetMutableUpdateCounters();

  
  void EmitUpdateCountersUpdate();

  
  void EmitStatusCountersUpdate();

 private:
  syncable::Directory* directory_;

  const ModelType type_;

  CommitCounters commit_counters_;
  UpdateCounters update_counters_;

  
  
  
  
  ObserverList<TypeDebugInfoObserver>* type_debug_info_observers_;

  DISALLOW_COPY_AND_ASSIGN(DirectoryTypeDebugInfoEmitter);
};

}  

#endif  

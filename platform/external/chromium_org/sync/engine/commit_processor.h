// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_COMMIT_PROCESSOR_H_
#define SYNC_ENGINE_COMMIT_PROCESSOR_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/engine/model_safe_worker.h"
#include "sync/sessions/model_type_registry.h"

namespace syncer {

namespace syncable {
class Directory;
}  

class CommitContributor;
class CommitContribution;

class SYNC_EXPORT_PRIVATE CommitProcessor {
 public:
  typedef std::map<ModelType, CommitContribution*> ContributionMap;

  
  
  explicit CommitProcessor(CommitContributorMap* commit_contributor_map);
  ~CommitProcessor();

  
  
  
  
  
  
  void GatherCommitContributions(
      ModelTypeSet commit_types,
      size_t max_entries,
      ContributionMap* contributions);

 private:
  
  CommitContributorMap* commit_contributor_map_;

  DISALLOW_COPY_AND_ASSIGN(CommitProcessor);
};

}  

#endif  

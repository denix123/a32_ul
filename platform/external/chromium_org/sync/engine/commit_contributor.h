// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_COMMIT_CONTRIBUTOR_H_
#define SYNC_ENGINE_COMMIT_CONTRIBUTOR_H_

#include <cstddef>

#include "base/memory/scoped_ptr.h"
#include "sync/base/sync_export.h"

namespace syncer {

class CommitContribution;

namespace syncable {
class Directory;
}

class SYNC_EXPORT_PRIVATE CommitContributor {
 public:
  CommitContributor();
  virtual ~CommitContributor() = 0;

  
  
  
  virtual scoped_ptr<CommitContribution> GetContribution(
      size_t max_entries) = 0;
};

}  

#endif  

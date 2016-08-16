// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_MOCK_INVALIDATION_TRACKER_H_
#define SYNC_TEST_MOCK_INVALIDATION_TRACKER_H_

#include <set>

#include "base/memory/scoped_ptr.h"
#include "sync/test/trackable_mock_invalidation.h"

namespace syncer {

class MockInvalidationTracker {
 public:
  
  
  scoped_ptr<TrackableMockInvalidation> IssueUnknownVersionInvalidation();
  scoped_ptr<TrackableMockInvalidation> IssueInvalidation(
      int64 version,
      const std::string& payload);

  MockInvalidationTracker();
  ~MockInvalidationTracker();

  
  
  void Acknowledge(int invaliation_id);

  
  void Drop(int invalidation_id);

  
  
  bool IsUnacked(int invalidation_id) const;

  
  
  bool IsAcknowledged(int invalidation_id) const;

  
  bool IsDropped(int invalidation_id) const;

  
  bool AllInvalidationsAccountedFor() const;

 private:
  
  
  int next_id_;

  
  
  
  
  std::set<int> dropped_;
  std::set<int> acknowledged_;
};

}  

#endif  

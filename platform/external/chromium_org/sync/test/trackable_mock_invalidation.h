// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_TRACKABLE_MOCK_INVALIDATION_H_
#define SYNC_TEST_TRACKABLE_MOCK_INVALIDATION_H_

#include "sync/test/mock_invalidation.h"

namespace syncer {

class MockInvalidationTracker;

class TrackableMockInvalidation : public MockInvalidation {
 public:
  TrackableMockInvalidation(bool is_unknown_version,
                            int64 version,
                            const std::string& payload,
                            MockInvalidationTracker* tracker,
                            int tracking_id);
  virtual ~TrackableMockInvalidation();

  
  
  virtual void Acknowledge() OVERRIDE;

  
  virtual void Drop() OVERRIDE;

  
  int GetTrackingId();

 private:
  
  
  
  MockInvalidationTracker* tracker_;

  
  
  
  
  
  
  int tracking_id_;
};

}  

#endif  

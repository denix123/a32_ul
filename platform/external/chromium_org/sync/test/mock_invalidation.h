// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_MOCK_INVALIDATION_H_
#define SYNC_TEST_MOCK_INVALIDATION_H_

#include "base/memory/scoped_ptr.h"
#include "sync/internal_api/public/base/invalidation_interface.h"

namespace syncer {

class MockInvalidation : public InvalidationInterface {
 public:
  
  static scoped_ptr<MockInvalidation> BuildUnknownVersion();
  static scoped_ptr<MockInvalidation> Build(int64 version,
                                            const std::string& payload);

  virtual ~MockInvalidation();

  
  virtual bool IsUnknownVersion() const OVERRIDE;
  virtual const std::string& GetPayload() const OVERRIDE;
  virtual int64 GetVersion() const OVERRIDE;
  virtual void Acknowledge() OVERRIDE;
  virtual void Drop() OVERRIDE;

 protected:
  MockInvalidation(bool is_unknown_version,
                   int64 version,
                   const std::string& payload);

  
  const bool is_unknown_version_;

  
  const int64 version_;

  
  const std::string payload_;
};

}  

#endif  

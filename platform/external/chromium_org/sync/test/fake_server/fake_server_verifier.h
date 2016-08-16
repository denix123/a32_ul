// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_FAKE_SERVER_FAKE_SERVER_VERIFIER_H_
#define SYNC_TEST_FAKE_SERVER_FAKE_SERVER_VERIFIER_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "sync/internal_api/public/base/model_type.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace fake_server {

class FakeServer;

class FakeServerVerifier {
 public:
  
  
  explicit FakeServerVerifier(FakeServer* fake_server);
  virtual ~FakeServerVerifier();

  
  
  
  testing::AssertionResult VerifyEntityCountByType(
      size_t expected_count,
      syncer::ModelType model_type) const;

  
  
  
  testing::AssertionResult VerifyEntityCountByTypeAndName(
      size_t expected_count,
      syncer::ModelType model_type,
      const std::string& name) const;

 private:
  FakeServer* const fake_server_;

  DISALLOW_COPY_AND_ASSIGN(FakeServerVerifier);
};

}  

#endif  

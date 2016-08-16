// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_CONTENT_TEST_SUITE_BASE_H_
#define CONTENT_PUBLIC_TEST_CONTENT_TEST_SUITE_BASE_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/test/test_suite.h"

namespace content {
class ContentClient;

class ContentTestSuiteBase : public base::TestSuite {
 protected:
  ContentTestSuiteBase(int argc, char** argv);

  virtual void Initialize() OVERRIDE;

  

  
  
  static void RegisterContentSchemes(ContentClient* content_client);

  
  void RegisterInProcessThreads();

 private:
  DISALLOW_COPY_AND_ASSIGN(ContentTestSuiteBase);
};

} 

#endif  

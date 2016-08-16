// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_SHELL_TEST_SHELL_API_TEST_H_
#define EXTENSIONS_SHELL_TEST_SHELL_API_TEST_H_

#include <string>

#include "extensions/shell/test/shell_test.h"

namespace extensions {

class ShellApiTest : public AppShellTest {
 public:
  ShellApiTest();
  virtual ~ShellApiTest();

  
  
  
  
  bool RunAppTest(const std::string& app_dir);

 protected:
  
  std::string message_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ShellApiTest);
};

}  

#endif  

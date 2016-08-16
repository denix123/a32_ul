// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_CHROMEDRIVER_COMMAND_LISTENER_H_
#define CHROME_TEST_CHROMEDRIVER_COMMAND_LISTENER_H_

#include <string>

class Status;

class CommandListener {
 public:
  virtual ~CommandListener() {}

  
  
  
  virtual Status BeforeCommand(const std::string& command_name) = 0;
};

#endif  

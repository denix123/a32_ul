// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSER_PROCESS_PLATFORM_PART_BASE_H_
#define CHROME_BROWSER_BROWSER_PROCESS_PLATFORM_PART_BASE_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace base {
class CommandLine;
}

namespace policy {
class BrowserPolicyConnector;
}

class BrowserProcessPlatformPartBase {
 public:
  BrowserProcessPlatformPartBase();
  virtual ~BrowserProcessPlatformPartBase();

  
  
  virtual void PlatformSpecificCommandLineProcessing(
      const base::CommandLine& command_line);

  
  virtual void StartTearDown();

  
  virtual void AttemptExit();

  
  virtual void PreMainMessageLoopRun();

#if defined(ENABLE_CONFIGURATION_POLICY)
  virtual scoped_ptr<policy::BrowserPolicyConnector>
      CreateBrowserPolicyConnector();
#endif

 private:
  DISALLOW_COPY_AND_ASSIGN(BrowserProcessPlatformPartBase);
};

#endif  

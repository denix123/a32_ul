// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_MIXIN_BASED_BROWSER_TEST_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_MIXIN_BASED_BROWSER_TEST_H_

#include "base/memory/scoped_vector.h"
#include "chrome/test/base/in_process_browser_test.h"

namespace chromeos {

class MixinBasedBrowserTest : public InProcessBrowserTest {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  class Mixin {
   public:
    Mixin() {}
    virtual ~Mixin() {}

    
    
    
    virtual void SetUpCommandLine(base::CommandLine* command_line) {}

    
    
    virtual void SetUpInProcessBrowserTestFixture() {}

    
    
    virtual void SetUpOnMainThread() {}

    
    
    
    virtual void TearDownOnMainThread() {}

    
    
    virtual void TearDownInProcessBrowserTestFixture() {}
  };

  MixinBasedBrowserTest();
  virtual ~MixinBasedBrowserTest();

  
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
  virtual void SetUpInProcessBrowserTestFixture() OVERRIDE;
  virtual void SetUpOnMainThread() OVERRIDE;
  virtual void TearDownOnMainThread() OVERRIDE;
  virtual void TearDownInProcessBrowserTestFixture() OVERRIDE;

 protected:
  
  
  
  
  void AddMixin(Mixin* mixin);

 private:
  
  ScopedVector<Mixin> mixins_;

  
  
  bool setup_was_launched_;
};

}  

#endif  

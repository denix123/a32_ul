// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SERVICES_CREDENTIALS_H_
#define SANDBOX_LINUX_SERVICES_CREDENTIALS_H_

#include "build/build_config.h"
#if defined(OS_ANDROID)
#error "Android is not supported."
#endif  

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class SANDBOX_EXPORT Credentials {
 public:
  Credentials();
  ~Credentials();

  
  
  
  int CountOpenFds(int proc_fd);

  
  
  
  
  
  
  
  
  
  
  
  
  bool HasOpenDirectory(int proc_fd);

  
  
  bool DropAllCapabilities();
  
  
  bool HasAnyCapability() const;
  
  
  
  scoped_ptr<std::string> GetCurrentCapString() const;

  
  
  
  
  
  static bool SupportsNewUserNS();

  
  
  
  
  
  
  bool MoveToNewUserNS();

  
  
  
  
  
  
  
  
  
  bool DropFileSystemAccess();

 private:
  DISALLOW_COPY_AND_ASSIGN(Credentials);
};

}  

#endif  

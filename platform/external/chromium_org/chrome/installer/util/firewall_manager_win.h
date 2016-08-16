// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_FIREWALL_MANAGER_WIN_H_
#define CHROME_INSTALLER_UTIL_FIREWALL_MANAGER_WIN_H_

#include "base/memory/scoped_ptr.h"

class BrowserDistribution;

namespace base {
class FilePath;
}

namespace installer {

class FirewallManager {
 public:
  virtual ~FirewallManager();

  
  
  static scoped_ptr<FirewallManager> Create(BrowserDistribution* dist,
                                            const base::FilePath& chrome_path);

  
  
  
  virtual bool CanUseLocalPorts() = 0;

  
  
  virtual bool AddFirewallRules() = 0;

  
  virtual void RemoveFirewallRules() = 0;

 protected:
  FirewallManager();

  DISALLOW_COPY_AND_ASSIGN(FirewallManager);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_LEGACY_FIREWALL_MANAGER_WIN_H_
#define CHROME_INSTALLER_UTIL_LEGACY_FIREWALL_MANAGER_WIN_H_

#include <windows.h>
#include <netfw.h>

#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "base/win/scoped_comptr.h"

namespace installer {

class LegacyFirewallManager {
 public:
  LegacyFirewallManager();
  ~LegacyFirewallManager();

  
  
  bool Init(const base::string16& app_name, const base::FilePath& app_path);

  
  bool IsFirewallEnabled();

  
  
  bool GetAllowIncomingConnection(bool* value);

  
  bool SetAllowIncomingConnection(bool allow);

  
  void DeleteRule();

 private:
  
  
  base::win::ScopedComPtr<INetFwAuthorizedApplications>
      GetAuthorizedApplications();

  
  
  base::win::ScopedComPtr<INetFwAuthorizedApplication>
      CreateChromeAuthorization(bool allow);

  base::string16 app_name_;
  base::FilePath app_path_;
  base::win::ScopedComPtr<INetFwProfile> current_profile_;

  DISALLOW_COPY_AND_ASSIGN(LegacyFirewallManager);
};

}  

#endif  

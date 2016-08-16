// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_ADVANCED_FIREWALL_MANAGER_WIN_H_
#define CHROME_INSTALLER_UTIL_ADVANCED_FIREWALL_MANAGER_WIN_H_

#include <windows.h>
#include <netfw.h>
#include <vector>

#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "base/win/scoped_comptr.h"

namespace installer {

class AdvancedFirewallManager {
 public:
  AdvancedFirewallManager();
  ~AdvancedFirewallManager();

  
  
  bool Init(const base::string16& app_name, const base::FilePath& app_path);

  
  bool IsFirewallEnabled();

  
  bool HasAnyRule();

  
  
  bool AddUDPRule(const base::string16& rule_name,
                  const base::string16& description,
                  uint16_t port);

  
  void DeleteRuleByName(const base::string16& rule_name);

  
  void DeleteAllRules();

 private:
  friend class AdvancedFirewallManagerTest;

  
  base::win::ScopedComPtr<INetFwRule> CreateUDPRule(
      const base::string16& rule_name,
      const base::string16& description,
      uint16_t port);

  
  void GetAllRules(std::vector<base::win::ScopedComPtr<INetFwRule> >* rules);

  
  void DeleteRule(base::win::ScopedComPtr<INetFwRule> rule);

  base::string16 app_name_;
  base::FilePath app_path_;
  base::win::ScopedComPtr<INetFwPolicy2> firewall_policy_;
  base::win::ScopedComPtr<INetFwRules> firewall_rules_;

  DISALLOW_COPY_AND_ASSIGN(AdvancedFirewallManager);
};

}  

#endif  

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_MAC_POLICY_H_
#define SANDBOX_MAC_POLICY_H_

#include <mach/mach.h>

#include <map>
#include <string>

#include "sandbox/sandbox_export.h"

namespace sandbox {

enum PolicyDecision {
  POLICY_DECISION_INVALID,
  
  POLICY_ALLOW,
  
  
  POLICY_DENY_ERROR,
  
  
  POLICY_DENY_DUMMY_PORT,
  
  
  POLICY_SUBSTITUTE_PORT,
  POLICY_DECISION_LAST,
};

struct SANDBOX_EXPORT Rule {
  Rule();
  explicit Rule(PolicyDecision result);
  explicit Rule(mach_port_t override_port);

  PolicyDecision result;

  
  
  
  mach_port_t substitute_port;
};

struct SANDBOX_EXPORT BootstrapSandboxPolicy {
  typedef std::map<std::string, Rule> NamedRules;

  BootstrapSandboxPolicy();
  ~BootstrapSandboxPolicy();

  
  
  Rule default_rule;

  
  NamedRules rules;
};

SANDBOX_EXPORT bool IsPolicyValid(const BootstrapSandboxPolicy& policy);

}  

#endif  

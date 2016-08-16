// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PSL_MATCHING_HELPER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PSL_MATCHING_HELPER_H_

#include <string>

#include "base/basictypes.h"

class GURL;

namespace autofill {
struct PasswordForm;
}  

namespace password_manager {

enum PSLDomainMatchMetric {
  PSL_DOMAIN_MATCH_NOT_USED = 0,
  PSL_DOMAIN_MATCH_NONE,
  PSL_DOMAIN_MATCH_FOUND,
  PSL_DOMAIN_MATCH_COUNT
};

bool ShouldPSLDomainMatchingApply(
    const std::string& registry_controlled_domain);

bool IsPublicSuffixDomainMatch(const std::string& url1,
                               const std::string& url2);

std::string GetRegistryControlledDomain(const GURL& signon_realm);

}  

#endif  
